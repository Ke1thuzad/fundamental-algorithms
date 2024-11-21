#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <iostream>

class binary_int {
private:
public:
    int content;
    binary_int();
    binary_int(int x);
    binary_int operator- () const;
    binary_int operator+ (binary_int x) const;
    binary_int operator- (binary_int x) const;
    binary_int &operator+= (binary_int x);
    binary_int &operator-= (binary_int x);
    binary_int &operator++ ();
    binary_int &operator-- ();
    bool operator< (binary_int x) const;
    binary_int &operator*= (binary_int x);
    binary_int operator* (binary_int x) const;
    binary_int operator<< (binary_int x) const;
    binary_int operator>> (binary_int x) const;
    binary_int &operator<<= (binary_int x);
    binary_int &operator>>= (binary_int x);
    binary_int operator& (binary_int) const;

    std::pair<binary_int, binary_int> split_bits() const;
};

std::ostream &operator<< (std::ostream &stream, binary_int binaryInt);

int adder(int a, int b);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
