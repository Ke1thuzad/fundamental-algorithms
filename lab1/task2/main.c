#include "main.h"
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 2) return 1;

    long double eps = strtold(argv[1], NULL);
    long double res = compute_series(eps, &series_e, 1, 0); // eps 0.000001

    printf("%d %Lf", (int)res, res);


    return 0;
}
