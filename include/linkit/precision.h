//
// Created by carlos on 9/24/25.
//

#ifndef LINKIT_PRECISION_H
#define LINKIT_PRECISION_H
#include <cmath>

namespace linkit
{
    typedef float real;

    inline real real_sqrt(const real num)
    {
        return std::sqrt(num);
    }

    inline real real_pow(const real base, const real exp)
    {
        return std::pow(base, exp);
    }
}

#endif //LINKIT_PRECISION_H