#pragma once

#include "math.hpp"
#include "network.hpp"
#include <ostream>
#include <istream>
#include <cstring>

template<class E, class T, int N>
std::basic_istream<E,T>& operator>>(std::basic_istream<E,T>& in, const E(&sliteral)[N]) {
        E buffer[N-1] = {}; //get buffer
        in >> buffer[0]; //skips whitespace
        if (N>2)
                in.read(buffer+1, N-2); //read the rest
        if (std::strncmp(buffer, sliteral, N-1)) //if it failed
                in.setstate(std::ios::failbit); //set the state
        return in;
}

std::ostream& operator<<(std::ostream& os, const Vector& b)
{
    os << "vector(" << b.rows() << ") [";
    for (uint i = 0; i < b.rows(); ++i)
        os << b.at(i) << " ";
    return os << "\b]";
}

std::ostream& operator<<(std::ostream& os, const Matrix& b)
{
    os << "matrix (" << b.rows() << " " << b.cols() << ") [";
    for (uint i = 0; i < b.rows(); ++i) {
        os << "[";
        for (uint j = 0; j < b.cols(); ++j)
            os << b.at(i, j) << " ";
        os << "\b]";
    }
    return os << "]";
}

std::istream& operator>>(std::istream& is, Vector& b)
{
    uint rows = 0;

    is >> "vector(" >> rows >> ") [";

    b = Vector(rows);
    for (uint i = 0; i < rows; ++i)
        is >> b.at(i);
    return is >> "]";
}

std::istream& operator>>(std::istream& is, Matrix& b)
{
    uint rows = 0;
    uint cols = 0;

    is >> "matrix(" >> rows >> cols >> ") [";

    b = Matrix(rows, cols);
    for (uint i = 0; i < rows; ++i) {
        is >> "[";
        for (uint j = 0; j < cols; ++j)
            is >> b.at(i, j);
        is >> "]";
    }
    return is >> "]";
}
/*
std::ostream& operator<<(std::ostream& os, const Layer& layer)
{
    os << "biases: " << layer.b << std::endl;
    return os << "weights: " << layer.w << std::endl;
}

std::istream& operator>>(std::istream& is, Layer& layer)
{
    is >> "biases: " >> layer.b >> "\n";
    return is >> "weights: " >> layer.w >> "\n";
}
*/
