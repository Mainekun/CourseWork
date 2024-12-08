#pragma once

#include <exception>
#include <iostream>
#include <vector>
#include <cmath>
#include <QVariant>
#include "matrix.h"

#define SIZE_CHECK(a, b) if (!isSizesEqual(a, b)) throw VecLib::Vector::SizesUnequality()
#define i_RANGE_0_TO_N(n) for (ul i = 0; i < n; i++)

using ul = unsigned long;
using e_type = double;

namespace VecLib
{

class Vector
{
    std::string _name;
    ul _size;
    e_type * _elements;
    
    class Iterator
    {
        e_type* element_ptr;

    public:
        using pointer = e_type*;
        using reference = e_type&;
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
            return Iterator(a.element_ptr + n);
        }
        friend Iterator operator-(int n, Iterator a)
        {
            return Iterator(a.element_ptr - n);
        }
        friend Iterator operator+(Iterator a, int n)
        {
            return Iterator(a.element_ptr + n);
        }
        friend Iterator operator-(Iterator a, int n)
        {
            return Iterator(a.element_ptr - n);
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
    void init(const std::string, const ul);
    Vector();
    Vector(const std::string, const ul, e_type const*);
    Vector(const std::string, const ul, const e_type = 0);
    Vector(const Vector&);
    ~Vector();

    ul size() const;
    e_type& at(ul) const;
    std::string getName() const;
    void setName(std::string);

    std::string at_s(ul index)
    {
        return std::to_string(this->at(index));
    }

    friend bool isSizesEqual(Vector a, Vector b)
    { return a._size == b._size; }
    friend bool operator==(Vector a, Vector b)
    {
        if (!isSizesEqual(a, b)) return false;

        for (ul i = 0; i < a._size; i++)
            if (a.at(i) != b.at(i))
                return false;

        return true;
    }

    Vector operator=(Vector);

    Vector::Iterator begin() const;
    Vector::Iterator end() const;

    //math
    Vector operator-();

    Vector operator*(e_type);
    Vector operator/(e_type);

    e_type module();

    e_type elementsSum();
    e_type elementsProd();

    std::vector<ul> maxsIndices();
    std::vector<ul> minsIndices();

    e_type scalarProd(Vector);

    Vector AscSort();
    Vector DesSort();

    Vector reverse();

    friend Vector GCD(Vector, Vector);
    friend Vector LCD(Vector, Vector);
};

Vector operator+(Vector, Vector);
Vector operator-(Vector, Vector);

Vector vectorProduct(std::vector<Vector>);

}

Q_DECLARE_METATYPE(VecLib::Vector)

std::string dtos(double, int);
