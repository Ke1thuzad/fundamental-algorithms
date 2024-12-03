#include "main.h"

int main() {
    logical_values_array a(3);
    logical_values_array b(5);

    std::cout << "a: " << a.getVal() << std::endl;
    std::cout << "b: " << b.getVal() << std::endl;

    char binary_a[33];
    char binary_b[33];

    a.to_char(binary_a);
    b.to_char(binary_b);

    std::cout << "Binary a: " << binary_a << std::endl;
    std::cout << "Binary b: " << binary_b << std::endl;

    std::cout << "Inversion a: " << a.inversion() << std::endl;
    std::cout << "Conjunction a & b: " << a.conjuction(b) << std::endl;
    std::cout << "Disjunction a | b: " << a.disjunction(b) << std::endl;
    std::cout << "Implication a -> b: " << a.implication(b) << std::endl;
    std::cout << "Coimplication a <-> b: " << a.coimplication(b) << std::endl;
    std::cout << "Exclusive Disjunction a ^ b: " << a.exclusive_disjunction(b) << std::endl;
    std::cout << "Equivalence a == b: " << a.equivalence(b) << std::endl;
    std::cout << "Peirce Arrow a ↓ b: " << a.peirce_arrow(b) << std::endl;
    std::cout << "Sheffer Stroke a | b: " << a.sheffer_stroke(b) << std::endl;

    std::cout << "a equals b: " << logical_values_array::equals(a, b) << std::endl;

    return 0;
}
