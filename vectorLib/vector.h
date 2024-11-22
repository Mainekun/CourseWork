#pragma once

#include <exception>
#include <iostream>
#include <vector>
#include <cmath>
#include <QVariant>
#include "matrix.h"

#define SIZE_CHECK(a, b) if (!isSizesEqual(a, b)) throw SizesUnequality()
#define i_RANGE_0_TO_N(n) for (ul i = 0; i < n; i++)

using ul = unsigned long;

class Vector
{
    std::string _name;
    ul _size;
    double * _elements;
    
    class Iterator
    {
        double* element_ptr;

    public:
        using pointer = double*;
        using reference = double&;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;

        Iterator(pointer ptr);

        reference operator*() const;
        pointer operator->();

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        Iterator& operator+=(int);
        Iterator& operator-=(int);

        difference_type operator-(const Iterator&) const;

        reference operator[](int) const;

        friend bool operator<=(const Iterator& a, const Iterator& b)
        { return a.element_ptr <= b.element_ptr;}
        friend bool operator>=(const Iterator& a, const Iterator& b)
        { return a.element_ptr >= b.element_ptr;}
        friend bool operator<(const Iterator& a, const Iterator& b)
        { return a.element_ptr < b.element_ptr;}
        friend bool operator>(const Iterator& a, const Iterator& b)
        { return a.element_ptr > b.element_ptr;}
        friend bool operator== (const Iterator& a, const Iterator& b) 
        { return a.element_ptr == b.element_ptr; }
        friend bool operator!= (const Iterator& a, const Iterator& b) 
        { return a.element_ptr != b.element_ptr; }
        friend Iterator operator+(int n, Iterator a)
        {
            return Vector::Iterator(a.element_ptr + n);
        }
        friend Iterator operator-(int n, Iterator a)
        {
            return Vector::Iterator(a.element_ptr - n);
        }
        friend Iterator operator+(Iterator a, int n)
        {
            return Vector::Iterator(a.element_ptr + n);
        }
        friend Iterator operator-(Iterator a, int n)
        {
            return Vector::Iterator(a.element_ptr - n);
        }
    };

public:
    //exceptions
    class SizesUnequality
    {
    public:
        SizesUnequality();
        char const * what();
    };

    class VectorProductException
    {
    public:
        VectorProductException();
        char const * what();
    };

    //vector
    constexpr void init(const std::string, const ul);
    Vector();
    Vector(const std::string, const ul, double const*);
    Vector(const std::string, const ul, const double = 0);
    constexpr Vector(const Vector&);
    ~Vector();

    ul size() const;
    double& at(ul) const;
    std::string getName() const;
    void setName(std::string);

    friend bool isSizesEqual(Vector&, Vector&);
    friend bool operator==(Vector&, Vector&);

    Vector operator=(Vector);

    Vector::Iterator begin() const;
    Vector::Iterator end() const;

    //math
    Vector operator-();
    Vector operator+(Vector&);
    Vector operator-(Vector&);
    Vector operator*(double);
    Vector operator/(double);

    double module();

    double elementsSum();
    double elementsProd();

    std::vector<ul> maxsIndices();
    std::vector<ul> minsIndices();

    double scalarProd(Vector&);


};

Vector vectorProduct(std::vector<Vector>&);

Q_DECLARE_METATYPE(Vector)

std::string dtos(double, int);
