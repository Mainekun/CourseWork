#include "vector.h"

VecLib::Vector::Vector() : _name(""), _size(0), _elements(nullptr) {}

void VecLib::Vector::init(const std::string name, const ul size) try
{
    _name = name;
    _size = size;
    _elements = new e_type[size]{0};
}
catch(std::bad_alloc& e)
{
    std::cerr << "BAD_ALLOC\nSIZE: " << size << "\n";
    throw;
}

VecLib::Vector::Vector(
    const std::string name,
    const ul size,
    e_type const * elements)
{
    init(name, size);
    i_RANGE_0_TO_N(_size)
        _elements[i] = elements[i];
}


VecLib::Vector::Vector(
    const std::string name,
    const ul size,
    const e_type filler)
{
    init(name, size);
    i_RANGE_0_TO_N(_size)
        _elements[i] = filler;
}

VecLib::Vector::Vector(const Vector& a)
{
    init(a._name, a._size);
    i_RANGE_0_TO_N(_size)
        _elements[i] = a._elements[i];
}

VecLib::Vector::~Vector() { delete[] _elements; }

ul VecLib::Vector::size() const { return _size; }

e_type& VecLib::Vector::at(ul index) const
{
    if (index >= _size) throw std::out_of_range("");
    return _elements[index];
}

std::string VecLib::Vector::getName() const
{
    return _name;
}

void VecLib::Vector::setName(std::string name)
{
    _name = name;
}

VecLib::Vector VecLib::Vector::operator=(VecLib::Vector a)
{
    _name = a._name;

    if (_elements == nullptr)
        delete[] _elements;

    _size = a._size;
    _elements = new e_type[_size];

    for (ul i = 0; i < _size; i++)
        _elements[i] = a._elements[i];

    return *this;
}
