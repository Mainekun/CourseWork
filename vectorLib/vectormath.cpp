#include "vector.h"

Vector Vector::operator-()
{
    Vector negated = *this;

    for (auto& i : negated) i *= -1;

    return negated;
}

Vector Vector::operator+(Vector& a)
{
    SIZE_CHECK(*this, a);
    
    Vector b("", _size);

    i_RANGE_0_TO_N(_size) 
        b.at(i) = this->at(i) + a.at(i);

    return b;
}

Vector Vector::operator-(Vector& a)
{
    SIZE_CHECK(*this, a);
    
    Vector b("", _size);

    i_RANGE_0_TO_N(_size) 
        b.at(i) = this->at(i) - a.at(i);

    return b;
}

Vector Vector::operator*(double k)
{
    Vector a = *this;

    i_RANGE_0_TO_N(_size)
        a.at(i) *= k;
    
    return a;
}

Vector Vector::operator/(double k)
{
    if (k == 0) 
        return Vector("", _size);

    Vector a = *this;

    i_RANGE_0_TO_N(_size)
        a.at(i) /= k;
    
    return a;
}

double Vector::module()
{
    double moduleValue = 0;

    for (auto i : *this)
        moduleValue += i*i;
    
    return sqrt(moduleValue);
}

double Vector::elementsSum()
{
    double sumOfElements = 0;

    for (auto i : *this)
        sumOfElements += i;

    return sumOfElements;
}

double Vector::elementsProd()
{
    double prodOfElements = 1;

    for (auto i : *this)
        prodOfElements *= i;

    return prodOfElements;
}

std::vector<ul> Vector::maxsIndices()
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

std::vector<ul> Vector::minsIndices()
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

double Vector::scalarProd(Vector& a)
{
    SIZE_CHECK(*this, a);

    double prod = 0;

    i_RANGE_0_TO_N(_size)
        prod += a.at(i) * this->at(i);
    
    return prod;
}

Vector Vector::vectorProd(Vector& a)
{
    SIZE_CHECK(*this, a);
    if (_size != 3) throw VectorProductException();

    Vector b("", 3, 0.);

    b.at(0) = this->at(1) * a.at(2) - this->at(2) * a.at(1);
    b.at(1) = this->at(2) * a.at(0) - this->at(0) * a.at(2);
    b.at(2) = this->at(0) * a.at(1) - this->at(1) * a.at(0);
    
    return b;
}

std::string dtos(double val, int prec)
{
    return std::to_string(val)
    .substr(0,std::to_string(val)
                       .find(".") + prec + 1);
}

Vector vectorProduct(std::vector<Vector>& vecs)
{
    int amount = vecs.size();
    for (auto& i : vecs)
        if (i.size() != amount + 1) throw "illegal size for vector product";

    Vector result("result", amount + 1, 0.);

    std::vector<std::vector<std::vector<double>>> determinants;

    for (int c = 0; c < amount + 1; c++)
    {
        for (int i = 0; i < amount; i++)
            for (int j = 0; j < amount + 1; j++)
                determinants[c][i][j] = vecs[i][j >= c ? j + 1 : j];
    }
    //???


    //determenant calculated with temp matrix
}

double detEval(int row, std::vector<std::vector<std::vector<double>>>& matrices)
{
    int amount  = matrices[i].size(),
        vec_size = amount + 1;


}

