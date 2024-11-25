#include "main.h"

int main() {
    // Create some complex numbers
    complex c1(3.0, 4.0);
    complex c2(1.0, -2.0);

    // Test addition
    complex sum = c1 + c2;
    std::cout << "Sum: " << sum;

    // Test subtraction
    complex diff = c1 - c2;
    std::cout << "Difference: " << diff;

    // Test multiplication
    complex prod = c1 * c2;
    std::cout << "Product: " << prod;

    // Test division
    try {
        complex quot = c1 / c2;
        std::cout << "Quotient: " << quot;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Test absolute value
    double abs_val = c1.abs();
    std::cout << "Absolute value of c1: " << abs_val << std::endl;

    // Test argument
    double arg_val = c1.arg();
    std::cout << "Argument of c1: " << arg_val << std::endl;

    return 0;
}