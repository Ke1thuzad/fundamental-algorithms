#include "main.h"

int parse_file(FILE* in, HashTable * ht);

int main(int argc, char **argv) {
    if (argc != 2)
        return throw_err(INCORRECT_ARGUMENTS);

    FILE *in = fopen(argv[1], "r");
    if (!in)
        return throw_err(FILE_ERROR);

    int err;

    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
    if (!ht)
        return throw_err(MEMORY_NOT_ALLOCATED);

    err = create_hash_table(ht, HASHSIZE);
    if (err) {
        free(ht);
        return err;
    }

    err = parse_file(in, ht);

    destroy_hash_table(ht);
    free(ht);

    return err;
}

// Господи помилуй этот код или заверши наши страдания.
int parse_file(FILE* in, HashTable * ht) {
    int err, defines = 1;

    Array arr, spacings;
    err = create_arr(64, &arr);
    if (err)
        return err;

    err = create_arr(64, &spacings);
    if (err) {
        destroy(&arr);
        return err;
    }

    int ch = fgetc(in);

    while(ch > 0) {
        if (ch > ' ') {
            err = append(&arr, (char) ch);
            if (err) {
                destroy(&arr);
                destroy(&spacings);
                return err;
            }

            if (defines && !compare_array_str(arr, "#define")) {
                fgetc(in);

                reset(&arr);

                err = read_value(&in, &arr, 0);
                if (err) {
                    destroy(&arr);
                    destroy(&spacings);
                    return err > 0 ? err : 0;
                }

                String def_name;
                err = create_str(&def_name, arr.val);
                if (err) {
                    destroy(&arr);
                    destroy(&spacings);
                    return err;
                }

                fgetc(in);

                reset(&arr);

                err = read_value(&in, &arr, 0);
                if (err) {
                    destroy(&arr);
                    destroy(&spacings);
                    destroy_str(&def_name);
                    return err > 0 ? err : 0;
                }

                String def_value;
                err = create_str(&def_value, arr.val);
                if (err) {
                    destroy(&arr);
                    destroy(&spacings);
                    destroy_str(&def_name);
                    return err;
                }

                err = insert_node(ht, def_name, def_value);

                destroy_str(&def_name);
                destroy_str(&def_value);

                if (err) {
                    destroy(&arr);
                    destroy(&spacings);
                    return err;
                }

                reset(&arr);
                reset(&spacings);
            } else {
                if (arr.val[0] == '#') {
                    ch = fgetc(in);
                    continue;
                }
                defines = 0;

                printf("%s", spacings.val);

                reset(&spacings);
                reset(&arr);

                err = read_value(&in, &arr, (char) ch);
                if (err > 0) {
                    destroy(&arr);
                    destroy(&spacings);
                    return err;
                }

                if (err == EOF)
                    fgetc(in);

                unsigned long hash;
                String str;
                err = create_str(&str, arr.val);
                if (err) {
                    destroy(&arr);
                    destroy(&spacings);
                    return err;
                }

                err = hash_function(str, &hash, ht->size);
                destroy_str(&str);
                if (err) {
                    destroy(&arr);
                    destroy(&spacings);
                    return err;
                }

                hash %= ht->size;
                Node *val = ht->table[hash], *prev = val;
                if (val) {
                    while (val) {
                        prev = val;
                        err = hash_function(val->value, &hash, ht->size);
                        if (err) {
                            destroy(&arr);
                            destroy(&spacings);

                            return err;
                        }
                        hash %= ht->size;
                        val = ht->table[hash];
                    }
                    printf("%s", prev->value.val);
                } else {
                    printf("%s", arr.val);
                }

                reset(&arr);
            }
        } else {
            err = append(&spacings, (char) ch);
            if (err) {
                destroy(&arr);
                destroy(&spacings);

                return err;
            }

            if (arr.length > 0) {
                printf("%s", arr.val);
                reset(&arr);
            }
        }

        ch = fgetc(in);
    }

    printf("%s", spacings.val);

    destroy(&arr);
    destroy(&spacings);

    return 0;
}

