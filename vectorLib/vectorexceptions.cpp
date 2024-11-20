#include "vector.h"

Vector::SizesUnequality::SizesUnequality() {}

char const * Vector::SizesUnequality::what()
{
    return "Sizes are not equal";
}

Vector::VectorProductException::VectorProductException() {}

char const * Vector::VectorProductException::what()
{
    return "Vector have to have size 3";
}