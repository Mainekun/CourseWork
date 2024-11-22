#ifndef MATRIX_H
#define MATRIX_H

#include <ctype.h>
#include <vector>

template<typename T = double>
    requires std::is_arithmetic<T>::value
class Matrix
{
    T **matrix;
    int size;

    void init()
    {
        matrix = new T *[size];
        for (int i = 0; i < size; i++)
            matrix[i] = new T[size];
    }
    void vectorCheck(std::vector<std::vector<T>> &vMatrix)
    {
        if (vMatrix.empty())
            throw "empty vectors";

        int amount = vMatrix.size();
        for (auto &i : vMatrix)
            if (amount != i.size())
                throw "vectors do not form square matrix";
    }
    void rangeCheck(int row, int col)
    {
        if (row < 0 || row >= size)
            throw "row is out of range";
        if (col < 0 || col >= size)
            throw "col is out of range";
    }

public:
    Matrix() = delete;
    Matrix(std::vector<std::vector<T>> vMatrix)
    {
        vectorCheck(vMatrix);
        size = vMatrix.size();
        init();

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrix[i][j] = vMatrix[i][j];
    }
    Matrix(T **matrix, int size)
    {
        this->size = size;
        init();
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                this->matrix[i][j] = matrix[i][j];
    }
    Matrix(int size)
    {
        this->size = size;
        init();
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                this->matrix[i][j] = 0;
    }
    ~Matrix()
    {
        for (int i = 0; i < size; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    T &at(int row, int col)
    {
        rangeCheck(row, col);
        return matrix[row][col];
    }

    Matrix cut(int row, int col)
    {
        rangeCheck(row, col);

        Matrix cutMatrix(size - 1);

        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - 1; j++)
                cutMatrix.at(i, j) = this->at(i >= row ? i + 1 : i, j >= col ? j + 1 : j);

        return cutMatrix;
    }

    T det()
    {
        if (size == 1)
            return matrix[0][0];

        if (size == 2)
            return this->at(0, 0) * this->at(1, 1) - this->at(1, 0) * this->at(0, 1);

        T result = 0;

        for (int i = 0; i < size; i++) {
            Matrix minorAddition = this->cut(0, i);
            result += this->at(0, i) * (i % 2 == 0 ? 1 : -1) * minorAddition.det();
        }

        return result;
    }
};
#endif // MATRIX_H
