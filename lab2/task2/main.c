#include "main.h"

int main() {
//    double arr[argc - 1] = {};
//    for (int i = 1; i < argc; ++i) {
//        parse_double(argv[i], &arr[i - 1]);
//    }
//    printf("%f", geometric_mean(argc - 1, arr[0], arr[1], arr[2]));
    printf("Geometric mean: %f\n\n", geometric_mean(3, 1.0, 2.0, 3.0));

    printf("Fast exponentiation: %f\n", fast_exponentiation(2, -4));

    return 0;
}