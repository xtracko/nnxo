#pragma once

#include "math.hpp"
#include <cmath>
#include <algorithm>

struct Fast_sigmoid {
    static Scalar root(const Scalar x)
    {
        return x / (1 + std::abs(x));
    }

    static Scalar derivative(const Scalar x)
    {
        const Scalar tmp = 1 + std::abs(x);
        return Scalar(1) / (tmp * tmp);
    }
};
/*
struct Rectified_linear {
    static Scalar root(const Scalar x)
    {
        return std::max(0, x);
    }

    static Scalar derivative(const Scalar x)
    {
        return ;
    }
};
*/
template <class Func>
struct Quadratic_cost {
    static double fn(Vector a, Vector y)
    {
        const double tmp = (a - y).norm();
        return 0.5 * tmp * tmp;
    }

    static Matrix delta(Matrix z, Matrix a, Matrix y)
    {
        return hadamard_product(a - y, z.map(Func::derivative));
    }
};
