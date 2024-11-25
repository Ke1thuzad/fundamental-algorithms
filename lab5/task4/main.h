#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <iostream>
#include <cmath>

class complex {
private:
    double real, imaginary;
public:
    complex(double real = 0, double imaginary = 0);

    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    complex operator+(complex rval) const;

    complex operator-(complex rval) const;

    complex operator*(complex rval) const;

    complex operator/(complex rval) const;

    double sqabs() const;

    double abs() const;

    double arg() const;

    friend std::ostream &operator<<(std::ostream &stream, complex complexVal);
};

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
