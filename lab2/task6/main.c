#include "main.h"

int main() {
    int res;

//    unroman("MMMCMXCIX", &res);

    zecken(&res, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1);
    printf("%d", res);

    return 0;
}
