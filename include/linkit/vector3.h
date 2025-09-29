#ifndef LINKIT_VECTOR3_H
#define LINKIT_VECTOR3_H
#include "precision.h"
#include "vector4.h"

namespace linkit
{
    class Vector3
    {
        private:
            real _padding; // Padding to ensure 16-byte alignment
        public:
            Vector3():
                x(0),
                y(0),
                z(0)
            {
            }
            Vector3(const real x, const real y, const real z)
                : x(x),
                  y(y),
                  z(z)
            {
            }

            real x;
            real y;
            real z;



        [[nodiscard]] real magnitude_squared() const
        {
            return x*x + y*y + z*z;
        }

        [[nodiscard]] real magnitude() const
        {
            return real_sqrt(x*x + y*y + z*z);
        }

        void normalize()
        {
            const real mag = magnitude();
            if (mag > 0)
            {
                (*this) /= mag;
            }
        }

        [[nodiscard]] Vector3 normalized() const
        {
            Vector3 result = *this;
            result.normalize();
            return result;
        }

        void invert()
        {
            (*this) *= -1;
        }


        Vector3 operator+ (const Vector3 &vec) const
        {
            return Vector3(x + vec.x, y + vec.y, z + vec.z);
        }

        Vector3 operator+ (const real scalar) const
        {
            return Vector3(x + scalar, y + scalar, z + scalar);
        }

        void operator+= (const Vector3 &vec)
        {
            x += vec.x;
            y += vec.y;
            z += vec.z;
        }

        void operator+= (const real scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
        }


        Vector3 operator- (const Vector3 &vec) const
        {
            return Vector3(x - vec.x, y - vec.y, z - vec.z);
        }

        Vector3 operator- (const real scalar) const
        {
            return Vector3(x - scalar, y - scalar, z - scalar);
        }

        void operator-= (const Vector3 &vec)
        {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
        }

        void operator-= (const real scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
        }


        // Dot product
        real operator* (const Vector3 &vec) const
        {
            return vec.x * x + vec.y * y + vec.z * z;
        }

        Vector3 operator* (const real scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        void operator*= (const real scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
        }

        Vector3 operator/ (const real scalar) const
        {
            return  Vector3(x / scalar, y / scalar, z / scalar);
        }

        void operator/= (const real scalar)
        {
            if (std::abs(scalar) < REAL_EPSILON) {
                return; // Avoid division by zero
            }
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }

        // vector "cross" product
        Vector3 operator% (const Vector3 &vec) const
        {
            return Vector3(
                y * vec.z - z * vec.y,
                z * vec.x - x * vec.z,
                x * vec.y - y * vec.x
                );
        }
        void operator%= (const Vector3 &vec)
        {
            x = vec.z * y - vec.y * z;
            y = vec.x * z - vec.z * x;
            z = vec.y * x - vec.x * y;
        }


        bool operator==(const Vector3 &vec) const
        {
            return vec.x == x && vec.y == y && vec.z == z;
        }

        bool operator!=(const Vector3 &vec) const
        {
            return !(*this == vec);
        }


        [[nodiscard]] std::string to_string() const
        {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        }



    };

    inline Vector3 operator+(const real scalar, const Vector3& vec) {
        return vec + scalar;  // Reuse the existing member operator
    }

    inline Vector3 operator-(const real scalar, const Vector3& vec) {
        return vec - scalar;  // Reuse the existing member operator
    }

    inline Vector3 operator*(const real scalar, const Vector3& vec) {
        return vec * scalar;  // Reuse the existing member operator
    }

    inline Vector3 operator/(const real scalar, const Vector3& vec) {
        return vec / scalar;  // Reuse the existing member operator
    }

}

#endif //LINKIT_VECTOR3_H