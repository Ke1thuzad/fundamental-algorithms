#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <iostream>
#include <cstring>
#include <algorithm>

class vector {
private:
    double *val;
    size_t length;
    size_t cap;

    class iterator {
    private:
        double* ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = double;
        using difference_type = std::ptrdiff_t;
        using pointer = double*;
        using reference = double&;

        iterator(double* p) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr; }

        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }

        iterator& operator--() { --ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr; return tmp; }

        iterator& operator+=(difference_type n) { ptr += n; return *this; }
        iterator& operator-=(difference_type n) { ptr -= n; return *this; }

        iterator operator+(difference_type n) const { return {ptr + n}; }
        iterator operator-(difference_type n) const { return {ptr - n}; }

        difference_type operator-(const iterator& other) const { return ptr - other.ptr; }

        reference operator[](difference_type n) const { return ptr[n]; }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        bool operator<(const iterator& other) const { return ptr < other.ptr; }
        bool operator<=(const iterator& other) const { return ptr <= other.ptr; }
        bool operator>(const iterator& other) const { return ptr > other.ptr; }
        bool operator>=(const iterator& other) const { return ptr >= other.ptr; }

        std::strong_ordering operator<=>(const iterator& other) const {
            if (ptr < other.ptr) return std::strong_ordering::less;
            if (ptr > other.ptr) return std::strong_ordering::greater;
            return std::strong_ordering::equal;
        }
    };

public:
    vector(size_t length, double default_value = 0) {
        this->length = length;
        this->cap = length * 2;
        this->val = new double[this->cap];
        std::fill(val, val + length, default_value);
        std::fill(val + length, val + cap, 0);
    }

    explicit vector(iterator first, iterator last) {
        this->length = std::distance(first, last);
        this->cap = length * 2;
        this->val = new double[this->cap];
        std::copy(first, last, this->val);
    }

    vector(std::initializer_list<double> init) : vector(const_cast<double*>(init.begin()), const_cast<double*>(init.end())) {}

    ~vector() {
        delete[] this->val;
        this->length = 0;
        this->cap = 0;
    }

    double& at(size_t index) const {
        if (index > length)
            throw std::invalid_argument("Out of bounds");

        return val[index];
    }

    double& front() const {
        return at(0);
    }

    double& back() const {
        return at(length - 1);
    }

    double* data() const {
        return val;
    }

    bool empty() const {
        return length == 0;
    }

    size_t size() const {
        return length;
    }

    size_t capacity() const {
        return cap;
    }

    void reserve(size_t num) {
        if (num <= capacity())
            return;

        double *new_array = new double[num];

        std::memset(new_array, 0, num * sizeof(double));
        std::memcpy(new_array, val, cap * sizeof(double));

        delete[] val;
        val = new_array;
        cap = num;
    }

    void shrink_to_fit() {
        if (size() >= capacity())
            return;

        double *new_array = new double[length];

        std::memcpy(new_array, val, cap * sizeof(double));

        delete[] val;
        val = new_array;
        cap = length;
    }

    void clear() {
        length = 0;
    }

    void insert(size_t index, double elem) {
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

    void erase(size_t index) {
        if (index > size())
            return;

        for (size_t i = index; i < size(); ++i) {
            val[i] = val[i + 1];
        }

        length--;
    }

    void push_back(double elem) {
        insert(size(), elem);
    }

    double pop_back() {
        double res = back();
        erase(size());
        return res;
    }

    void resize(size_t size, double elem) {
        if (size > this->size()) {
            reserve(size);
            std::fill(val + this->size(), val + size, elem);
        }
        length = size;
    }

    std::partial_ordering operator<=>(const vector& other) const {
        size_t minSize = std::min(size(), other.size());
        for (size_t i = 0; i < minSize; ++i) {
            if (val[i] != other.val[i]) {
                return val[i] <=> other.val[i];
            }
        }
        return size() <=> other.size();
    }

    bool operator==(const vector& other) const {
        return (*this <=> other) == 0;
    }

    iterator begin() { return {val}; }
    iterator end() { return {val + length}; }

    friend std::ostream &operator<<(std::ostream &stream, const vector& vec) {
        for (int i = 0; i < vec.size(); ++i) {
            stream << vec.at(i) << ' ';
        }
        stream << '\n';

        return stream;
    }
};

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
