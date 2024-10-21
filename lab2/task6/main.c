#include "main.h"

int main() {
    int res, res0, res1;
    char temp[100];

//    unroman("MMMCMXCIX", &res);

//    zecken(&res, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1);
//    printf("%d", res);

    FILE* a = fopen("a", "r");
//

//    scanf("asd%d%d w%d", &res0, &res, &res1, temp);
    overfscanf(a, " ", &res0, 2, &res, temp, &res1);
//    fscanf(stdin, "   %d   %d %s", &res, &res1, temp);
//    unzeckendorf(&res, a);
//    printf("%d\n", fgetc(a));
    printf("%d %d %s %d", res, res0, temp, res1);

    return 0;
}
