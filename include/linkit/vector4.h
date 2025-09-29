#ifndef LINKIT_VECTOR4_H
#define LINKIT_VECTOR4_H
#include "precision.h"
#include "vector3.h"

#include <string>

namespace linkit
{
    class Vector4
    {
    public:
        real x;
        real y;
        real z;
        real w;

        Vector4():
            x(0),
            y(0),
            z(0),
            w(0)
        {
        }
        Vector4(const real x, const real y, const real z, const real w)
            : x(x),
              y(y),
              z(z),
              w(w)
        {
        }

        [[nodiscard]] real magnitude_squared() const
        {
            return x*x + y*y + z*z + w*w;
        }

        [[nodiscard]] real magnitude() const
        {
            return real_sqrt(x*x + y*y + z*z + w*w);
        }

        void normalize()
        {
            const real mag = magnitude();
            if (mag > 0)
            {
                (*this) /= mag;
            }
        }

        [[nodiscard]] Vector4 normalized() const
        {
            Vector4 result = *this;
            result.normalize();
            return result;
        }

        void invert()
        {
            (*this) *= -1;
        }


        Vector4 operator+ (const Vector4 &vec) const
        {
            return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
        }

        Vector4 operator+ (const real scalar) const
        {
            return Vector4(x + scalar, y + scalar, z + scalar, w + scalar);
        }

        void operator+= (const Vector4 &vec)
        {
            x += vec.x;
            y += vec.y;
            z += vec.z;
            w += vec.w;
        }

        void operator+= (const real scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            w += scalar;
        }


        Vector4 operator- (const Vector4 &vec) const
        {
            return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
        }

        Vector4 operator- (const real scalar) const
        {
            return Vector4(x - scalar, y - scalar, z - scalar, w - scalar);
        }

        void operator-= (const Vector4 &vec)
        {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
            w -= vec.w;
        }

        void operator-= (const real scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            w -= scalar;
        }


        // Dot product
        real operator* (const Vector4 &vec) const
        {
            return vec.x * x + vec.y * y + vec.z * z + vec.w * w;
        }

        Vector4 operator* (const real scalar) const
        {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        void operator*= (const real scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
        }

        Vector4 operator/ (const real scalar) const
        {
            return  Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

        void operator/= (const real scalar)
        {
            if (std::abs(scalar) < REAL_EPSILON) return;
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
        }

        bool operator==(const Vector4 &vec) const
        {
            return vec.x == x && vec.y == y && vec.z == z && vec.w == w;
        }

        bool operator!=(const Vector4 &vec) const
        {
            return !(*this == vec);
        }



        [[nodiscard]] std::string to_string() const
        {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
        }
    };

    inline Vector4 operator+(const real scalar, const Vector4& vec) {
        return vec + scalar;
    }

    inline Vector4 operator-(const real scalar, const Vector4& vec) {
        return vec - scalar;
    }

    inline Vector4 operator*(const real scalar, const Vector4& vec) {
        return vec * scalar;
    }

    inline Vector4 operator/(const real scalar, const Vector4& vec) {
        return vec / scalar;
    }
}
#endif //LINKIT_VECTOR4_H