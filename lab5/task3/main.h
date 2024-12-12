#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <iostream>

class logical_values_array {
private:
    unsigned int value;
public:
    logical_values_array(unsigned int val = 0);

    unsigned int getVal() const;

    logical_values_array inversion() const;

    logical_values_array conjuction(logical_values_array rval) const;

    logical_values_array disjunction(logical_values_array rval) const;

    logical_values_array implication(logical_values_array rval) const;

    logical_values_array coimplication(logical_values_array rval) const;

    logical_values_array exclusive_disjunction(logical_values_array rval) const;

    logical_values_array equivalence(logical_values_array rval) const;

    logical_values_array peirce_arrow(logical_values_array rval) const;

    logical_values_array sheffer_stroke(logical_values_array rval) const;

    static bool equals(logical_values_array a, logical_values_array b);

    unsigned int get_bit(int pos) const;

    char* to_char(char *str) const;

    friend std::ostream &operator<< (std::ostream &stream, const logical_values_array& logicv);

};

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
