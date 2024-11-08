#include "main.h"

int main(int argc, char **argv) {
    String a, b, c, d, sp, e, as;
    create_str(&a, "A");
    create_str(&b, "B");
    create_str(&c, "C");
    create_str(&as, "D");
    create_str(&d, "T");
    create_str(&sp, "\t");
    create_str(&e, "a");

    Node *root = create_tree_node(b);
    insert_tree(&root, c);
    insert_tree(&root, a);
    insert_tree(&root, a);
    insert_tree(&root, a);
    insert_tree(&root, a);
    insert_tree(&root, a);
    insert_tree(&root, a);
    insert_tree(&root, a);
    insert_tree(&root, d);
    insert_tree(&root, d);
    insert_tree(&root, d);
    insert_tree(&root, d);
    insert_tree(&root, sp);
    insert_tree(&root, e);
    insert_tree(&root, e);
    insert_tree(&root, e);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);
    insert_tree(&root, as);

    print_tree(root, 0);

    int treedepth;
    NodeList *res = {};

    find_most_frequent_words(root, &res, &treedepth);

    print_list(stdout, res);
//    find_most_frequent_words(root, &res, &treedepth);
//
//    print_tree(res, 0);
//
//    printf("%d", treedepth);

    destroy_tree(root);

    destroy_str(&a);
    destroy_str(&b);
    destroy_str(&c);
    destroy_str(&d);
    destroy_str(&sp);

    return 0;
}
