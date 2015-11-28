#pragma once

using uint = unsigned int;
using Scalar = float;

#include <vector>
#include <assert.h>

class Matrix {
    uint _rows = 0;
    uint _cols = 0;
    std::vector<Scalar> _v;
public:
    Matrix() = default;

    Matrix(uint rows, uint cols)
        : _rows(rows), _cols(cols)
        , _v(rows * cols)
    {}
public:
    uint rows() const { return _rows; }
    uint cols() const { return _cols; }

    Scalar at(uint i, uint j) const
    {
        assert(i < _rows && j < _cols);
        return _v[i * _cols + j];
    }

    Scalar& at(uint i, uint j)
    {
        assert(i < _rows && j < _cols);
        return _v[i * _cols + j];
    }

    Matrix operator*(const Matrix& b) const
    {
        assert(_cols == b._rows);

        Matrix c(_rows, b._cols);
        for (uint i = 0; i < c.rows(); ++i)
            for (uint j = 0; j < c.cols(); ++j)
                for (uint k = 0; k < _cols; ++k)
                    c.at(i, j) += at(i, k) * b.at(k, j);
        return c;
    }

    Matrix operator*(const Scalar b) const
    {
        Matrix c(_rows, _cols);
        for (int i = 0; i < _v.size(); ++i)
            c._v[i] = b * _v[i];
        return c;
    }

    Matrix operator+(const Matrix& b) const
    {
        assert(_rows == b._rows && _cols == b._cols);

        Matrix c(_rows, _cols);
        for (uint i = 0; i < _v.size(); ++i)
            c._v[i] = _v[i] + b._v[i];
        return c;
    }

    Matrix operator-(const Matrix& b) const
    {
        assert(_rows == b._rows && _cols == b._cols);

        Matrix c(_rows, _cols);
        for (uint i = 0; i < _v.size(); ++i)
            c._v[i] = _v[i] - b._v[i];
        return c;
    }

    Matrix transpose() const
    {
        Matrix c(_cols, _rows);
        for (uint i = 0; i < _cols; ++i)
            for (uint j = 0; j < _rows; ++j)
                c.at(i, j) = at(j, i);
        return c;
    }

    template <class F>
    Matrix map(F func) const
    {
        Matrix c(_rows, _cols);
        for (uint i = 0; i < _rows; ++i)
            for (uint j = 0; j < _cols; ++j)
                c.at(i, j) = func(at(i, j));
        return c;
    }
};

Matrix operator*(const Scalar a, const Matrix& b)
{
    return b * a;
}

class Vector {
    uint _rows = 0;
    std::vector<Scalar> _v;
public:
    Vector() = default;

    Vector(uint rows)
        : _rows(rows)
        , _v(rows)
    {}

    Vector(std::vector<Scalar>&& v)
        : _rows(v.size())
        , _v(std::move(v))
    {}

public:
    uint rows() const { return _rows; }

    Scalar at(uint i) const
    {
        assert(i < _rows);
        return _v[i];
    }
    Scalar& at(uint i)
    {
        assert (i < _rows);
        return _v[i];
    }

    Vector operator*(const Scalar b) const
    {
        Vector c(_rows);
        for (uint i = 0; i < _rows; ++i)
            c.at(i) = at(i) * b;
        return c;
    }

    Vector operator+(const Vector& b) const
    {
        Vector c(_rows);
        for (uint i = 0; i < _rows; ++i)
            c.at(i) = at(i) + b.at(i);
        return c;
    }

    Vector operator-(const Vector& b) const
    {
        Vector c(_rows);
        for (uint i = 0; i < _rows; ++i)
            c.at(i) = at(i) - b.at(i);
        return c;
    }

    Matrix transpose() const
    {
        Matrix c(1, _rows);
        for (uint i = 0; i < _rows; ++i)
            c.at(0, i) = at(i);
        return c;
    }

    template <class F>
    Vector map(F func) const
    {
        Vector c(_rows);
        for (uint i = 0; i < _rows; ++i)
            c.at(i) = func(at(i));
        return c;
    }
};

Vector operator*(const Scalar a, const Vector& b)
{
    return b * a;
}

Vector operator*(const Matrix& a, const Vector& b)
{
    Vector c(a.rows());
    for (uint i = 0; i < a.rows(); ++i)
        for (uint j = 0; j < a.cols(); ++j)
            c.at(i) += a.at(i, j) * b.at(j);
    return c;
}

Matrix operator+(const Matrix& a, const Vector& b)
{
    assert(a.rows() == b.rows());

    Matrix c(a.rows(), a.cols());
    for (uint i = 0; i < a.rows(); ++i)
        for (uint j = 0; j < a.cols(); ++j)
            c.at(i, j) = a.at(i, j) + b.at(i);
    return c;
}

Vector hadamard_product(const Vector& a, const Vector& b)
{
    assert(a.rows() == b.rows());

    Vector c(a.rows());
    for (uint i = 0; i < a.rows(); ++i)
        c.at(i) = a.at(i) * b.at(i);
    return c;
}

Matrix hadamard_product(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows() && a.cols() == b.cols());

    Matrix c(a.rows(), a.cols());
    for (uint i = 0; i < a.rows(); ++i)
        for (uint j = 0; j < a.cols(); ++j)
            c.at(i, j) = a.at(i, j) * b.at(i, j);
    return c;
}

Vector sum_columns(const Matrix& a)
{
    Vector c(a.rows());
    for (uint i = 0; i < a.rows(); ++i)
        for (uint j = 0; j < a.cols(); ++j)
            c.at(i) += a.at(i, j);
    return c;
}
