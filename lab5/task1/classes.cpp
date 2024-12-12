#include "main.h"

binary_int::binary_int() {
    content = 0;
}

binary_int::binary_int(int x) {
    content = x;
}

binary_int binary_int::operator- () const {
    return adder(~this->content, 1);
}

binary_int binary_int::operator+ (binary_int x) const {
    return adder(this->content, x.content);
}

binary_int binary_int::operator- (binary_int x) const {
    return (*this) + (-x);
}

binary_int &binary_int::operator+= (binary_int x) {
    *this = (*this) + x;
    return *this;
}

binary_int &binary_int::operator-= (binary_int x) {
    *this = (*this) - x;
    return *this;
}

binary_int &binary_int::operator++ () {
    *this += 1;
    return *this;
}

binary_int &binary_int::operator-- () {
    *this -= 1;
    return *this;
}

binary_int binary_int::operator++ (int)& {
    binary_int copy = *this;
    ++(*this);
    return copy;
}

binary_int binary_int::operator-- (int)& {
    binary_int copy = *this;
    --(*this);
    return copy;
}

bool binary_int::operator< (binary_int x) const {
    return this->content < x.content;
}

binary_int binary_int::operator* (binary_int x) const {
    binary_int temp;

    for (binary_int i = 0; i < x; ++i) {
        temp += *this;
    }

    return temp;
}

binary_int &binary_int::operator*= (binary_int x) {
    *this = *this * x;

    return *this;
}

binary_int binary_int::operator<< (binary_int x) const {
    return this->content << x.content;
}

binary_int binary_int::operator>> (binary_int x) const {
    return this->content >> x.content;
}

binary_int &binary_int::operator<<= (binary_int x) {
    *this = *this << x;

    return *this;
}

binary_int &binary_int::operator>>= (binary_int x) {
    *this = *this >> x;

    return *this;
}

binary_int binary_int::operator& (binary_int x) const {
    return this->content & x.content;
}

std::ostream &operator<< (std::ostream &stream, const binary_int& binaryInt) {
    binary_int value = binaryInt.content;
    for (binary_int i = ((binary_int) (sizeof(int) * 8)) - 1; i.content >= 0; --i) {
        int bit = (value >> i).content & 1;
        stream << bit;
    }

    return stream;
}

std::pair<binary_int, binary_int> binary_int::split_bits() const {
    binary_int half_bits = sizeof(int) * 4;
    binary_int high_bits = ((*this >> half_bits) & (((binary_int)(1) << half_bits) - 1)) << half_bits;
    binary_int low_bits = *this & (((binary_int)(1) << half_bits) - 1);

    return std::make_pair(high_bits, low_bits);
}

int adder(int a, int b) {
    int carry = 0;

    while (b != 0) {
        carry = a & b;

        a ^= b;
        b = carry << 1;
    }

    return a;
}