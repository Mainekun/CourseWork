#include "vector.h"

VecLib::Vector::SizesUnequality::SizesUnequality() {}

char const * VecLib::Vector::SizesUnequality::what()
{
    return "Sizes are not equal";
}

VecLib::Vector::VectorProductException::VectorProductException() {}

char const * VecLib::Vector::VectorProductException::what()
{
    return "Vector have to have size 3";
}
