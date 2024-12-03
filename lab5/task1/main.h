#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <iostream>

class binary_int {
private:
    int content;
public:
    binary_int();
    binary_int(int x);
    binary_int operator- () const;
    binary_int operator+ (binary_int x) const;
    binary_int operator- (binary_int x) const;
    binary_int &operator+= (binary_int x);
    binary_int &operator-= (binary_int x);
    binary_int &operator++ ();
    binary_int &operator-- ();
    binary_int operator++ (int)&;
    binary_int operator-- (int)&;
    bool operator< (binary_int x) const;
    binary_int &operator*= (binary_int x);
    binary_int operator* (binary_int x) const;
    binary_int operator<< (binary_int x) const;
    binary_int operator>> (binary_int x) const;
    binary_int &operator<<= (binary_int x);
    binary_int &operator>>= (binary_int x);
    binary_int operator& (binary_int) const;

    std::pair<binary_int, binary_int> split_bits() const;
    friend std::ostream &operator<< (std::ostream &stream, const binary_int& binaryInt);
};


int adder(int a, int b);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
