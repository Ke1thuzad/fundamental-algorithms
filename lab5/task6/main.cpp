#include "main.h"

int main() {
    vector a(10, 1);
//
    a.insert(15, 3);
    a.insert(50, 899);
    a.insert(2, 2);
    a.insert(2, 2);
    a.insert(2, 2);
    a.insert(14, 7);
    a.insert(16, 8);
    a.erase(14);
    a.erase(1);

    vector b(a.begin(), a.end());
//
//    std::cout << a.pop_back() << '\n';
//    std::cout << a.pop_back() << '\n';
//    std::cout << a.pop_back() << '\n';
//    std::cout << a.pop_back() << '\n';
//    std::cout << a.pop_back() << '\n';

//    a.resize(222, 4);
//
//    a.insert(221, 5);

//    std::cout << b << b.size() << '\n' << b.capacity() << '\n' << (a.begin() <= a.end());

    std::cout << a << a.size() << '\n' << a.capacity() << '\n' << a.back();

    return 0;
}
