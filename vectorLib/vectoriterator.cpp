#include "vector.h"

VecLib::Vector::Iterator::Iterator(pointer ptr) :
element_ptr(ptr) {}

VecLib::Vector::Iterator::reference VecLib::Vector::Iterator::operator*() const
{
    return *element_ptr;
}

VecLib::Vector::Iterator::pointer VecLib::Vector::Iterator::operator->()
{
    return element_ptr;
}

VecLib::Vector::Iterator& VecLib::Vector::Iterator::operator++()
{
    element_ptr++;
    return *this;
}

VecLib::Vector::Iterator VecLib::Vector::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

VecLib::Vector::Iterator& VecLib::Vector::Iterator::operator+=(int n)
{
    element_ptr += n;
    return *this;
}

VecLib::Vector::Iterator& VecLib::Vector::Iterator::operator-=(int n)
{
    element_ptr -= n;
    return *this;
}

VecLib::Vector::Iterator VecLib::Vector::begin() const
{ return Iterator(&_elements[0]); }

VecLib::Vector::Iterator VecLib::Vector::end() const
{ return Iterator(&_elements[_size]); }

VecLib::Vector::Iterator::difference_type
VecLib::Vector::Iterator::operator -(const VecLib::Vector::Iterator& a) const
{ return element_ptr - a.element_ptr; }

VecLib::Vector::Iterator::reference
VecLib::Vector::Iterator::operator [](int n) const
{ return *(element_ptr + n); }

