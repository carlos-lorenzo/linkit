#ifndef LINKIT_PRECISION_H
#define LINKIT_PRECISION_H
#include <cmath>

namespace linkit
{
    typedef float real;
    constexpr real REAL_EPSILON = 1e-6;

    inline real real_sqrt(const real num)
    {
        return std::sqrt(num);
    }

    inline real real_pow(const real base, const real exp)
    {
        return std::pow(base, exp);
    }

    inline real real_sin(const real angle)
    {
        return std::sin(angle);
    }

    inline real real_cos(const real angle)
    {
        return std::cos(angle);
    }

}

#endif //LINKIT_PRECISION_H