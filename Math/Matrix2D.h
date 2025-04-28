//
// Created by natha on 2025-04-26.
//

#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <cmath>
#include <iostream>

#include "Vector2D.h"

namespace Math {
    struct Matrix2D {
        float m00, m01;
        float m10, m11;

        constexpr Matrix2D() = default;

        constexpr Matrix2D(float m00, float m01, float m10, float m11)
                : m00(m00), m01(m01), m10(m10), m11(m11) {}

        /**
         * Multiplies this matrix by another matrix.
         *
         * @param OtherMatrix The matrix to multiply with.
         * @return The product of the two matrices.
         */
        constexpr Matrix2D operator*(const Matrix2D &OtherMatrix) const {
            return Matrix2D(
                    m00 * OtherMatrix.m00 + m01 * OtherMatrix.m10,
                    m00 * OtherMatrix.m01 + m01 * OtherMatrix.m11,
                    m10 * OtherMatrix.m00 + m11 * OtherMatrix.m10,
                    m10 * OtherMatrix.m01 + m11 * OtherMatrix.m11
            );
        }

        /**
         * Multiplies this matrix by another matrix.
         *
         * @param OtherMatrix The matrix to multiply with.
         */
        inline void operator*=(const Matrix2D &OtherMatrix) {
            *this = *this * OtherMatrix;
        }

        /**
         * Multiplies this matrix by a vector.
         *
         * @param Vector The vector to multiply with.
         * @return The product of the matrix and the vector.
         */
        constexpr Vector2D operator*(const Vector2D &Vector) const {
            return Vector2D(
                    m00 * Vector.x + m01 * Vector.y,
                    m10 * Vector.x + m11 * Vector.y
            );
        }

        /**
         * Multiplies this matrix by a scalar.
         *
         * @param Scalar The scalar to multiply by.
         * @return The product of the matrix and the scalar.
         */
        constexpr Vector2D operator*(const float Scalar) const {
            return Vector2D(
                    m00 * Scalar,
                    m01 * Scalar
            );
        }

        /**
         * Returns the sum of this matrix and another matrix.
         *
         * @param OtherMatrix The matrix to add.
         * @return The sum of the two matrices.
         */
        constexpr Matrix2D operator+(const Matrix2D &OtherMatrix) const {
            return Matrix2D(
                    m00 + OtherMatrix.m00,
                    m01 + OtherMatrix.m01,
                    m10 + OtherMatrix.m10,
                    m11 + OtherMatrix.m11
            );
        }

        /**
         * Adds another matrix to this matrix.
         *
         * @param OtherMatrix The matrix to add.
         */
        inline void operator+=(const Matrix2D &OtherMatrix) {
            m00 += OtherMatrix.m00;
            m01 += OtherMatrix.m01;
            m10 += OtherMatrix.m10;
            m11 += OtherMatrix.m11;
        }

        /**
         * Returns the difference of this matrix and another matrix.
         *
         * @param OtherMatrix The matrix to subtract.
         * @return The difference of the two matrices.
         */
        constexpr Matrix2D operator-(const Matrix2D &OtherMatrix) const {
            return Matrix2D(
                    m00 - OtherMatrix.m00,
                    m01 - OtherMatrix.m01,
                    m10 - OtherMatrix.m10,
                    m11 - OtherMatrix.m11
            );
        }

        /**
         * Subtracts another matrix from this matrix.
         *
         * @param OtherMatrix The matrix to subtract.
         */
        inline void operator-=(const Matrix2D &OtherMatrix) {
            m00 -= OtherMatrix.m00;
            m01 -= OtherMatrix.m01;
            m10 -= OtherMatrix.m10;
            m11 -= OtherMatrix.m11;
        }

        /**
         * Divides this matrix by a scalar.
         *
         * @param Scalar The scalar to divide by.
         * @return The quotient of the matrix and the scalar.
         */
        constexpr Matrix2D operator/(const float Scalar) const {
            return Matrix2D(
                    m00 / Scalar,
                    m01 / Scalar,
                    m10 / Scalar,
                    m11 / Scalar
            );
        }

        /**
         * Divides this matrix by a scalar.
         *
         * @param Scalar The scalar to divide by.
         */
        inline void operator/=(const float Scalar) {
            m00 /= Scalar;
            m01 /= Scalar;
            m10 /= Scalar;
            m11 /= Scalar;
        }

        /**
         * Generates a 2D rotation matrix for a given angle in radians.
         *
         * @param RadAngle The angle of rotation in radians.
         * @return A 2x2 matrix representing the rotation.
         */
        static inline Matrix2D RotationRad(float RadAngle) {
            float Cos = std::cos(RadAngle);
            float Sin = std::sin(RadAngle);
            return Matrix2D(
                    Cos, -Sin,
                    Sin, Cos
            );
        }

        /**
         * Generates a 2D rotation matrix for a given angle in degrees.
         *
         * @param DegAngle The angle of rotation in degrees.
         * @return A 2x2 matrix representing the rotation.
         */
        static inline Matrix2D RotationDeg(float DegAngle) {
            return RotationRad(DegAngle * (M_PI / 180.0f));
        }

        /**
         * Creates a 2D identity matrix.
         *
         * @return A 2x2 identity matrix.
         */
        static constexpr Matrix2D Identity() {
            return Matrix2D(
                    1.0f, 0.0f,
                    0.0f, 1.0f
            );
        }

        /**
         * Creates a 2D zero matrix.
         *
         * @return A 2x2 zero matrix.
         */
        static constexpr Matrix2D Zero() {
            return Matrix2D(
                    0.0f, 0.0f,
                    0.0f, 0.0f
            );
        }

        /**
         * Calculates the determinant of the matrix.
         *
         * The determinant is calculated as:
         *          Det(A) = m00 * m11 - m01 * m10
         *
         * @return The determinant of the matrix.
         */
        inline float Determinant() const {
            return m00 * m11 - m01 * m10;
        }

        /**
         * Calculates the inverse of the matrix.
         *
         * The inverse is calculated as:
         *          Inv(A) = (1 / Det(A)) * adj(A)
         *
         * @return The inverse of the matrix.
         */
        inline Matrix2D Inverse() const {
            float Det = Determinant();
            if (Det == 0) {
                throw std::runtime_error("Matrix is singular and cannot be inverted.");
            }
            return Matrix2D(
                    m11 / Det, -m01 / Det,
                    -m10 / Det, m00 / Det
            );
        }

        /**
         * Transposes the matrix.
         *
         * The transpose is calculated as:
         *          Transpose(A) = A^T
         *
         * @return The transposed matrix.
         */
        constexpr Matrix2D Transpose() const {
            return Matrix2D(
                    m00, m10,
                    m01, m11
            );
        }

        /**
         * Check if the matrix is invertible.
         *
         * @return True if the matrix is invertible, false otherwise.
         */
        inline bool IsInvertible() const {
            return Determinant() != 0;
        }

        /**
         * Check if the matrix is a zero matrix.
         *
         * @return True if the matrix is a zero matrix, false otherwise.
         */
        inline bool IsZero(float epsilon = 1e-6f) const {
            return (std::fabs(m00) < epsilon &&
                    std::fabs(m01) < epsilon &&
                    std::fabs(m10) < epsilon &&
                    std::fabs(m11) < epsilon);
        }

        /**
         * Check if the matrix is an identity matrix.
         *
         * @return True if the matrix is an identity matrix, false otherwise.
         */
        inline bool IsIdentity(float epsilon = 1e-6f) const {
            return (std::fabs(m00 - 1.0f) < epsilon &&
                    std::fabs(m01 - 0.0f) < epsilon &&
                    std::fabs(m10 - 0.0f) < epsilon &&
                    std::fabs(m11 - 1.0f) < epsilon);
        }

        /**
         * Generates the adjoint of the matrix.
         *
         * The adjoint is calculated as:
         *          adj(A) = | m11  -m01 |
         *                   | -m10  m00 |
         *
         * @return The adjoint of the matrix.
         */
        inline Matrix2D Adjoint() const {
            return Matrix2D(
                    m11, -m01,
                    -m10, m00
            );
        }

        /**
         * Orthogonalizes the matrix.
         *
         * The orthogonalization process ensures that the columns of the matrix are orthogonal to each other.
         *
         * @return The orthogonalized matrix.
         */
        inline Matrix2D Orthogonalize() const {
            float length0 = std::sqrt(m00 * m00 + m10 * m10);
            float length1 = std::sqrt(m01 * m01 + m11 * m11);

            if (length0 == 0 || length1 == 0) {
                throw std::runtime_error("Matrix cannot be orthogonalized.");
            }

            return Matrix2D(
                    m00 / length0, m01 / length1,
                    m10 / length0, m11 / length1
            );
        }

        /**
         * Checks if the matrix is orthogonal.
         *
         * An orthogonal matrix satisfies the condition:
         *          A^T * A = I
         *
         * @return True if the matrix is orthogonal, false otherwise.
         */
        inline bool IsOrthogonal() const {
            Matrix2D TransposeMatrix = Transpose();
            Matrix2D IdentityMatrix = TransposeMatrix * (*this);
            return IdentityMatrix.IsIdentity();
        }

        /**
         * Checks if the matrix is equal to another matrix.
         *
         * @param OtherMatrix The matrix to compare with.
         * @return True if the matrices are equal, false otherwise.
         */
        constexpr bool operator==(const Matrix2D& OtherMatrix) const {
            float epsilon = 1e-6f;
            return (std::fabs(m00 - OtherMatrix.m00) < epsilon &&
                    std::fabs(m01 - OtherMatrix.m01) < epsilon &&
                    std::fabs(m10 - OtherMatrix.m10) < epsilon &&
                    std::fabs(m11 - OtherMatrix.m11) < epsilon);
        }

        /**
         * Checks if the matrix is not equal to another matrix.
         *
         * @param OtherMatrix The matrix to compare with.
         * @return True if the matrices are not equal, false otherwise.
         */
        constexpr bool operator!=(const Matrix2D &OtherMatrix) const {
            return !(*this == OtherMatrix);
        }

        /**
         * Prints the matrix to the console.
         */
        inline void Print(const char* label = nullptr) const {
            if (label) {
                std::cout << label << ":\n";
            }
            std::cout << "[" << m00 << ", " << m01 << "]\n"
                      << "[" << m10 << ", " << m11 << "]\n";
        }

        /**
         * Returns a rotated matrix.
         *
         * @param RadAngle The angle of rotation in radians.
         * @return The rotated matrix.
         */
        inline Matrix2D GetRotatedRad(float RadAngle) const {
            Matrix2D RotationMatrix = RotationRad(RadAngle);
            return *this * RotationMatrix;
        }

        /**
         * Returns a rotated matrix.
         *
         * @param DegAngle The angle of rotation in degrees.
         * @return The rotated matrix.
         */
        inline Matrix2D GetRotatedDeg(float DegAngle) const {
            Matrix2D RotationMatrix = RotationDeg(DegAngle);
            return *this * RotationMatrix;
        }

        /**
         * Applies a rotation transformation to the matrix.
         *
         * @param RadAngle The angle of rotation in radians.
         */
        inline void RotateRad(float RadAngle) {
            Matrix2D RotationMatrix = RotationRad(RadAngle);
            *this *= RotationMatrix;
        }

        /**
         * Applies a rotation transformation to the matrix.
         *
         * @param DegAngle The angle of rotation in degrees.
         */
        inline void RotateDeg(float DegAngle) {
            Matrix2D RotationMatrix = RotationDeg(DegAngle);
            *this *= RotationMatrix;
        }


        /**
         * Returns a scaled matrix.
         *
         * @param ScaleX The scaling factor in the x direction.
         * @param ScaleY The scaling factor in the y direction.
         * @return The scaled matrix.
         */
        inline Matrix2D GetScaled(float ScaleX, float ScaleY) const {
            return Matrix2D(
                    m00 * ScaleX, m01 * ScaleY,
                    m10 * ScaleX, m11 * ScaleY
            );
        }

        /**
         * Returns a scaled matrix.
         *
         * @param ScaleFactor The scaling factor.
         * @return The scaled matrix.
         */
        inline Matrix2D GetScaled(float ScaleFactor) const {
            return GetScaled(ScaleFactor, ScaleFactor);
        }

        /**
         * Applies a scaling transformation to the matrix.
         *
         * @param ScaleX The scaling factor in the x direction.
         * @param ScaleY The scaling factor in the y direction.
         */
        inline void Scale(float ScaleX, float ScaleY) {
            m00 *= ScaleX;
            m01 *= ScaleY;
            m10 *= ScaleX;
            m11 *= ScaleY;
        }

        /**
         * Applies a scaling transformation to the matrix.
         *
         * @param ScaleFactor The scaling factor.
         */
        inline void Scale(float ScaleFactor) {
            Scale(ScaleFactor, ScaleFactor);
        }

        /**
         * Returns a sheared matrix.
         *
         * @param ShearX The shearing factor in the x direction.
         * @param ShearY The shearing factor in the y direction.
         * @return The sheared matrix.
         */
        inline Matrix2D GetSheared(float ShearX, float ShearY) const {
            return Matrix2D(
                    m00 + ShearX * m10, m01 + ShearY * m11,
                    m10 + ShearX * m00, m11 + ShearY * m01
            );
        }

        /**
         * Returns a sheared matrix.
         *
         * @param ShearFactor The shearing factor.
         * @return The sheared matrix.
         */
        inline Matrix2D GetSheared(float ShearFactor) const {
            return GetSheared(ShearFactor, ShearFactor);
        }

        /**
         * Applies a shearing transformation to the matrix.
         *
         * @param ShearX The shearing factor in the x direction.
         * @param ShearY The shearing factor in the y direction.
         */
        inline void Shear(float ShearX, float ShearY) {
            float old_m00 = m00;
            float old_m01 = m01;
            float old_m10 = m10;
            float old_m11 = m11;

            m00 = old_m00 + ShearX * old_m10;
            m01 = old_m01 + ShearX * old_m11;
            m10 = old_m10 + ShearY * old_m00;
            m11 = old_m11 + ShearY * old_m01;
        }


        /**
         * Applies a shearing transformation to the matrix.
         *
         * @param ShearFactor The shearing factor.
         */
        inline void Shear(float ShearFactor) {
            Shear(ShearFactor, ShearFactor);
        }

        /**
         * Prints the matrix to the console.
         *
         * @param os The output stream.
         * @param Matrix The matrix to print.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const Matrix2D &Matrix) {
            os << "[" << Matrix.m00 << ", " << Matrix.m01 << "]\n"
               << "[" << Matrix.m10 << ", " << Matrix.m11 << "]\n";
            return os;
        }

    };
} // namespace Math

#endif //MATRIX2D_H