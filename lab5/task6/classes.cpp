#include "main.h"

vector::vector(size_t length, double default_value) {
    this->length = length;
    this->cap = length * 2;
    this->val = new double[this->cap];
    std::fill(val, val + length, default_value);
    std::fill(val + length, val + cap, 0);
}

vector::vector(vector::iterator first, vector::iterator last) {
    this->length = std::distance(first, last);
    this->cap = length * 2;
    this->val = new double[this->cap];
    std::copy(first, last, this->val);
}

vector::~vector() {
    delete[] this->val;
    this->length = 0;
    this->cap = 0;
}

double &vector::at(size_t index) const {
    if (index > length)
        throw std::invalid_argument("Out of bounds");

    return val[index];
}

double &vector::front() const {
    return at(0);
}

double &vector::back() const {
    return at(length - 1);
}

double *vector::data() const {
    return val;
}

bool vector::empty() const {
    return length == 0;
}

size_t vector::size() const {
    return length;
}

size_t vector::capacity() const {
    return cap;
}

void vector::reserve(size_t num) {
    if (num <= capacity())
        return;

    double *new_array = new double[num];

    std::memset(new_array, 0, num * sizeof(double));
    std::memcpy(new_array, val, cap * sizeof(double));

    delete[] val;
    val = new_array;
    cap = num;
}

void vector::shrink_to_fit() {
    if (size() >= capacity())
        return;

    double *new_array = new double[length];

    std::memcpy(new_array, val, cap * sizeof(double));

    delete[] val;
    val = new_array;
    cap = length;
}

void vector::clear() {
    length = 0;
}

void vector::insert(size_t index, double elem) {
    if (index > capacity()) {
        reserve(index + 5);
    } else if (size() + 1 >= capacity()) {
        reserve(capacity() * 2);
    }

    if (index > size())
        length = index + 1;
    else
        length++;

    for (size_t i = size(); i > index; --i) {
        val[i] = val[i - 1];
    }

    val[index] = elem;
}

void vector::erase(size_t index) {
    if (index > size())
        return;

    for (size_t i = index; i < size(); ++i) {
        val[i] = val[i + 1];
    }

    length--;
}

void vector::push_back(double elem) {
    insert(size(), elem);
}

double vector::pop_back() {
    double res = back();
    erase(size());
    return res;
}

void vector::resize(size_t size, double elem) {
    if (size > this->size()) {
        reserve(size);
        std::fill(val + this->size(), val + size, elem);
    }
    length = size;
}

std::partial_ordering vector::operator<=>(const vector &other) const {
    size_t minSize = std::min(size(), other.size());
    for (size_t i = 0; i < minSize; ++i) {
        if (val[i] != other.val[i]) {
            return val[i] <=> other.val[i];
        }
    }
    return size() <=> other.size();
}

bool vector::operator==(const vector &other) const {
    return (*this <=> other) == 0;
}

std::ostream &operator<<(std::ostream &stream, const vector &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        stream << vec.at(i) << ' ';
    }
    stream << '\n';

    return stream;
}

std::strong_ordering vector::iterator::operator<=>(const vector::iterator &other) const {
    if (ptr < other.ptr) return std::strong_ordering::less;
    if (ptr > other.ptr) return std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

vector::iterator vector::iterator::operator++(int) { iterator tmp = *this; ++ptr; return tmp; }

vector::iterator vector::iterator::operator--(int) { iterator tmp = *this; --ptr; return tmp; }
