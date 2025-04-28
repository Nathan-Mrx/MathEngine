
//
// Created by natha on 2025-04-26.
//

#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <cmath>
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Vector3D.h"
#include "Constants.h"

namespace Math {

    /**
     * @class Matrix3D
     * @brief A 3x3 matrix class for 3D mathematical operations.
     *
     * This class provides functionality for manipulating 3x3 matrices, which are commonly
     * used in 3D graphics, physics simulations, and linear algebra operations. It supports
     * all standard matrix operations including addition, subtraction, multiplication,
     * determinant calculation, inverse, transpose, etc.
     *
     * The matrix is stored in row-major order, meaning elements are arranged as:
     * | m00 m01 m02 |
     * | m10 m11 m12 |
     * | m20 m21 m22 |
     *
     * Common uses include representing 3D rotations, scaling, shearing, and projections.
     */
    struct Matrix3D {
        /** @brief Matrix elements stored in row-major order */
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;

        /**
         * @brief Default constructor initializes to identity matrix.
         */
        constexpr Matrix3D()
            : m00(1.0f), m01(0.0f), m02(0.0f),
              m10(0.0f), m11(1.0f), m12(0.0f),
              m20(0.0f), m21(0.0f), m22(1.0f) {}

        /**
         * @brief Constructor with individual elements.
         * 
         * @param m00 Element at row 0, column 0
         * @param m01 Element at row 0, column 1
         * @param m02 Element at row 0, column 2
         * @param m10 Element at row 1, column 0
         * @param m11 Element at row 1, column 1
         * @param m12 Element at row 1, column 2
         * @param m20 Element at row 2, column 0
         * @param m21 Element at row 2, column 1
         * @param m22 Element at row 2, column 2
         */
        constexpr Matrix3D(
            float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22
        ) : m00(m00), m01(m01), m02(m02),
            m10(m10), m11(m11), m12(m12),
            m20(m20), m21(m21), m22(m22) {}

        /**
         * @brief Constructor from column vectors.
         * 
         * @param col0 The first column vector
         * @param col1 The second column vector
         * @param col2 The third column vector
         */
        constexpr Matrix3D(const Vector3D& col0, const Vector3D& col1, const Vector3D& col2)
            : m00(col0.x), m01(col1.x), m02(col2.x),
              m10(col0.y), m11(col1.y), m12(col2.y),
              m20(col0.z), m21(col1.z), m22(col2.z) {}

        /**
         * @brief Constructor from array of elements in row-major order.
         * 
         * @param elements Array of 9 float values in row-major order
         */
        explicit constexpr Matrix3D(const std::array<float, 9>& elements)
            : m00(elements[0]), m01(elements[1]), m02(elements[2]),
              m10(elements[3]), m11(elements[4]), m12(elements[5]),
              m20(elements[6]), m21(elements[7]), m22(elements[8]) {}

        /**
         * @brief Get a specific element from the matrix using row and column indices.
         * 
         * @param row The row index (0-2)
         * @param col The column index (0-2)
         * @return The element at the specified position
         * @throws std::out_of_range if indices are out of bounds
         */
        [[nodiscard]] float GetElement(int row, int col) const {
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                throw std::out_of_range("Matrix indices out of range");
            }
            
            const float* elements[3][3] = {
                {&m00, &m01, &m02},
                {&m10, &m11, &m12},
                {&m20, &m21, &m22}
            };
            
            return *elements[row][col];
        }

        /**
         * @brief Set a specific element in the matrix using row and column indices.
         * 
         * @param row The row index (0-2)
         * @param col The column index (0-2)
         * @param value The value to set
         * @throws std::out_of_range if indices are out of bounds
         */
        void SetElement(int row, int col, float value) {
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                throw std::out_of_range("Matrix indices out of range");
            }
            
            float* elements[3][3] = {
                {&m00, &m01, &m02},
                {&m10, &m11, &m12},
                {&m20, &m21, &m22}
            };
            
            *elements[row][col] = value;
        }

        /**
         * @brief Get a row of the matrix as a Vector3D.
         * 
         * @param row The row index (0-2)
         * @return The row as a Vector3D
         * @throws std::out_of_range if row index is out of bounds
         */
        [[nodiscard]] Vector3D GetRow(int row) const {
            if (row < 0 || row > 2) {
                throw std::out_of_range("Row index out of range");
            }
            
            switch (row) {
                case 0: return Vector3D(m00, m01, m02);
                case 1: return Vector3D(m10, m11, m12);
                case 2: return Vector3D(m20, m21, m22);
                default: return Vector3D(); // Should never reach here
            }
        }

        /**
         * @brief Set a row of the matrix.
         * 
         * @param row The row index (0-2)
         * @param value The Vector3D to set as the row
         * @throws std::out_of_range if row index is out of bounds
         */
        void SetRow(int row, const Vector3D& value) {
            if (row < 0 || row > 2) {
                throw std::out_of_range("Row index out of range");
            }
            
            switch (row) {
                case 0:
                    m00 = value.x;
                    m01 = value.y;
                    m02 = value.z;
                    break;
                case 1:
                    m10 = value.x;
                    m11 = value.y;
                    m12 = value.z;
                    break;
                case 2:
                    m20 = value.x;
                    m21 = value.y;
                    m22 = value.z;
                    break;
            }
        }

        /**
         * @brief Get a column of the matrix as a Vector3D.
         * 
         * @param col The column index (0-2)
         * @return The column as a Vector3D
         * @throws std::out_of_range if column index is out of bounds
         */
        [[nodiscard]] Vector3D GetColumn(int col) const {
            if (col < 0 || col > 2) {
                throw std::out_of_range("Column index out of range");
            }
            
            switch (col) {
                case 0: return Vector3D(m00, m10, m20);
                case 1: return Vector3D(m01, m11, m21);
                case 2: return Vector3D(m02, m12, m22);
                default: return Vector3D(); // Should never reach here
            }
        }

        /**
         * @brief Set a column of the matrix.
         * 
         * @param col The column index (0-2)
         * @param value The Vector3D to set as the column
         * @throws std::out_of_range if column index is out of bounds
         */
        void SetColumn(int col, const Vector3D& value) {
            if (col < 0 || col > 2) {
                throw std::out_of_range("Column index out of range");
            }
            
            switch (col) {
                case 0:
                    m00 = value.x;
                    m10 = value.y;
                    m20 = value.z;
                    break;
                case 1:
                    m01 = value.x;
                    m11 = value.y;
                    m21 = value.z;
                    break;
                case 2:
                    m02 = value.x;
                    m12 = value.y;
                    m22 = value.z;
                    break;
            }
        }

        /**
         * @brief Convert the matrix to an array of elements in row-major order.
         * 
         * @return An array of 9 elements representing the matrix in row-major order
         */
        [[nodiscard]] std::array<float, 9> ToArray() const {
            return {
                m00, m01, m02,
                m10, m11, m12,
                m20, m21, m22
            };
        }

        /**
         * @brief Multiplies this matrix by another matrix.
         *
         * Matrix multiplication is performed as (this * other).
         *
         * @param other The matrix to multiply with
         * @return The product of the two matrices
         */
        [[nodiscard]] constexpr Matrix3D operator*(const Matrix3D& other) const {
            return Matrix3D(
                // Row 0
                m00 * other.m00 + m01 * other.m10 + m02 * other.m20,
                m00 * other.m01 + m01 * other.m11 + m02 * other.m21,
                m00 * other.m02 + m01 * other.m12 + m02 * other.m22,
                // Row 1
                m10 * other.m00 + m11 * other.m10 + m12 * other.m20,
                m10 * other.m01 + m11 * other.m11 + m12 * other.m21,
                m10 * other.m02 + m11 * other.m12 + m12 * other.m22,
                // Row 2
                m20 * other.m00 + m21 * other.m10 + m22 * other.m20,
                m20 * other.m01 + m21 * other.m11 + m22 * other.m21,
                m20 * other.m02 + m21 * other.m12 + m22 * other.m22
            );
        }

        /**
         * @brief Multiplies this matrix by another matrix and assigns the result to this matrix.
         *
         * @param other The matrix to multiply with
         * @return Reference to this matrix after multiplication
         */
        Matrix3D& operator*=(const Matrix3D& other) {
            *this = *this * other;
            return *this;
        }

        /**
         * @brief Multiplies this matrix by a vector.
         *
         * Transforms the vector by this matrix.
         *
         * @param vector The vector to multiply with
         * @return The transformed vector
         */
        [[nodiscard]] constexpr Vector3D operator*(const Vector3D& vector) const {
            return Vector3D(
                m00 * vector.x + m01 * vector.y + m02 * vector.z,
                m10 * vector.x + m11 * vector.y + m12 * vector.z,
                m20 * vector.x + m21 * vector.y + m22 * vector.z
            );
        }

        /**
         * @brief Multiplies this matrix by a scalar.
         *
         * @param scalar The scalar to multiply by
         * @return The scaled matrix
         */
        [[nodiscard]] constexpr Matrix3D operator*(float scalar) const {
            return Matrix3D(
                m00 * scalar, m01 * scalar, m02 * scalar,
                m10 * scalar, m11 * scalar, m12 * scalar,
                m20 * scalar, m21 * scalar, m22 * scalar
            );
        }

        /**
         * @brief Multiplies this matrix by a scalar and assigns the result to this matrix.
         *
         * @param scalar The scalar to multiply by
         * @return Reference to this matrix after scaling
         */
        Matrix3D& operator*=(float scalar) {
            m00 *= scalar; m01 *= scalar; m02 *= scalar;
            m10 *= scalar; m11 *= scalar; m12 *= scalar;
            m20 *= scalar; m21 *= scalar; m22 *= scalar;
            return *this;
        }

        /**
         * @brief Adds another matrix to this matrix.
         *
         * @param other The matrix to add
         * @return The sum of the two matrices
         */
        [[nodiscard]] constexpr Matrix3D operator+(const Matrix3D& other) const {
            return Matrix3D(
                m00 + other.m00, m01 + other.m01, m02 + other.m02,
                m10 + other.m10, m11 + other.m11, m12 + other.m12,
                m20 + other.m20, m21 + other.m21, m22 + other.m22
            );
        }

        /**
         * @brief Adds another matrix to this matrix and assigns the result to this matrix.
         *
         * @param other The matrix to add
         * @return Reference to this matrix after addition
         */
        Matrix3D& operator+=(const Matrix3D& other) {
            m00 += other.m00; m01 += other.m01; m02 += other.m02;
            m10 += other.m10; m11 += other.m11; m12 += other.m12;
            m20 += other.m20; m21 += other.m21; m22 += other.m22;
            return *this;
        }

        /**
         * @brief Subtracts another matrix from this matrix.
         *
         * @param other The matrix to subtract
         * @return The difference of the two matrices
         */
        [[nodiscard]] constexpr Matrix3D operator-(const Matrix3D& other) const {
            return Matrix3D(
                m00 - other.m00, m01 - other.m01, m02 - other.m02,
                m10 - other.m10, m11 - other.m11, m12 - other.m12,
                m20 - other.m20, m21 - other.m21, m22 - other.m22
            );
        }

        /**
         * @brief Subtracts another matrix from this matrix and assigns the result to this matrix.
         *
         * @param other The matrix to subtract
         * @return Reference to this matrix after subtraction
         */
        Matrix3D& operator-=(const Matrix3D& other) {
            m00 -= other.m00; m01 -= other.m01; m02 -= other.m02;
            m10 -= other.m10; m11 -= other.m11; m12 -= other.m12;
            m20 -= other.m20; m21 -= other.m21; m22 -= other.m22;
            return *this;
        }

        /**
         * @brief Negates this matrix (changes the sign of all elements).
         *
         * @return The negated matrix
         */
        [[nodiscard]] constexpr Matrix3D operator-() const {
            return Matrix3D(
                -m00, -m01, -m02,
                -m10, -m11, -m12,
                -m20, -m21, -m22
            );
        }

        /**
         * @brief Checks if this matrix is equal to another matrix within a small epsilon.
         *
         * @param other The matrix to compare with
         * @param epsilon The tolerance for floating-point comparison (default: 1e-6)
         * @return True if the matrices are equal within the specified epsilon, false otherwise
         */
        [[nodiscard]] bool Equals(const Matrix3D& other, float epsilon = 1e-6f) const {
            return (std::fabs(m00 - other.m00) < epsilon &&
                    std::fabs(m01 - other.m01) < epsilon &&
                    std::fabs(m02 - other.m02) < epsilon &&
                    std::fabs(m10 - other.m10) < epsilon &&
                    std::fabs(m11 - other.m11) < epsilon &&
                    std::fabs(m12 - other.m12) < epsilon &&
                    std::fabs(m20 - other.m20) < epsilon &&
                    std::fabs(m21 - other.m21) < epsilon &&
                    std::fabs(m22 - other.m22) < epsilon);
        }

        /**
         * @brief Equality operator.
         *
         * @param other The matrix to compare with
         * @return True if the matrices are equal, false otherwise
         */
        bool operator==(const Matrix3D& other) const {
            return Equals(other);
        }

        /**
         * @brief Inequality operator.
         *
         * @param other The matrix to compare with
         * @return True if the matrices are not equal, false otherwise
         */
        bool operator!=(const Matrix3D& other) const {
            return !(*this == other);
        }

        /**
         * @brief Calculates the determinant of the matrix.
         *
         * The determinant is calculated as:
         * det = m00 * (m11 * m22 - m12 * m21) - m01 * (m10 * m22 - m12 * m20) + m02 * (m10 * m21 - m11 * m20)
         *
         * @return The determinant of the matrix
         */
        [[nodiscard]] float Determinant() const {
            return m00 * (m11 * m22 - m12 * m21) -
                   m01 * (m10 * m22 - m12 * m20) +
                   m02 * (m10 * m21 - m11 * m20);
        }

        /**
         * @brief Calculates the trace of the matrix.
         *
         * The trace is the sum of the diagonal elements:
         * trace = m00 + m11 + m22
         *
         * @return The trace of the matrix
         */
        [[nodiscard]] float Trace() const {
            return m00 + m11 + m22;
        }

        /**
         * @brief Calculates the transpose of the matrix.
         *
         * The transpose swaps rows and columns:
         * transpose(M)[i,j] = M[j,i]
         *
         * @return The transposed matrix
         */
        [[nodiscard]] constexpr Matrix3D Transpose() const {
            return Matrix3D(
                m00, m10, m20,
                m01, m11, m21,
                m02, m12, m22
            );
        }

        /**
         * @brief Transposes this matrix in place.
         */
        void TransposeInPlace() {
            std::swap(m01, m10);
            std::swap(m02, m20);
            std::swap(m12, m21);
        }

        /**
         * @brief Creates the adjoint (adjugate) matrix.
         *
         * The adjoint is the transpose of the cofactor matrix.
         *
         * @return The adjoint matrix
         */
        [[nodiscard]] Matrix3D Adjoint() const {
            // Calculate cofactors
            float c00 = m11 * m22 - m12 * m21;
            float c01 = m10 * m22 - m12 * m20;
            float c02 = m10 * m21 - m11 * m20;
            
            float c10 = m01 * m22 - m02 * m21;
            float c11 = m00 * m22 - m02 * m20;
            float c12 = m00 * m21 - m01 * m20;
            
            float c20 = m01 * m12 - m02 * m11;
            float c21 = m00 * m12 - m02 * m10;
            float c22 = m00 * m11 - m01 * m10;
            
            // Adjoint is the transpose of the cofactor matrix with appropriate sign adjustments
            return Matrix3D(
                 c00, -c10,  c20,
                -c01,  c11, -c21,
                 c02, -c12,  c22
            );
        }

        /**
         * @brief Calculates the inverse of the matrix.
         *
         * The inverse is calculated as:
         * inverse = adjoint / determinant
         *
         * @return The inverse matrix
         * @throws std::runtime_error if the matrix is singular (determinant is zero)
         */
        [[nodiscard]] Matrix3D Inverse() const {
            float det = Determinant();
            
            if (std::fabs(det) < 1e-6f) {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }
            
            return Adjoint() * (1.0f / det);
        }

        /**
         * @brief Inverts this matrix in place.
         *
         * @throws std::runtime_error if the matrix is singular (determinant is zero)
         */
        void InvertInPlace() {
            *this = this->Inverse();
        }

        /**
         * @brief Checks if this matrix is an identity matrix.
         *
         * @param epsilon The tolerance for floating-point comparison (default: 1e-6)
         * @return True if the matrix is an identity matrix within the specified epsilon, false otherwise
         */
        [[nodiscard]] bool IsIdentity(float epsilon = 1e-6f) const {
            return (std::fabs(m00 - 1.0f) < epsilon &&
                    std::fabs(m11 - 1.0f) < epsilon &&
                    std::fabs(m22 - 1.0f) < epsilon &&
                    std::fabs(m01) < epsilon &&
                    std::fabs(m02) < epsilon &&
                    std::fabs(m10) < epsilon &&
                    std::fabs(m12) < epsilon &&
                    std::fabs(m20) < epsilon &&
                    std::fabs(m21) < epsilon);
        }

        /**
         * @brief Checks if this matrix is a zero matrix.
         *
         * @param epsilon The tolerance for floating-point comparison (default: 1e-6)
         * @return True if the matrix is a zero matrix within the specified epsilon, false otherwise
         */
        [[nodiscard]] bool IsZero(float epsilon = 1e-6f) const {
            return (std::fabs(m00) < epsilon &&
                    std::fabs(m01) < epsilon &&
                    std::fabs(m02) < epsilon &&
                    std::fabs(m10) < epsilon &&
                    std::fabs(m11) < epsilon &&
                    std::fabs(m12) < epsilon &&
                    std::fabs(m20) < epsilon &&
                    std::fabs(m21) < epsilon &&
                    std::fabs(m22) < epsilon);
        }

        /**
         * @brief Checks if this matrix is symmetric.
         *
         * A symmetric matrix is equal to its transpose: M = M^T
         *
         * @param epsilon The tolerance for floating-point comparison (default: 1e-6)
         * @return True if the matrix is symmetric within the specified epsilon, false otherwise
         */
        [[nodiscard]] bool IsSymmetric(float epsilon = 1e-6f) const {
            return (std::fabs(m01 - m10) < epsilon &&
                    std::fabs(m02 - m20) < epsilon &&
                    std::fabs(m12 - m21) < epsilon);
        }

        /**
         * @brief Checks if this matrix is orthogonal.
         *
         * An orthogonal matrix satisfies: M * M^T = I
         * Which means its transpose equals its inverse.
         *
         * @param epsilon The tolerance for floating-point comparison (default: 1e-6)
         * @return True if the matrix is orthogonal within the specified epsilon, false otherwise
         */
        [[nodiscard]] bool IsOrthogonal(float epsilon = 1e-6f) const {
            Matrix3D product = *this * this->Transpose();
            return product.IsIdentity(epsilon);
        }

        /**
         * @brief Checks if this matrix is diagonal.
         *
         * A diagonal matrix has non-zero elements only on the main diagonal.
         *
         * @param epsilon The tolerance for floating-point comparison (default: 1e-6)
         * @return True if the matrix is diagonal within the specified epsilon, false otherwise
         */
        [[nodiscard]] bool IsDiagonal(float epsilon = 1e-6f) const {
            return (std::fabs(m01) < epsilon &&
                    std::fabs(m02) < epsilon &&
                    std::fabs(m10) < epsilon &&
                    std::fabs(m12) < epsilon &&
                    std::fabs(m20) < epsilon &&
                    std::fabs(m21) < epsilon);
        }

        /**
         * @brief Checks if this matrix is invertible.
         *
         * A matrix is invertible if its determinant is not zero.
         *
         * @param epsilon The tolerance for floating-point comparison (default: 1e-6)
         * @return True if the matrix is invertible, false otherwise
         */
        [[nodiscard]] bool IsInvertible(float epsilon = 1e-6f) const {
            return std::fabs(Determinant()) >= epsilon;
        }

        /**
         * @brief Creates an identity matrix.
         *
         * @return The 3x3 identity matrix
         */
        static constexpr Matrix3D Identity() {
            return Matrix3D(
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        /**
         * @brief Creates a zero matrix.
         *
         * @return The 3x3 zero matrix
         */
        static constexpr Matrix3D Zero() {
            return Matrix3D(
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f
            );
        }

        /**
         * @brief Creates a diagonal matrix from three scalar values.
         *
         * @param d0 The first diagonal element (m00)
         * @param d1 The second diagonal element (m11)
         * @param d2 The third diagonal element (m22)
         * @return A diagonal matrix with the specified values on the main diagonal
         */
        static constexpr Matrix3D Diagonal(float d0, float d1, float d2) {
            return Matrix3D(
                d0, 0.0f, 0.0f,
                0.0f, d1, 0.0f,
                0.0f, 0.0f, d2
            );
        }

        /**
         * @brief Creates a diagonal matrix from a vector.
         *
         * @param diagonal The vector containing the diagonal elements
         * @return A diagonal matrix with the vector elements on the main diagonal
         */
        static constexpr Matrix3D Diagonal(const Vector3D& diagonal) {
            return Diagonal(diagonal.x, diagonal.y, diagonal.z);
        }

        /**
         * @brief Creates a scaling matrix.
         *
         * @param scaleX The scaling factor along the X axis
         * @param scaleY The scaling factor along the Y axis
         * @param scaleZ The scaling factor along the Z axis
         * @return A scaling matrix
         */
        static constexpr Matrix3D Scaling(float scaleX, float scaleY, float scaleZ) {
            return Diagonal(scaleX, scaleY, scaleZ);
        }

        /**
         * @brief Creates a scaling matrix from a vector.
         *
         * @param scale The scaling factors as a 3D vector
         * @return A scaling matrix
         */
        static constexpr Matrix3D Scaling(const Vector3D& scale) {
            return Diagonal(scale.x, scale.y, scale.z);
        }

        /**
         * @brief Creates a uniform scaling matrix.
         *
         * @param scale The uniform scaling factor for all axes
         * @return A uniform scaling matrix
         */
        static constexpr Matrix3D Scaling(float scale) {
            return Diagonal(scale, scale, scale);
        }

        /**
         * @brief Creates a rotation matrix around the X axis.
         *
         * @param angleRadians The rotation angle in radians
         * @return A rotation matrix around the X axis
         */
        static Matrix3D RotationX(float angleRadians) {
            float cosAngle = std::cos(angleRadians);
            float sinAngle = std::sin(angleRadians);
            
            return Matrix3D(
                1.0f, 0.0f, 0.0f,
                0.0f, cosAngle, -sinAngle,
                0.0f, sinAngle, cosAngle
            );
        }

        /**
         * @brief Creates a rotation matrix around the Y axis.
         *
         * @param angleRadians The rotation angle in radians
         * @return A rotation matrix around the Y axis
         */
        static Matrix3D RotationY(float angleRadians) {
            float cosAngle = std::cos(angleRadians);
            float sinAngle = std::sin(angleRadians);
            
            return Matrix3D(
                cosAngle, 0.0f, sinAngle,
                0.0f, 1.0f, 0.0f,
                -sinAngle, 0.0f, cosAngle
            );
        }

        /**
         * @brief Creates a rotation matrix around the Z axis.
         *
         * @param angleRadians The rotation angle in radians
         * @return A rotation matrix around the Z axis
         */
        static Matrix3D RotationZ(float angleRadians) {
            float cosAngle = std::cos(angleRadians);
            float sinAngle = std::sin(angleRadians);
            
            return Matrix3D(
                cosAngle, -sinAngle, 0.0f,
                sinAngle, cosAngle, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }


        /**
         * @brief Creates a rotation matrix around an arbitrary axis.
         *
         * @param axis The axis to rotate around (should be normalized)
         * @param angleRadians The rotation angle in radians
         * @return A rotation matrix around the specified axis
         */
        static Matrix3D RotationAxis(const Vector3D& axis, float angleRadians) {
            float cosAngle = std::cos(angleRadians);
            float sinAngle = std::sin(angleRadians);
            float oneMinusCos = 1.0f - cosAngle;

            // Ensure the axis is normalized
            Vector3D normalizedAxis = axis.Normalize();
            float x = normalizedAxis.x;
            float y = normalizedAxis.y;
            float z = normalizedAxis.z;

            // Precompute common products
            float xx = x * x;
            float xy = x * y;
            float xz = x * z;
            float yy = y * y;
            float yz = y * z;
            float zz = z * z;

            float xSin = x * sinAngle;
            float ySin = y * sinAngle;
            float zSin = z * sinAngle;

            return Matrix3D(
                cosAngle + xx * oneMinusCos,    xy * oneMinusCos - zSin,      xz * oneMinusCos + ySin,
                xy * oneMinusCos + zSin,        cosAngle + yy * oneMinusCos,  yz * oneMinusCos - xSin,
                xz * oneMinusCos - ySin,        yz * oneMinusCos + xSin,      cosAngle + zz * oneMinusCos
            );
        }

        /**
         * @brief Creates a rotation matrix from Euler angles (in radians).
         *
         * The rotation is applied in the order: Z, Y, X (roll, pitch, yaw).
         *
         * @param xRadians Rotation around X axis in radians (roll)
         * @param yRadians Rotation around Y axis in radians (pitch)
         * @param zRadians Rotation around Z axis in radians (yaw)
         * @return A combined rotation matrix
         */
        static Matrix3D RotationEuler(float xRadians, float yRadians, float zRadians) {
            Matrix3D xRot = RotationX(xRadians);
            Matrix3D yRot = RotationY(yRadians);
            Matrix3D zRot = RotationZ(zRadians);

            // Apply rotations in the order Z, Y, X
            return xRot * yRot * zRot;
        }

        /**
         * @brief Creates a rotation matrix from Euler angles specified in degrees.
         *
         * The rotation is applied in the order: Z, Y, X (roll, pitch, yaw).
         *
         * @param xDegrees Rotation around X axis in degrees (roll)
         * @param yDegrees Rotation around Y axis in degrees (pitch)
         * @param zDegrees Rotation around Z axis in degrees (yaw)
         * @return A combined rotation matrix
         */
        static Matrix3D RotationEulerDegrees(float xDegrees, float yDegrees, float zDegrees) {
            constexpr float degToRad = M_PI / 180.0f;
            return RotationEuler(
                xDegrees * degToRad,
                yDegrees * degToRad,
                zDegrees * degToRad
            );
        }

        /**
         * @brief Creates a rotation matrix to align with the specified direction.
         *
         * Creates a rotation matrix that would rotate the Z axis to point in the specified direction.
         *
         * @param direction The target direction (should be normalized)
         * @param up The up vector used to determine orientation (default is world up)
         * @return A rotation matrix aligning with the specified direction
         */
        static Matrix3D LookAt(const Vector3D& direction, const Vector3D& up = Vector3D(0, 1, 0)) {
            // Ensure the direction is normalized
            Vector3D forward = direction.Normalize();

            // Compute right vector via cross product
            Vector3D right = up.Cross(forward).Normalize();

            // Recompute up vector to ensure orthogonality
            Vector3D newUp = forward.Cross(right);

            // Construct rotation matrix from the three orthogonal vectors
            return Matrix3D(
                right.x, right.y, right.z,
                newUp.x, newUp.y, newUp.z,
                forward.x, forward.y, forward.z
            );
        }

        /**
         * @brief Creates a reflection matrix that reflects across a plane.
         *
         * @param normal The normal vector of the reflection plane (should be normalized)
         * @return A reflection matrix
         */
        static Matrix3D Reflection(const Vector3D& normal) {
            // Ensure the normal is normalized
            Vector3D normalizedNormal = normal.Normalize();
            float x = normalizedNormal.x;
            float y = normalizedNormal.y;
            float z = normalizedNormal.z;

            float xx = 2.0f * x * x;
            float xy = 2.0f * x * y;
            float xz = 2.0f * x * z;
            float yy = 2.0f * y * y;
            float yz = 2.0f * y * z;
            float zz = 2.0f * z * z;

            return Matrix3D(
                1.0f - xx, -xy, -xz,
                -xy, 1.0f - yy, -yz,
                -xz, -yz, 1.0f - zz
            );
        }

        /**
         * @brief Creates a shearing matrix.
         *
         * @param shearXY Amount to shear X by Y
         * @param shearXZ Amount to shear X by Z
         * @param shearYX Amount to shear Y by X
         * @param shearYZ Amount to shear Y by Z
         * @param shearZX Amount to shear Z by X
         * @param shearZY Amount to shear Z by Y
         * @return A shearing matrix
         */
        static constexpr Matrix3D Shearing(
            float shearXY, float shearXZ,
            float shearYX, float shearYZ,
            float shearZX, float shearZY
        ) {
            return Matrix3D(
                1.0f, shearXY, shearXZ,
                shearYX, 1.0f, shearYZ,
                shearZX, shearZY, 1.0f
            );
        }

        /**
         * @brief Creates a skew-symmetric matrix from a vector.
         *
         * A skew-symmetric matrix satisfies M^T = -M and can be used to represent
         * the cross product: v × w = S(v) * w, where S(v) is the skew-symmetric matrix of v.
         *
         * @param v The vector to create a skew-symmetric matrix from
         * @return A skew-symmetric matrix
         */
        static constexpr Matrix3D SkewSymmetric(const Vector3D& v) {
            return Matrix3D(
                0.0f, -v.z, v.y,
                v.z, 0.0f, -v.x,
                -v.y, v.x, 0.0f
            );
        }

        /**
         * @brief Extracts the scale components from the matrix.
         *
         * @return A vector containing the scale factors along each axis
         */
        [[nodiscard]] Vector3D ExtractScale() const {
            Vector3D col0(m00, m10, m20);
            Vector3D col1(m01, m11, m21);
            Vector3D col2(m02, m12, m22);

            return Vector3D(
                col0.Length(),
                col1.Length(),
                col2.Length()
            );
        }

        /**
         * @brief Extracts the rotation matrix by removing scaling.
         *
         * @return A rotation-only matrix
         */
        [[nodiscard]] Matrix3D ExtractRotation() const {
            Vector3D scale = ExtractScale();

            // Prevent division by zero
            if (scale.x < 1e-6f || scale.y < 1e-6f || scale.z < 1e-6f) {
                return Identity();
            }

            // Remove scaling to get pure rotation
            return Matrix3D(
                m00 / scale.x, m01 / scale.y, m02 / scale.z,
                m10 / scale.x, m11 / scale.y, m12 / scale.z,
                m20 / scale.x, m21 / scale.y, m22 / scale.z
            );
        }

        /**
         * @brief Linearly interpolates between two matrices.
         *
         * @param a The starting matrix
         * @param b The ending matrix
         * @param t The interpolation parameter in the range [0, 1]
         * @return The interpolated matrix
         */
        static Matrix3D Lerp(const Matrix3D& a, const Matrix3D& b, float t) {
            // Clamp t to [0, 1]
            t = std::max(0.0f, std::min(1.0f, t));

            return Matrix3D(
                a.m00 + (b.m00 - a.m00) * t, a.m01 + (b.m01 - a.m01) * t, a.m02 + (b.m02 - a.m02) * t,
                a.m10 + (b.m10 - a.m10) * t, a.m11 + (b.m11 - a.m11) * t, a.m12 + (b.m12 - a.m12) * t,
                a.m20 + (b.m20 - a.m20) * t, a.m21 + (b.m21 - a.m21) * t, a.m22 + (b.m22 - a.m22) * t
            );
        }

        /**
         * @brief Creates a projection matrix for projecting onto a plane.
         *
         * @param normal The normal vector of the projection plane (should be normalized)
         * @return A projection matrix
         */
        static Matrix3D ProjectionOntoPlane(const Vector3D& normal) {
            // Ensure the normal is normalized
            Vector3D normalizedNormal = normal.Normalize();
            float x = normalizedNormal.x;
            float y = normalizedNormal.y;
            float z = normalizedNormal.z;

            float xx = x * x;
            float xy = x * y;
            float xz = x * z;
            float yy = y * y;
            float yz = y * z;
            float zz = z * z;

            return Matrix3D(
                1.0f - xx, -xy, -xz,
                -xy, 1.0f - yy, -yz,
                -xz, -yz, 1.0f - zz
            );
        }

        /**
         * @brief Calculates the eigenvalues of the matrix.
         *
         * For a 3x3 matrix, there are up to 3 eigenvalues, which are the solutions to:
         * det(A - λI) = 0
         *
         * This function will only work correctly for symmetric matrices.
         *
         * @return A vector containing the eigenvalues
         * @throws std::runtime_error if the algorithm fails to converge
         */
        [[nodiscard]] Vector3D CalculateEigenvalues() {
            // Ensure the matrix is symmetric
            if (!IsSymmetric()) {
                throw std::runtime_error("Eigenvalue calculation requires a symmetric matrix");
            }

            // Use the characteristic equation for a 3x3 matrix
            // λ³ - tr(A)λ² + (m00m11 + m11m22 + m00m22 - m01² - m12² - m02²)λ - det(A) = 0

            float a = -Trace();
            float b = m00 * m11 + m11 * m22 + m00 * m22 -
                     m01 * m01 - m12 * m12 - m02 * m02;
            float c = -Determinant();

            // This is a cubic equation. For simplicity, we'll use a numerical method
            // For a more robust implementation, consider using a dedicated eigenvalue solver

            // For this example, we'll implement a simple power iteration method
            // which works well for symmetric matrices

            Vector3D eigenvalues;
            Vector3D v = Vector3D(1, 1, 1).Normalize(); // Starting vector

            for (int i = 0; i < 3; i++) {
                // Power iteration for largest eigenvalue
                for (int iter = 0; iter < 30; iter++) { // Usually converges in fewer iterations
                    Vector3D new_v = (*this) * v;
                    float length = new_v.Length();

                    if (length < 1e-10f) {
                        // Matrix likely has a zero eigenvalue
                        eigenvalues[i] = 0;
                        break;
                    }

                    new_v = new_v / length;

                    // Check for convergence
                    if ((new_v - v).Length() < 1e-6f || (new_v + v).Length() < 1e-6f) {
                        eigenvalues[i] = v.Dot((*this) * v); // Rayleigh quotient
                        break;
                    }

                    v = new_v;

                    if (iter == 29) {
                        // Failed to converge
                        throw std::runtime_error("Eigenvalue calculation failed to converge");
                    }
                }

                // Deflation - remove the found eigenvalue/eigenvector
                if (i < 2) { // We don't need to do this for the last eigenvalue
                    Matrix3D vvT(
                        v.x * v.x, v.x * v.y, v.x * v.z,
                        v.y * v.x, v.y * v.y, v.y * v.z,
                        v.z * v.x, v.z * v.y, v.z * v.z
                    );

                    *this = *this - vvT * eigenvalues[i];

                    // For the next eigenvalue, start with a vector orthogonal to v
                    if (i == 0) {
                        if (std::fabs(v.x) > std::fabs(v.y)) {
                            v = Vector3D(-v.z, 0, v.x).Normalize();
                        } else {
                            v = Vector3D(0, -v.z, v.y).Normalize();
                        }
                    }
                }
            }

            return eigenvalues;
        }

        [[nodiscard]] constexpr Matrix3D operator/(float scalar) const {
            if (std::abs(scalar) < Constants::EPSILON) {
                // Handle division by zero
                return *this;
            }
            return Matrix3D(
                m00 / scalar, m01 / scalar, m02 / scalar,
                m10 / scalar, m11 / scalar, m12 / scalar,
                m20 / scalar, m21 / scalar, m22 / scalar
            );
        }

        Matrix3D& operator/=(float scalar) {
            if (std::abs(scalar) < Constants::EPSILON) {
                // Handle division by zero
                return *this;
            }
            m00 /= scalar; m01 /= scalar; m02 /= scalar;
            m10 /= scalar; m11 /= scalar; m12 /= scalar;
            m20 /= scalar; m21 /= scalar; m22 /= scalar;
            return *this;
        }

        static Matrix3D RotationXRad(float angleRadians) {
            return RotationX(angleRadians);
        }

        static Matrix3D RotationYRad(float angleRadians) {
            return RotationY(angleRadians);
        }

        static Matrix3D RotationZRad(float angleRadians) {
            return RotationZ(angleRadians);
        }

        static Matrix3D RotationXDeg(float angleDegrees) {
            return RotationX(Constants::DEG_TO_RAD * angleDegrees);
        }

        static Matrix3D RotationYDeg(float angleDegrees) {
            return RotationY(Constants::DEG_TO_RAD * angleDegrees);
        }

        static Matrix3D RotationZDeg(float angleDegrees) {
            return RotationZ(Constants::DEG_TO_RAD * angleDegrees);
        }

        [[nodiscard]] Matrix3D GetScaled(float scaleX, float scaleY, float scaleZ) const {
            return Matrix3D(
                m00 * scaleX, m01 * scaleY, m02 * scaleZ,
                m10 * scaleX, m11 * scaleY, m12 * scaleZ,
                m20 * scaleX, m21 * scaleY, m22 * scaleZ
            );
        }

        [[nodiscard]] Matrix3D GetScaled(float scale) const {
            return GetScaled(scale, scale, scale);
        }

        void Scale(float scaleX, float scaleY, float scaleZ) {
            m00 *= scaleX; m01 *= scaleY; m02 *= scaleZ;
            m10 *= scaleX; m11 *= scaleY; m12 *= scaleZ;
            m20 *= scaleX; m21 *= scaleY; m22 *= scaleZ;
        }

        [[nodiscard]] Matrix3D GetRotatedXRad(float angleRadians) const {
            return *this * RotationXRad(angleRadians);
        }

        [[nodiscard]] Matrix3D GetRotatedYRad(float angleRadians) const {
            return *this * RotationYRad(angleRadians);
        }

        [[nodiscard]] Matrix3D GetRotatedZRad(float angleRadians) const {
            return *this * RotationZRad(angleRadians);
        }

        void RotateXRad(float angleRadians) {
            *this = *this * RotationXRad(angleRadians);
        }

        void RotateYRad(float angleRadians) {
            *this = *this * RotationYRad(angleRadians);
        }

        void RotateZRad(float angleRadians) {
            *this = *this * RotationZRad(angleRadians);
        }


        /**
         * @brief Output stream operator for the matrix.
         *
         * @param os The output stream
         * @param m The matrix to output
         * @return The output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix3D& m) {
            os << "[" << m.m00 << ", " << m.m01 << ", " << m.m02 << "]\n"
               << "[" << m.m10 << ", " << m.m11 << ", " << m.m12 << "]\n"
               << "[" << m.m20 << ", " << m.m21 << ", " << m.m22 << "]";
            return os;
        }

        /**
         * @brief Print the matrix to the console with an optional label.
         *
         * @param label An optional label to print before the matrix
         */
        void Print(const char* label = nullptr) const {
            if (label) {
                std::cout << label << ":\n";
            }
            std::cout << *this << std::endl;
        }

        /**
         * @brief Convert the matrix to a formatted string.
         *
         * @return A string representation of the matrix
         */
        [[nodiscard]] std::string ToString() const {
            std::ostringstream ss;
            ss << *this;
            return ss.str();
        }

        /**
         * @brief Performs matrix orthogonalization using the Gram-Schmidt process.
         *
         * Makes the column vectors of the matrix orthogonal to each other while
         * preserving their general direction.
         *
         * @return An orthogonalized matrix
         */
        [[nodiscard]] Matrix3D Orthogonalize() const {
            // Extract column vectors
            Vector3D v1 = GetColumn(0);
            Vector3D v2 = GetColumn(1);
            Vector3D v3 = GetColumn(2);

            // Gram-Schmidt process
            Vector3D u1 = v1.Normalize();

            Vector3D u2 = v2 - u1 * v2.Dot(u1);
            float len2 = u2.Length();
            if (len2 > 1e-6f) {
                u2 = u2 / len2;
            } else {
                // Generate a vector orthogonal to u1
                if (std::fabs(u1.x) < std::fabs(u1.y)) {
                    if (std::fabs(u1.x) < std::fabs(u1.z)) {
                        u2 = Vector3D(1, 0, 0) - u1 * u1.x;
                    } else {
                        u2 = Vector3D(0, 0, 1) - u1 * u1.z;
                    }
                } else {
                    if (std::fabs(u1.y) < std::fabs(u1.z)) {
                        u2 = Vector3D(0, 1, 0) - u1 * u1.y;
                    } else {
                        u2 = Vector3D(0, 0, 1) - u1 * u1.z;
                    }
                }
                u2 = u2.Normalize();
            }

            // u3 is orthogonal to both u1 and u2
            Vector3D u3 = u1.Cross(u2);

            return Matrix3D(u1, u2, u3);
        }

        /**
         * @brief Accesses the matrix elements using row and column indices.
         *
         * @param row The row index (0, 1, or 2)
         * @param col The column index (0, 1, or 2)
         * @return The element at the specified row and column
         * @throws std::out_of_range if indices are out of bounds
         */
        [[nodiscard]] float operator()(int row, int col) const {
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                throw std::out_of_range("Matrix indices out of range");
            }

            const float* elements[3][3] = {
                {&m00, &m01, &m02},
                {&m10, &m11, &m12},
                {&m20, &m21, &m22}
            };

            return *elements[row][col];
        }

    };

    /**
     * @brief Free function to multiply a scalar with a matrix.
     *
     * Allows for expressions like: 2.0f * matrix
     *
     * @param scalar The scalar to multiply with
     * @param matrix The matrix to multiply
     * @return The result of scalar * matrix
     */
    inline Matrix3D operator*(float scalar, const Matrix3D& matrix) {
        return matrix * scalar;
    }

} // namespace Math

#endif // MATRIX3D_H