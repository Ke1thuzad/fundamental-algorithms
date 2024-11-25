#include "main.h"

complex::complex(double real, double imaginary) {
    this->real = real;
    this->imaginary = imaginary;
}

complex complex::operator+(complex rval) const {
    complex res = {real + rval.real, imaginary + rval.imaginary};
    return res;
}

complex complex::operator-(complex rval) const {
    complex res = {real - rval.real, imaginary - rval.imaginary};
    return res;
}

complex complex::operator*(complex rval) const {
    complex res = {real * rval.real - imaginary * rval.imaginary, imaginary * rval.real + real * rval.imaginary};
    return res;
}

complex complex::operator/(complex rval) const {
    if (rval.imaginary == 0 && rval.real == 0)
        throw std::invalid_argument("Division by zero");

    complex res;

    double squared_abs = rval.sqabs();

    res.real = rval.real * real + rval.imaginary * imaginary;
    res.real /= squared_abs;

    res.imaginary = imaginary * rval.real - real * rval.imaginary;
    res.imaginary /= squared_abs;

    return res;
}

double complex::sqabs() const {
    return real * real + imaginary * imaginary;
}

double complex::abs() const {
    return sqrt(this->sqabs());
}

double complex::arg() const {
    if (real == 0) {
        if (imaginary > 0)
            return M_PI / 2;
        else if (imaginary < 0)
            return -M_PI / 2;
        else
            return 0;
    }

    double res = atan(imaginary / real);

    if (imaginary > 0 && real < 0)
        res += M_PI;
    else if (imaginary < 0 && real < 0)
        res -= M_PI;

    return res;
}

std::ostream &operator<<(std::ostream &stream, complex complexVal) {
    if (complexVal.real != 0)
        stream << complexVal.real << ' ';

    if (complexVal.imaginary == 0) {
        if (complexVal.real == 0)
            stream << 0;
        stream << '\n';
        return stream;
    }

    if (complexVal.imaginary < 0)
        stream << "- ";
    else if (complexVal.imaginary > 0)
        stream << "+ ";
    stream << abs(complexVal.imaginary) << "i\n";

    return stream;
}

