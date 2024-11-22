#include "vector.h"

Vector::Iterator::Iterator(pointer ptr) : 
element_ptr(ptr) {}

Vector::Iterator::reference Vector::Iterator::operator*() const
{
    return *element_ptr;
}

Vector::Iterator::pointer Vector::Iterator::operator->()
{
    return element_ptr;
}

Vector::Iterator& Vector::Iterator::operator++()
{
    element_ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

Vector::Iterator& Vector::Iterator::operator+=(int n)
{
    element_ptr += n;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(int n)
{
    element_ptr -= n;
    return *this;
}

Vector::Iterator Vector::begin() const
{ return Iterator(&_elements[0]); }

Vector::Iterator Vector::end() const
{ return Iterator(&_elements[_size]); }

Vector::Iterator::difference_type
Vector::Iterator::operator -(const Vector::Iterator& a) const
{ return element_ptr - a.element_ptr; }

Vector::Iterator::reference
Vector::Iterator::operator [](int n) const
{ return *(element_ptr + n); }

