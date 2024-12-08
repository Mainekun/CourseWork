#include "vector.h"
#include <algorithm>
#include <vector>

VecLib::Vector VecLib::Vector::operator-()
{
    VecLib::Vector negated = *this;

    for (auto& i : negated) i *= -1;

    return negated;
}

VecLib::Vector VecLib::operator+(VecLib::Vector a, VecLib::Vector b)
{
    SIZE_CHECK(a, b);
    
    Vector c("", a.size());

    i_RANGE_0_TO_N(a.size())
        c.at(i) = a.at(i) + b.at(i);

    return c;
}

VecLib::Vector VecLib::operator-(VecLib::Vector a, VecLib::Vector b)
{
    SIZE_CHECK(a, b);
    
    VecLib::Vector c("", a.size());

    i_RANGE_0_TO_N(a.size())
        c.at(i) = a.at(i) - b.at(i);

    return c;
}

VecLib::Vector VecLib::Vector::operator*(e_type k)
{
    VecLib::Vector a = *this;

    i_RANGE_0_TO_N(_size)
        a.at(i) *= k;
    
    return a;
}

VecLib::Vector VecLib::Vector::operator/(e_type k)
{
    if (k == 0) 
        return VecLib::Vector("", _size);

    VecLib::Vector a = *this;

    i_RANGE_0_TO_N(_size)
        a.at(i) /= k;
    
    return a;
}

e_type VecLib::Vector::module()
{
    e_type moduleValue = 0;

    for (auto i : *this)
        moduleValue += i*i;
    
    return sqrt(moduleValue);
}

e_type VecLib::Vector::elementsSum()
{
    e_type sumOfElements = 0;

    for (auto i : *this)
        sumOfElements += i;

    return sumOfElements;
}

e_type VecLib::Vector::elementsProd()
{
    e_type prodOfElements = 1;

    for (auto i : *this)
        prodOfElements *= i;

    return prodOfElements;
}

std::vector<ul> VecLib::Vector::maxsIndices()
{
    if (_size == 0) return std::vector<ul>(0);
    if (_size == 1) return std::vector<ul>{0};
    
    e_type maxValue = _elements[0];
    std::vector<ul> indicies;

    i_RANGE_0_TO_N(_size)
    {
        if (_elements[i] == maxValue) indicies.push_back(i);
        else if (_elements[i] > maxValue)
        {
            indicies.clear();
            indicies.push_back(i);
            maxValue = _elements[i];
        }
    }

    return indicies;
}

std::vector<ul> VecLib::Vector::minsIndices()
{
    if (_size == 0) return std::vector<ul>(0);
    if (_size == 1) return std::vector<ul>{0};
    
    e_type minValue = _elements[0];
    std::vector<ul> indicies;

    i_RANGE_0_TO_N(_size)
    {
        if (_elements[i] == minValue) indicies.push_back(i);
        else if (_elements[i] < minValue)
        {
            indicies.clear();
            indicies.push_back(i);
            minValue = _elements[i];
        }
    }

    return indicies;
}

e_type VecLib::Vector::scalarProd(VecLib::Vector a)
{
    SIZE_CHECK(*this, a);

    e_type prod = 0;

    i_RANGE_0_TO_N(_size)
        prod += a.at(i) * this->at(i);
    
    return prod;
}

std::string dtos(e_type val, int prec)
{
    return std::to_string(val)
    .substr(0,std::to_string(val)
                       .find(".") + prec + 1);
}

VecLib::Vector VecLib::vectorProduct(std::vector<VecLib::Vector> vecs)
{
    int amount = vecs.size();
    for (auto& i : vecs)
        if (i.size() != amount + 1) throw "illegal size for vector product";

    VecLib::Vector result("result", amount + 1, 0.);

    std::vector<std::vector<std::vector<e_type>>> determinants;
    determinants.resize(amount + 1);

    for (auto& i : determinants)
    {
        i.resize(amount);
        for (auto& j : i)
            j.resize(amount);
    }

    for (int c = 0; c < amount + 1; c++)
    {
        for (int i = 0; i < amount; i++)
            for (int j = 0; j < amount; j++)
                determinants[c][i][j] = vecs[i].at(j >= c ? j + 1 : j);
    }

    for (int i = 0; i < amount + 1; i++)
        result.at(i) = (i % 2 == 0 ? 1 : -1) * Matrix<>(determinants[i]).det();

    return result;
}

VecLib::Vector VecLib::Vector::AscSort()
{
    VecLib::Vector result = *this;

    std::vector<e_type> elems;
    for (auto& i: result)
    {
        elems.push_back(i);
    }

    std::sort(elems.begin(), elems.end(), std::less<e_type>());

    for (ul i = 0; i < _size; i++)
    {
        result._elements[i] = elems[i];
    }

    return result;
}

VecLib::Vector VecLib::Vector::DesSort()
{
    VecLib::Vector result = *this;

    std::vector<e_type> elems;
    for (auto& i: result)
    {
        elems.push_back(i);
    }

    std::sort(elems.begin(), elems.end(), std::greater<e_type>());

    for (ul i = 0; i < _size; i++)
    {
        result._elements[i] = elems[i];
    }

    return result;
}

VecLib::Vector VecLib::Vector::reverse()
{
    VecLib::Vector result = *this;

    for (ul i = 0; i < _size / 2; i++)
    {
        e_type tmp = result._elements[i];
        result._elements[i] = result._elements[_size - 1 - i];
        result._elements[_size - 1 - i] = tmp;
    }

    return result;
}
