#include "main.h"

int main() {
    double res;
    polynomial(&res, 1.0, 3, 1.0, 1.0, 5.0);

    printf("%f", res);

    return 0;
}
