#include "main.h"

int compare(const void* a, const void* b) {
    return ( *(int*)a - *(int*)b );
}

int chrtoint(char x, int* num) {
    int a = x - '0';
    if (a < 0 || a > 9) return throw_err(OUT_OF_BOUNDS);
    *num = a;
    return 0;
}

int parse_int(char* str, int* res) {
    int i = 0, result = 0, sign = 1;

    if (str[0] == '-') i++, sign = -1;

    while (str[i] != '\0') {
        int temp, err = chrtoint(str[i], &temp);
        if (err)
            return err;
        result *= 10;
        result += temp;
        i++;
    }

    *res = sign * result;
    return 0;
}

int part_one(int a, int b) {
    if (a < 0 || b < 0)
        return throw_err(INCORRECT_ARGUMENTS);
    if (b < a) {
        int temp = a;
        a = b;
        b = temp;
    }
    int min = INT_MAX, max = INT_MIN, max_ind = -1, min_ind = -1;
    int arr[1000], number;
    for (int i = 0; i < 1000; ++i) {
        number = a + rand() % (b - a);
        if (number > max) {
            max = number;
            max_ind = i;
        } else if (number < min) {
            min = number;
            min_ind = i;
        }
        arr[i] = number;
    }
    int temp;
    temp = arr[max_ind];
    arr[max_ind] = arr[min_ind];
    arr[min_ind] = temp;

    for (int i = 0; i < 1000; ++i) {
        printf("%d ", arr[i]);
    }
    printf("%d %d %d\n", arr[max_ind], arr[min_ind], max);

    return 0;
}

int part_two() {
    IntArray A, B, C;
    int err = create_intarr(10 + rand() % 9990, &A);
    if (err)
        return err;

    err = create_intarr(10 + rand() % 9990, &B);
    if (err) {
        destroy_int(&A);
        return err;
    }
    err = create_intarr(5000, &C);
    if (err) {
        destroy_int(&A);
        destroy_int(&B);
        return err;
    }

    err = fill_array(&A, -1000, 1000) | fill_array(&B, -1000, 1000);
    if (err)
        return err;

    qsort(B.val, B.length, sizeof(int), compare);
    for (int i = 0; i < A.length; ++i) {
        int key = A.val[i], closest_id = binary_search_closest(B, key);
        append_int(&C, key + B.val[closest_id]);
    }

    printf("\n\nArray A: \n");
    print_intarr(A);
    printf("\n\n\n");
    printf("Array B: \n");
    print_intarr(B);
    printf("\n\n\n");
    printf("Array C: \n");
    print_intarr(C);

    destroy_int(&A);
    destroy_int(&B);
    destroy_int(&C);

    return 0;
}

int fill_array(IntArray* arr, int a, int b) {
    for (int i = 0; i < arr->capacity; ++i) {
        int err = append_int(arr, a + rand() % (b - a));
        if (err)
            return err;
    }

    return 0;
}

int binary_search_closest(IntArray arr, int key) {
    int closest = 0;
    int l = 0, r = arr.length - 1, mid;
    while(l <= r) {
        mid = (l + r) / 2;
        if ((abs(arr.val[mid]) - key) < abs(arr.val[closest] - key)) {
            closest = mid;
        }

        if (arr.val[mid] == key) {
            return mid;
        }
        if (arr.val[mid] < key)
            l = mid + 1;
        else if (arr.val[mid] > key)
            r = mid - 1;
    }

    return closest;
}