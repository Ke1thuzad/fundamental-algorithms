#include "main.h"

int main() {
    binary_int a(128);

//    std::cout << a;

    std::cout << a + a - 1 << ' ' << a * 10 << ' ' << '\n' << a << '\n' << a++ << '\n' << a << '\n' << ++a << '\n';

    std::pair<binary_int, binary_int> res = ((binary_int)((1 << 31) - 1)).split_bits();

    std::cout << res.first << ' ' << res.second;

    return 0;
}