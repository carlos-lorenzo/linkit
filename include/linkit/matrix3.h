#ifndef LINKIT_MATRIX3_H
#define LINKIT_MATRIX3_H
#include "precision.h"
#include "vector3.h"
#include <string>
#include <cmath> // For std::abs, sin, cos

namespace linkit
{
    class Matrix3
    {
    public:
        real m[3][3]{};

        Matrix3() {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    m[i][j] = (i == j) ? 1.0 : 0.0; // Identity matrix
        }

        explicit Matrix3(const real mat[3][3]) {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    m[i][j] = mat[i][j];
        }

        // Transformation matrices
        static Matrix3 scale(const Vector3& scale_vec) {
            Matrix3 result; // Identity
            result.m[0][0] = scale_vec.x;
            result.m[1][1] = scale_vec.y;
            result.m[2][2] = scale_vec.z;
            return result;
        }

        static Matrix3 rotate(const real angle, const Vector3& axis) {
            Matrix3 result;
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
        Matrix3 operator*(const Matrix3& other) const {
            Matrix3 result;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    result.m[i][j] = m[i][0] * other.m[0][j] +
                                     m[i][1] * other.m[1][j] +
                                     m[i][2] * other.m[2][j];
                }
            }
            return result;
        }

        void operator*=(const Matrix3& other) {
            *this = *this * other;
        }

        // Matrix-Vector multiplication
        Vector3 operator*(const Vector3 &other) const {
            return Vector3(
                m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z,
                m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z,
                m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z
            );
        }

        // Matrix-Scalar operations
        Matrix3 operator+(const real scalar) const {
            Matrix3 result;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    result.m[i][j] = m[i][j] + scalar;
            return result;
        }

        void operator+=(const real scalar) {
            for (auto & i : m)
                for (real & j : i)
                    j += scalar;
        }

        Matrix3 operator-(const real scalar) const {
            Matrix3 result;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    result.m[i][j] = m[i][j] - scalar;
            return result;
        }

        void operator-=(const real scalar) {
            for (auto & i : m)
                for (real & j : i)
                    j -= scalar;
        }

        Matrix3 operator*(const real scalar) const {
            Matrix3 result;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    result.m[i][j] = m[i][j] * scalar;
            return result;
        }

        void operator*=(const real scalar) {
            for (auto & i : m)
                for (real & j : i)
                    j *= scalar;
        }

        Matrix3 operator/(const real scalar) const {
            Matrix3 result;
            if (scalar == 0) return result; // Avoid division by zero
            const real inv_scalar = static_cast<real>(1.0) / scalar;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    result.m[i][j] = m[i][j] * inv_scalar;
            return result;
        }

        void operator/=(const real scalar) {
            if (scalar == 0) return; // Avoid division by zero
            real inv_scalar = 1.0 / scalar;
            for (auto & i : m)
                for (real & j : i)
                    j *= inv_scalar;
        }

        // Comparison
        bool operator==(const Matrix3& other) const {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (std::abs(m[i][j] - other.m[i][j]) > REAL_EPSILON)
                        return false;
            return true;
        }

        bool operator!=(const Matrix3& other) const {
            return !(*this == other);
        }

        // Matrix operations
        [[nodiscard]] real determinant() const {
            return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                   m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                   m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        }

        void invert() {
            const real det = determinant();
            if (std::abs(det) < REAL_EPSILON) return; // Cannot invert

            real inv_det = 1.0 / det;
            Matrix3 result;

            result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * inv_det;
            result.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * inv_det;
            result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * inv_det;
            result.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * inv_det;
            result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * inv_det;
            result.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * inv_det;
            result.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * inv_det;
            result.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * inv_det;
            result.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * inv_det;

            *this = result;
        }

        [[nodiscard]] Matrix3 inverse() const {
            Matrix3 result = *this;
            result.invert();
            return result;
        }

        void transpose() {
            real temp;
            temp = m[0][1]; m[0][1] = m[1][0]; m[1][0] = temp;
            temp = m[0][2]; m[0][2] = m[2][0]; m[2][0] = temp;
            temp = m[1][2]; m[1][2] = m[2][1]; m[2][1] = temp;
        }

        [[nodiscard]] Matrix3 transposed() const {
            Matrix3 result = *this;
            result.transpose();
            return result;
        }

        [[nodiscard]] std::string to_string() const {
            std::string s = "[\n";
            for (const auto & i : m) {
                s += "  [" + std::to_string(i[0]) + ", " + std::to_string(i[1]) + ", " + std::to_string(i[2]) + "]\n";
            }
            s += "]";
            return s;
        }

        static Matrix3 matrix_from_columns(const Vector3& col1, const Vector3& col2, const Vector3& col3) {
            Matrix3 result;
            result.m[0][0] = col1.x; result.m[0][1] = col2.x; result.m[0][2] = col3.x;
            result.m[1][0] = col1.y; result.m[1][1] = col2.y; result.m[1][2] = col3.y;
            result.m[2][0] = col1.z; result.m[2][1] = col2.z; result.m[2][2] = col3.z;
            return result;
        }

        static Matrix3 matrix_from_rows(const Vector3& row1, const Vector3& row2, const Vector3& row3) {
            Matrix3 result;
            result.m[0][0] = row1.x; result.m[0][1] = row1.y; result.m[0][2] = row1.z;
            result.m[1][0] = row2.x; result.m[1][1] = row2.y; result.m[1][2] = row2.z;
            result.m[2][0] = row3.x; result.m[2][1] = row3.y; result.m[2][2] = row3.z;
            return result;
        }

        // Changes from current basis to new_base. Useful when converting from world to local space
        [[nodiscard]] Matrix3 changed_base(const Matrix3 new_base) const {
            return new_base.inverse() * (*this) * new_base;
        }

        // Optimisation for changed_base.inverse(). Useful when converting from local to world space
        [[nodiscard]] Matrix3 inverted_changed_base(const Matrix3 new_base) const {
            return new_base * (*this) * new_base.inverse();
        }
    };

    // Bidirectional scalar operations
    inline Matrix3 operator+(const real scalar, const Matrix3& matrix) {
        return matrix + scalar;
    }

    inline Matrix3 operator-(const real scalar, const Matrix3& matrix) {
        Matrix3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = scalar - matrix.m[i][j];
        return result;
    }

    inline Matrix3 operator*(const real scalar, const Matrix3& matrix) {
        return matrix * scalar;
    }


}

#endif //LINKIT_MATRIX3_H