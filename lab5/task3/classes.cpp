#include "main.h"

logical_values_array::logical_values_array(unsigned int val) {
    this->value = val;
}

unsigned int logical_values_array::getVal() const {
    return this->value;
}

logical_values_array logical_values_array::inversion() const {
    return ~value;
}

logical_values_array logical_values_array::conjuction(logical_values_array rval) const {
    return value & rval.value;
}

logical_values_array logical_values_array::disjunction(logical_values_array rval) const {
    return value | rval.value;
}

logical_values_array logical_values_array::implication(logical_values_array rval) const {
    return this->inversion().disjunction(rval.value);
}

logical_values_array logical_values_array::coimplication(logical_values_array rval) const {
    return implication(rval).inversion();
}

logical_values_array logical_values_array::exclusive_disjunction(logical_values_array rval) const {
    return inversion().conjuction(rval).disjunction(conjuction(rval.inversion()));  // !x & y | x & !y
}

logical_values_array logical_values_array::equivalence(logical_values_array rval) const {
    return exclusive_disjunction(rval).inversion();
}

logical_values_array logical_values_array::peirce_arrow(logical_values_array rval) const {
    return disjunction(rval).inversion();
}

logical_values_array logical_values_array::sheffer_stroke(logical_values_array rval) const {
    return conjuction(rval).inversion();
}

bool logical_values_array::equals(logical_values_array a, logical_values_array b) {
    return a.getVal() == b.getVal();
}

unsigned int logical_values_array::get_bit(int pos) const {
    return getVal() & (1 << pos);
}

char* logical_values_array::to_char(char *str) const {
    int size = sizeof(unsigned int) * 8;

    if (str == nullptr)
        throw std::invalid_argument("Null pointer");

    for (int i = 0; i < size; ++i) {
        str[size - i - 1] = (get_bit(i) ? '1' : '0');
    }
    str[size] = '\0';

    return str;
}
