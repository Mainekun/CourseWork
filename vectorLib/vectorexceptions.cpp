#include "vector.h"

VecLib::Vector::SizesUnequality::SizesUnequality() {}

char const * VecLib::Vector::SizesUnequality::what()
{
    return "Sizes are not equal";
}
