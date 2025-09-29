#ifndef LINKIT_MATRIX4_H
#define LINKIT_MATRIX4_H
#include "precision.h"
#include "vector4.h"
#include "vector3.h"
#include <string>
#include <cmath> // For std::abs, sin, cos

namespace linkit
{
    class Matrix4
    {
    public:
        real m[4][4]{};

        Matrix4() {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = (i == j) ? 1.0 : 0.0; // Identity matrix
        }

        explicit Matrix4(const real mat[4][4]) {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = mat[i][j];
        }

        // Transformation matrices
        static Matrix4 translate(const Vector3& translation) {
            Matrix4 result; // Identity
            result.m[0][3] = translation.x;
            result.m[1][3] = translation.y;
            result.m[2][3] = translation.z;
            return result;
        }

        static Matrix4 scale(const Vector3& scale_vec) {
            Matrix4 result; // Identity
            result.m[0][0] = scale_vec.x;
            result.m[1][1] = scale_vec.y;
            result.m[2][2] = scale_vec.z;
            return result;
        }

        static Matrix4 rotate(real angle, const Vector3& axis) {
            Matrix4 result;
            Vector3 norm_axis = axis.normalized();
            const real x = norm_axis.x;
            const real y = norm_axis.y;
            const real z = norm_axis.z;
            const real c = real_cos(angle);
            const real s = real_sin(angle);
            const real omc = static_cast<real>(1.0) - c;

            result.m[0][0] = c + x * x * omc;
            result.m[0][1] = x * y * omc - z * s;
            result.m[0][2] = x * z * omc + y * s;

            result.m[1][0] = y * x * omc + z * s;
            result.m[1][1] = c + y * y * omc;
            result.m[1][2] = y * z * omc - x * s;

            result.m[2][0] = z * x * omc - y * s;
            result.m[2][1] = z * y * omc + x * s;
            result.m[2][2] = c + z * z * omc;

            return result;
        }

        // Matrix-Matrix multiplication
        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.m[i][j] = m[i][0] * other.m[0][j] +
                                     m[i][1] * other.m[1][j] +
                                     m[i][2] * other.m[2][j] +
                                     m[i][3] * other.m[3][j];
                }
            }
            return result;
        }

        void operator*=(const Matrix4& other) {
            *this = *this * other;
        }

        // Matrix-Vector multiplication
        Vector4 operator*(const Vector4 &other) const {
            return Vector4(
                m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3] * other.w,
                m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3] * other.w,
                m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3] * other.w,
                m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3] * other.w
            );
        }

        // Matrix-Scalar operations
        Matrix4 operator+(const real scalar) const {
            Matrix4 result;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    result.m[i][j] += scalar;
            return result;
        }

        void operator+=(const real scalar) {
            for (auto & i : m)
                for (real & j : i)
                    j += scalar;
        }

        Matrix4 operator-(const real scalar) const {
            Matrix4 result;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    result.m[i][j] -= scalar;
            return result;
        }

        void operator-=(const real scalar) {
            for (auto & i : m)
                for (real & j : i)
                    j -= scalar;
        }

        Matrix4 operator*(const real scalar) const {
            Matrix4 result;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    result.m[i][j] *= scalar;
            return result;
        }

        void operator*=(const real scalar) {
            for (auto & i : m)
                for (real & j : i)
                    j *= scalar;
        }

        Matrix4 operator/(const real scalar) const {
            Matrix4 result;
            if (std::abs(scalar) < REAL_EPSILON) return result; // Avoid division by zero
            real inv_scalar = static_cast<real>(1.0) / scalar;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    result.m[i][j] *= inv_scalar;
            return result;
        }

        void operator/=(const real scalar) {
            if (std::abs(scalar) < REAL_EPSILON) return; // Avoid division by zero
            real inv_scalar = static_cast<real>(1.0) / scalar;
            for (auto & i : m)
                for (real & j : i)
                    j *= inv_scalar;
        }

        // Comparison
        bool operator==(const Matrix4& other) const {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    if (std::abs(m[i][j] - other.m[i][j]) > REAL_EPSILON)
                        return false;
            return true;
        }

        bool operator!=(const Matrix4& other) const {
            return !(*this == other);
        }

        // Matrix operations
        [[nodiscard]] real determinant() const {
            return
                m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] -
                m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
                m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] -
                m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
                m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] -
                m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
                m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] -
                m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
                m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] -
                m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
                m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] -
                m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
        }

        void invert() {
            const real det = determinant();
            if (std::abs(det) < REAL_EPSILON) return; // Cannot invert

            const real inv_det = static_cast<real>(1.0) / det;
            Matrix4 result;

            result.m[0][0] = (m[1][2]*m[2][3]*m[3][1] - m[1][3]*m[2][2]*m[3][1] + m[1][3]*m[2][1]*m[3][2] - m[1][1]*m[2][3]*m[3][2] - m[1][2]*m[2][1]*m[3][3] + m[1][1]*m[2][2]*m[3][3]) * inv_det;
            result.m[0][1] = (m[0][3]*m[2][2]*m[3][1] - m[0][2]*m[2][3]*m[3][1] - m[0][3]*m[2][1]*m[3][2] + m[0][1]*m[2][3]*m[3][2] + m[0][2]*m[2][1]*m[3][3] - m[0][1]*m[2][2]*m[3][3]) * inv_det;
            result.m[0][2] = (m[0][2]*m[1][3]*m[3][1] - m[0][3]*m[1][2]*m[3][1] + m[0][3]*m[1][1]*m[3][2] - m[0][1]*m[1][3]*m[3][2] - m[0][2]*m[1][1]*m[3][3] + m[0][1]*m[1][2]*m[3][3]) * inv_det;
            result.m[0][3] = (m[0][3]*m[1][2]*m[2][1] - m[0][2]*m[1][3]*m[2][1] - m[0][3]*m[1][1]*m[2][2] + m[0][1]*m[1][3]*m[2][2] + m[0][2]*m[1][1]*m[2][3] - m[0][1]*m[1][2]*m[2][3]) * inv_det;
            result.m[1][0] = (m[1][3]*m[2][2]*m[3][0] - m[1][2]*m[2][3]*m[3][0] - m[1][3]*m[2][0]*m[3][2] + m[1][0]*m[2][3]*m[3][2] + m[1][2]*m[2][0]*m[3][3] - m[1][0]*m[2][2]*m[3][3]) * inv_det;
            result.m[1][1] = (m[0][2]*m[2][3]*m[3][0] - m[0][3]*m[2][2]*m[3][0] + m[0][3]*m[2][0]*m[3][2] - m[0][0]*m[2][3]*m[3][2] - m[0][2]*m[2][0]*m[3][3] + m[0][0]*m[2][2]*m[3][3]) * inv_det;
            result.m[1][2] = (m[0][3]*m[1][2]*m[3][0] - m[0][2]*m[1][3]*m[3][0] - m[0][3]*m[1][0]*m[3][2] + m[0][0]*m[1][3]*m[3][2] + m[0][2]*m[1][0]*m[3][3] - m[0][0]*m[1][2]*m[3][3]) * inv_det;
            result.m[1][3] = (m[0][2]*m[1][3]*m[2][0] - m[0][3]*m[1][2]*m[2][0] + m[0][3]*m[1][0]*m[2][2] - m[0][0]*m[1][3]*m[2][2] - m[0][2]*m[1][0]*m[2][3] + m[0][0]*m[1][2]*m[2][3]) * inv_det;
            result.m[2][0] = (m[1][1]*m[2][3]*m[3][0] - m[1][3]*m[2][1]*m[3][0] + m[1][3]*m[2][0]*m[3][1] - m[1][0]*m[2][3]*m[3][1] - m[1][1]*m[2][0]*m[3][3] + m[1][0]*m[2][1]*m[3][3]) * inv_det;
            result.m[2][1] = (m[0][3]*m[2][1]*m[3][0] - m[0][1]*m[2][3]*m[3][0] - m[0][3]*m[2][0]*m[3][1] + m[0][0]*m[2][3]*m[3][1] + m[0][1]*m[2][0]*m[3][3] - m[0][0]*m[2][1]*m[3][3]) * inv_det;
            result.m[2][2] = (m[0][1]*m[1][3]*m[3][0] - m[0][3]*m[1][1]*m[3][0] + m[0][3]*m[1][0]*m[3][1] - m[0][0]*m[1][3]*m[3][1] - m[0][1]*m[1][0]*m[3][3] + m[0][0]*m[1][1]*m[3][3]) * inv_det;
            result.m[2][3] = (m[0][3]*m[1][1]*m[2][0] - m[0][1]*m[1][3]*m[2][0] - m[0][3]*m[1][0]*m[2][1] + m[0][0]*m[1][3]*m[2][1] + m[0][1]*m[1][0]*m[2][3] - m[0][0]*m[1][1]*m[2][3]) * inv_det;
            result.m[3][0] = (m[1][2]*m[2][1]*m[3][0] - m[1][1]*m[2][2]*m[3][0] - m[1][2]*m[2][0]*m[3][1] + m[1][0]*m[2][2]*m[3][1] + m[1][1]*m[2][0]*m[3][2] - m[1][0]*m[2][1]*m[3][2]) * inv_det;
            result.m[3][1] = (m[0][1]*m[2][2]*m[3][0] - m[0][2]*m[2][1]*m[3][0] + m[0][2]*m[2][0]*m[3][1] - m[0][0]*m[2][2]*m[3][1] - m[0][1]*m[2][0]*m[3][2] + m[0][0]*m[2][1]*m[3][2]) * inv_det;
            result.m[3][2] = (m[0][2]*m[1][1]*m[3][0] - m[0][1]*m[1][2]*m[3][0] - m[0][2]*m[1][0]*m[3][1] + m[0][0]*m[1][2]*m[3][1] + m[0][1]*m[1][0]*m[3][2] - m[0][0]*m[1][1]*m[3][2]) * inv_det;
            result.m[3][3] = (m[0][1]*m[1][2]*m[2][0] - m[0][2]*m[1][1]*m[2][0] + m[0][2]*m[1][0]*m[2][1] - m[0][0]*m[1][2]*m[2][1] - m[0][1]*m[1][0]*m[2][2] + m[0][0]*m[1][1]*m[2][2]) * inv_det;

            *this = result;
        }

        [[nodiscard]] Matrix4 inverse() const {
            Matrix4 result = *this;
            result.invert();
            return result;
        }

        void transpose() {
            real temp;
            for (int i = 0; i < 4; ++i) {
                for (int j = i + 1; j < 4; ++j) {
                    temp = m[i][j];
                    m[i][j] = m[j][i];
                    m[j][i] = temp;
                }
            }
        }

        [[nodiscard]] Matrix4 transposed() const {
            Matrix4 result = *this;
            result.transpose();
            return result;
        }

        [[nodiscard]] std::string to_string() const {
            std::string s = "[\n";
            for (int i = 0; i < 4; ++i) {
                s += "  [" + std::to_string(m[i][0]) + ", " + std::to_string(m[i][1]) + ", " + std::to_string(m[i][2]) + ", " + std::to_string(m[i][3]) + "]\n";
            }
            s += "]";
            return s;
        }
    };

    // Bidirectional scalar operations
    inline Matrix4 operator+(const real scalar, const Matrix4& matrix) {
        return matrix + scalar;
    }

    inline Matrix4 operator-(const real scalar, const Matrix4& matrix) {
        Matrix4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.m[i][j] = scalar - matrix.m[i][j];
        return result;
    }

    inline Matrix4 operator*(const real scalar, const Matrix4& matrix) {
        return matrix * scalar;
    }
}

#endif //LINKIT_MATRIX4_H