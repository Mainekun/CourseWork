#include "vector.h"

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

VecLib::Vector VecLib::Vector::operator*(double k)
{
    VecLib::Vector a = *this;

    i_RANGE_0_TO_N(_size)
        a.at(i) *= k;
    
    return a;
}

VecLib::Vector VecLib::Vector::operator/(double k)
{
    if (k == 0) 
        return VecLib::Vector("", _size);

    VecLib::Vector a = *this;

    i_RANGE_0_TO_N(_size)
        a.at(i) /= k;
    
    return a;
}

double VecLib::Vector::module()
{
    double moduleValue = 0;

    for (auto i : *this)
        moduleValue += i*i;
    
    return sqrt(moduleValue);
}

double VecLib::Vector::elementsSum()
{
    double sumOfElements = 0;

    for (auto i : *this)
        sumOfElements += i;

    return sumOfElements;
}

double VecLib::Vector::elementsProd()
{
    double prodOfElements = 1;

    for (auto i : *this)
        prodOfElements *= i;

    return prodOfElements;
}

std::vector<ul> VecLib::Vector::maxsIndices()
{
    if (_size == 0) return std::vector<ul>(0);
    if (_size == 1) return std::vector<ul>{0};
    
    double maxValue = _elements[0];
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
    
    double minValue = _elements[0];
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

double VecLib::Vector::scalarProd(VecLib::Vector a)
{
    SIZE_CHECK(*this, a);

    double prod = 0;

    i_RANGE_0_TO_N(_size)
        prod += a.at(i) * this->at(i);
    
    return prod;
}

std::string dtos(double val, int prec)
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

    std::vector<std::vector<std::vector<double>>> determinants;
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

