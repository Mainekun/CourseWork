#include "vectoritem.h"

VectorItem::VectorItem() : _name(""), _vec(0) {}

VectorItem::VectorItem(Vector* vec, std::string name) :
    _name(name), _vec(vec)
{}

std::string VectorItem::name() const { return _name; }

Vector* VectorItem::vec() const { return _vec; }

void VectorItem::setName(std::string name) { _name = name; }

void VectorItem::setVec(Vector a) { _vec = new Vector(a); }

VectorItem VectorItem::operator=(VectorItem& a)
{
    _name = a.name();
    _vec = a.vec();

    return *this;
}
