#ifndef LINKIT_QUATERNION_H
#define LINKIT_QUATERNION_H

#include "precision.h"
#include "vector4.h"
#include "vector3.h"
#include <string>
#include <cmath> // For std::abs, sin, cos

namespace linkit
{
    class Quaternion
    {
        public:
            real w, x, y, z;
            Quaternion() : w(1), x(0), y(0), z(0) {};
            Quaternion(const real w, const real x, const real y, const real z): w(w), x(x), y(y), z(z) {};
            Quaternion(real angle, Vector3 axis)
            {
                axis.normalize();
                angle /= 2;
                w = real_cos(angle);
                x = axis.x * real_sin(angle);
                y = axis.y * real_sin(angle);
                z = axis.z * real_sin(angle);
            }


            Quaternion operator* (const Quaternion &other) const
            {
                return Quaternion(
                    w*other.w - x*other.x - y*other.y - z*other.z,
                    w*other.x + x*other.w + y*other.z - z*other.y,
                    w*other.y - x*other.z + y*other.w + z*other.x,
                    w*other.z + x*other.y - y*other.x + z*other.w
                );
            }




            void normalize()
            {
                const real mag_sq = w*w + x*x + y*y + z*z;
                if (mag_sq > 0)
                {
                    const real mag = real_sqrt(mag_sq);
                    w/=mag;
                    x/=mag;
                    y/=mag;
                    z/=mag;
                }
                else
                {
                    w = 1; // Reset to identity if it's a zero quaternion
                }
            }

            void add_scaled_vector(const Vector3& vec, real scale)
            {
                Quaternion q(0, vec.x * scale, vec.y * scale, vec.z * scale);
                q *= *this;
                w += q.w * 0.5;
                x += q.x * 0.5;
                y += q.y * 0.5;
                z += q.z * 0.5;
            }




            [[nodiscard]] real angle_radians() const
            {
                return static_cast<real>(2 * acos(w));
            }

            [[nodiscard]] Vector3 axis() const
            {
                real sin_theta_sq = 1.0 - w*w;
                if (sin_theta_sq <= 0.0)
                {
                    return Vector3(0, 0, 1); // Arbitrary axis for no rotation
                }
                real one_over_sin_theta = 1.0 / real_sqrt(sin_theta_sq);
                return Vector3(x * one_over_sin_theta, y * one_over_sin_theta, z * one_over_sin_theta);
            }

            [[nodiscard]] std::string to_string() const
            {
                return "(" + std::to_string(w) + " + " + std::to_string(x) + "i + " + std::to_string(y) + "j + " + std::to_string(z) + "k)";
            }

            [[nodiscard]] std::string angle_axis_string() const
            {
                return "Angle: " + std::to_string(angle_radians()) + ", Axis: " + axis().to_string();
            }

        void operator*=(const Quaternion &other)
        {
            *this = *this * other;
        }


    };
}

#endif //LINKIT_QUATERNION_H