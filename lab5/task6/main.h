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
        iterator operator++(int);

        iterator& operator--() { --ptr; return *this; }
        iterator operator--(int);

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

        std::strong_ordering operator<=>(const iterator& other) const;
    };

public:
    vector(size_t length, double default_value = 0);

    explicit vector(iterator first, iterator last);

    vector(std::initializer_list<double> init) : vector(const_cast<double*>(init.begin()), const_cast<double*>(init.end())) {}

    ~vector();

    double& at(size_t index) const;

    double& front() const;

    double& back() const;

    double* data() const;

    bool empty() const;

    size_t size() const;

    size_t capacity() const;

    void reserve(size_t num);

    void shrink_to_fit();

    void clear();

    void insert(size_t index, double elem);

    void erase(size_t index);

    void push_back(double elem);

    double pop_back();

    void resize(size_t size, double elem);

    std::partial_ordering operator<=>(const vector& other) const;

    bool operator==(const vector& other) const;

    iterator begin() { return {val}; }
    iterator end() { return {val + length}; }

    friend std::ostream &operator<<(std::ostream &stream, const vector& vec);
};

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
