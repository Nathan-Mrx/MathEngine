//
// Created by natha on 2025-04-28.
//

#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <stdexcept>

#include "Vector3D.h"
#include "Constants.h"

namespace Math {

/**
 * @class Matrix4D
 * @brief A 4x4 matrix for 3D transformations with homogeneous coordinates.
 *
 * This class represents a 4x4 matrix that can be used for 3D transformations including
 * translation, rotation, scaling, projection, and view transformations. The matrix is stored
 * in column-major order for better compatibility with graphics APIs.
 *
 * The elements are indexed as follows:
 * @verbatim
 *   | m00 m01 m02 m03 |
 *   | m10 m11 m12 m13 |
 *   | m20 m21 m22 m23 |
 *   | m30 m31 m32 m33 |
 * @endverbatim
 *
 * Where each column represents a vector in the transformation:
 * - Column 0 (m00, m10, m20, m30): X axis direction + scale
 * - Column 1 (m01, m11, m21, m31): Y axis direction + scale
 * - Column 2 (m02, m12, m22, m32): Z axis direction + scale
 * - Column 3 (m03, m13, m23, m33): Translation (position) + w-coordinate handling
 */
struct Matrix4D {
    // Matrix elements stored in row-major order
    float m00, m01, m02, m03;  // First row
    float m10, m11, m12, m13;  // Second row
    float m20, m21, m22, m23;  // Third row
    float m30, m31, m32, m33;  // Fourth row

    /**
     * @brief Default constructor - creates an identity matrix.
     *
     * Creates a 4x4 identity matrix with ones on the main diagonal and zeros elsewhere.
     */
    constexpr Matrix4D()
        : m00(1.0f), m01(0.0f), m02(0.0f), m03(0.0f),
          m10(0.0f), m11(1.0f), m12(0.0f), m13(0.0f),
          m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
          m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f) {}

    /**
     * @brief Constructor with 16 elements specified in row-major order.
     *
     * @param m00 Element at row 0, column 0
     * @param m01 Element at row 0, column 1
     * @param m02 Element at row 0, column 2
     * @param m03 Element at row 0, column 3
     * @param m10 Element at row 1, column 0
     * @param m11 Element at row 1, column 1
     * @param m12 Element at row 1, column 2
     * @param m13 Element at row 1, column 3
     * @param m20 Element at row 2, column 0
     * @param m21 Element at row 2, column 1
     * @param m22 Element at row 2, column 2
     * @param m23 Element at row 2, column 3
     * @param m30 Element at row 3, column 0
     * @param m31 Element at row 3, column 1
     * @param m32 Element at row 3, column 2
     * @param m33 Element at row 3, column 3
     */
    constexpr Matrix4D(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    ) : m00(m00), m01(m01), m02(m02), m03(m03),
        m10(m10), m11(m11), m12(m12), m13(m13),
        m20(m20), m21(m21), m22(m22), m23(m23),
        m30(m30), m31(m31), m32(m32), m33(m33) {}

    /**
     * @brief Constructor from 4 column vectors.
     *
     * @param col0 First column vector (x-axis)
     * @param col1 Second column vector (y-axis)
     * @param col2 Third column vector (z-axis)
     * @param col3 Fourth column vector (translation)
     */
    constexpr Matrix4D(const Vector3D& col0, const Vector3D& col1, const Vector3D& col2, const Vector3D& col3)
        : m00(col0.x), m01(col1.x), m02(col2.x), m03(col3.x),
          m10(col0.y), m11(col1.y), m12(col2.y), m13(col3.y),
          m20(col0.z), m21(col1.z), m22(col2.z), m23(col3.z),
          m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f) {}

    /**
     * @brief Constructor from an array of 16 elements in row-major order.
     *
     * @param elements Array of 16 floating-point values in row-major order
     */
    explicit constexpr Matrix4D(const std::array<float, 16>& elements)
        : m00(elements[0]), m01(elements[1]), m02(elements[2]), m03(elements[3]),
          m10(elements[4]), m11(elements[5]), m12(elements[6]), m13(elements[7]),
          m20(elements[8]), m21(elements[9]), m22(elements[10]), m23(elements[11]),
          m30(elements[12]), m31(elements[13]), m32(elements[14]), m33(elements[15]) {}

    /**
     * @brief Get element at specified row and column.
     *
     * @param row Row index (0-3)
     * @param col Column index (0-3)
     * @return The element at the specified position
     * @throws std::out_of_range if indices are out of bounds
     */
    [[nodiscard]] float GetElement(int row, int col) const {
        if (row < 0 || row > 3 || col < 0 || col > 3) {
            throw std::out_of_range("Matrix4D indices out of range");
        }

        const float* data = &m00;
        return data[row * 4 + col];
    }

    /**
     * @brief Set element at specified row and column.
     *
     * @param row Row index (0-3)
     * @param col Column index (0-3)
     * @param value New value for the element
     * @throws std::out_of_range if indices are out of bounds
     */
    void SetElement(int row, int col, float value) {
        if (row < 0 || row > 3 || col < 0 || col > 3) {
            throw std::out_of_range("Matrix4D indices out of range");
        }

        float* data = &m00;
        data[row * 4 + col] = value;
    }

    /**
     * @brief Get a row of the matrix as a 4-element array.
     *
     * @param row Row index (0-3)
     * @return Array containing the row elements
     * @throws std::out_of_range if row index is out of bounds
     */
    [[nodiscard]] std::array<float, 4> GetRow(int row) const {
        if (row < 0 || row > 3) {
            throw std::out_of_range("Matrix4D row index out of range");
        }

        switch (row) {
            case 0: return {m00, m01, m02, m03};
            case 1: return {m10, m11, m12, m13};
            case 2: return {m20, m21, m22, m23};
            case 3: return {m30, m31, m32, m33};
            default: return {0.0f, 0.0f, 0.0f, 0.0f}; // Unreachable but needed for compiler
        }
    }

    /**
     * @brief Set an entire row of the matrix.
     *
     * @param row Row index (0-3)
     * @param values Array of 4 values for the row
     * @throws std::out_of_range if row index is out of bounds
     */
    void SetRow(int row, const std::array<float, 4>& values) {
        if (row < 0 || row > 3) {
            throw std::out_of_range("Matrix4D row index out of range");
        }

        switch (row) {
            case 0:
                m00 = values[0]; m01 = values[1]; m02 = values[2]; m03 = values[3];
                break;
            case 1:
                m10 = values[0]; m11 = values[1]; m12 = values[2]; m13 = values[3];
                break;
            case 2:
                m20 = values[0]; m21 = values[1]; m22 = values[2]; m23 = values[3];
                break;
            case 3:
                m30 = values[0]; m31 = values[1]; m32 = values[2]; m33 = values[3];
                break;
        }
    }

    /**
     * @brief Get a column of the matrix as a 4-element array.
     *
     * @param col Column index (0-3)
     * @return Array containing the column elements
     * @throws std::out_of_range if column index is out of bounds
     */
    [[nodiscard]] std::array<float, 4> GetColumn(int col) const {
        if (col < 0 || col > 3) {
            throw std::out_of_range("Matrix4D column index out of range");
        }

        switch (col) {
            case 0: return {m00, m10, m20, m30};
            case 1: return {m01, m11, m21, m31};
            case 2: return {m02, m12, m22, m32};
            case 3: return {m03, m13, m23, m33};
            default: return {0.0f, 0.0f, 0.0f, 0.0f}; // Unreachable but needed for compiler
        }
    }

    /**
     * @brief Set an entire column of the matrix.
     *
     * @param col Column index (0-3)
     * @param values Array of 4 values for the column
     * @throws std::out_of_range if column index is out of bounds
     */
    void SetColumn(int col, const std::array<float, 4>& values) {
        if (col < 0 || col > 3) {
            throw std::out_of_range("Matrix4D column index out of range");
        }

        switch (col) {
            case 0:
                m00 = values[0]; m10 = values[1]; m20 = values[2]; m30 = values[3];
                break;
            case 1:
                m01 = values[0]; m11 = values[1]; m21 = values[2]; m31 = values[3];
                break;
            case 2:
                m02 = values[0]; m12 = values[1]; m22 = values[2]; m32 = values[3];
                break;
            case 3:
                m03 = values[0]; m13 = values[1]; m23 = values[2]; m33 = values[3];
                break;
        }
    }

    /**
     * @brief Convert the matrix to a flat array of 16 elements in row-major order.
     *
     * @return Array of 16 floating-point values representing the matrix
     */
    [[nodiscard]] std::array<float, 16> ToArray() const {
        return {
            m00, m01, m02, m03,
            m10, m11, m12, m13,
            m20, m21, m22, m23,
            m30, m31, m32, m33
        };
    }

    /**
     * @brief Multiplies this matrix by another matrix.
     *
     * Performs matrix multiplication: this * other
     *
     * @param other The matrix to multiply with
     * @return The product of the two matrices
     */
    [[nodiscard]] constexpr Matrix4D operator*(const Matrix4D& other) const {
        return Matrix4D(
            // Row 0
            m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30,
            m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31,
            m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32,
            m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33,

            // Row 1
            m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30,
            m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31,
            m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32,
            m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33,

            // Row 2
            m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30,
            m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31,
            m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32,
            m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33,

            // Row 3
            m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30,
            m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31,
            m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32,
            m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33
        );
    }

    /**
     * @brief Multiplies this matrix by another matrix and assigns the result to this matrix.
     *
     * @param other The matrix to multiply with
     * @return Reference to this matrix after multiplication
     */
    Matrix4D& operator*=(const Matrix4D& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Transforms a 3D vector using this matrix.
     *
     * Treats the vector as a point (w=1) for proper translation.
     *
     * @param vector The vector to transform
     * @return The transformed vector
     */
    [[nodiscard]] Vector3D TransformPoint(const Vector3D& vector) const {
        float w = m30 * vector.x + m31 * vector.y + m32 * vector.z + m33;
        if (w == 0.0f) {
            return Vector3D(0.0f, 0.0f, 0.0f);
        }

        float invW = 1.0f / w;
        return Vector3D(
            (m00 * vector.x + m01 * vector.y + m02 * vector.z + m03) * invW,
            (m10 * vector.x + m11 * vector.y + m12 * vector.z + m13) * invW,
            (m20 * vector.x + m21 * vector.y + m22 * vector.z + m23) * invW
        );
    }

    /**
     * @brief Transforms a 3D vector using this matrix, ignoring translation.
     *
     * Treats the vector as a direction (w=0) to ignore translation.
     *
     * @param vector The vector to transform
     * @return The transformed vector
     */
    [[nodiscard]] Vector3D TransformVector(const Vector3D& vector) const {
        return Vector3D(
            m00 * vector.x + m01 * vector.y + m02 * vector.z,
            m10 * vector.x + m11 * vector.y + m12 * vector.z,
            m20 * vector.x + m21 * vector.y + m22 * vector.z
        );
    }

    /**
     * @brief Multiply this matrix by a scalar.
     *
     * @param scalar The scalar to multiply by
     * @return The product of this matrix and the scalar
     */
    [[nodiscard]] constexpr Matrix4D operator*(float scalar) const {
        return Matrix4D(
            m00 * scalar, m01 * scalar, m02 * scalar, m03 * scalar,
            m10 * scalar, m11 * scalar, m12 * scalar, m13 * scalar,
            m20 * scalar, m21 * scalar, m22 * scalar, m23 * scalar,
            m30 * scalar, m31 * scalar, m32 * scalar, m33 * scalar
        );
    }

    /**
     * @brief Multiply this matrix by a scalar and assign the result to this matrix.
     *
     * @param scalar The scalar to multiply by
     * @return Reference to this matrix after multiplication
     */
    Matrix4D& operator*=(float scalar) {
        m00 *= scalar; m01 *= scalar; m02 *= scalar; m03 *= scalar;
        m10 *= scalar; m11 *= scalar; m12 *= scalar; m13 *= scalar;
        m20 *= scalar; m21 *= scalar; m22 *= scalar; m23 *= scalar;
        m30 *= scalar; m31 *= scalar; m32 *= scalar; m33 *= scalar;
        return *this;
    }

    /**
     * @brief Add another matrix to this matrix.
     *
     * @param other The matrix to add
     * @return The sum of the two matrices
     */
    [[nodiscard]] constexpr Matrix4D operator+(const Matrix4D& other) const {
        return Matrix4D(
            m00 + other.m00, m01 + other.m01, m02 + other.m02, m03 + other.m03,
            m10 + other.m10, m11 + other.m11, m12 + other.m12, m13 + other.m13,
            m20 + other.m20, m21 + other.m21, m22 + other.m22, m23 + other.m23,
            m30 + other.m30, m31 + other.m31, m32 + other.m32, m33 + other.m33
        );
    }

    /**
     * @brief Add another matrix to this matrix and assign the result to this matrix.
     *
     * @param other The matrix to add
     * @return Reference to this matrix after addition
     */
    Matrix4D& operator+=(const Matrix4D& other) {
        m00 += other.m00; m01 += other.m01; m02 += other.m02; m03 += other.m03;
        m10 += other.m10; m11 += other.m11; m12 += other.m12; m13 += other.m13;
        m20 += other.m20; m21 += other.m21; m22 += other.m22; m23 += other.m23;
        m30 += other.m30; m31 += other.m31; m32 += other.m32; m33 += other.m33;
        return *this;
    }

    /**
     * @brief Subtract another matrix from this matrix.
     *
     * @param other The matrix to subtract
     * @return The difference of the two matrices
     */
    [[nodiscard]] constexpr Matrix4D operator-(const Matrix4D& other) const {
        return Matrix4D(
            m00 - other.m00, m01 - other.m01, m02 - other.m02, m03 - other.m03,
            m10 - other.m10, m11 - other.m11, m12 - other.m12, m13 - other.m13,
            m20 - other.m20, m21 - other.m21, m22 - other.m22, m23 - other.m23,
            m30 - other.m30, m31 - other.m31, m32 - other.m32, m33 - other.m33
        );
    }

    /**
     * @brief Subtract another matrix from this matrix and assign the result to this matrix.
     *
     * @param other The matrix to subtract
     * @return Reference to this matrix after subtraction
     */
    Matrix4D& operator-=(const Matrix4D& other) {
        m00 -= other.m00; m01 -= other.m01; m02 -= other.m02; m03 -= other.m03;
        m10 -= other.m10; m11 -= other.m11; m12 -= other.m12; m13 -= other.m13;
        m20 -= other.m20; m21 -= other.m21; m22 -= other.m22; m23 -= other.m23;
        m30 -= other.m30; m31 -= other.m31; m32 -= other.m32; m33 -= other.m33;
        return *this;
    }

    /**
     * @brief Negate this matrix.
     *
     * @return The negated matrix
     */
    [[nodiscard]] constexpr Matrix4D operator-() const {
        return Matrix4D(
            -m00, -m01, -m02, -m03,
            -m10, -m11, -m12, -m13,
            -m20, -m21, -m22, -m23,
            -m30, -m31, -m32, -m33
        );
    }

    /**
     * @brief Divide this matrix by a scalar.
     *
     * @param scalar The scalar to divide by
     * @return The quotient of this matrix and the scalar
     * @throws std::invalid_argument if scalar is zero
     */
    [[nodiscard]] constexpr Matrix4D operator/(float scalar) const {
        if (scalar == 0.0f) {
            throw std::invalid_argument("Division by zero");
        }

        float invScalar = 1.0f / scalar;
        return Matrix4D(
            m00 * invScalar, m01 * invScalar, m02 * invScalar, m03 * invScalar,
            m10 * invScalar, m11 * invScalar, m12 * invScalar, m13 * invScalar,
            m20 * invScalar, m21 * invScalar, m22 * invScalar, m23 * invScalar,
            m30 * invScalar, m31 * invScalar, m32 * invScalar, m33 * invScalar
        );
    }

    /**
     * @brief Divide this matrix by a scalar and assign the result to this matrix.
     *
     * @param scalar The scalar to divide by
     * @return Reference to this matrix after division
     * @throws std::invalid_argument if scalar is zero
     */
    Matrix4D& operator/=(float scalar) {
        if (scalar == 0.0f) {
            throw std::invalid_argument("Division by zero");
        }

        float invScalar = 1.0f / scalar;
        m00 *= invScalar; m01 *= invScalar; m02 *= invScalar; m03 *= invScalar;
        m10 *= invScalar; m11 *= invScalar; m12 *= invScalar; m13 *= invScalar;
        m20 *= invScalar; m21 *= invScalar; m22 *= invScalar; m23 *= invScalar;
        m30 *= invScalar; m31 *= invScalar; m32 *= invScalar; m33 *= invScalar;
        return *this;
    }

    /**
     * @brief Check if this matrix equals another matrix within a small epsilon.
     *
     * @param other The matrix to compare with
     * @param epsilon The maximum difference allowed for equality
     * @return True if matrices are approximately equal, false otherwise
     */
    [[nodiscard]] bool Equals(const Matrix4D& other, float epsilon = Constants::EPSILON) const {
        return
            std::fabs(m00 - other.m00) <= epsilon && std::fabs(m01 - other.m01) <= epsilon &&
            std::fabs(m02 - other.m02) <= epsilon && std::fabs(m03 - other.m03) <= epsilon &&
            std::fabs(m10 - other.m10) <= epsilon && std::fabs(m11 - other.m11) <= epsilon &&
            std::fabs(m12 - other.m12) <= epsilon && std::fabs(m13 - other.m13) <= epsilon &&
            std::fabs(m20 - other.m20) <= epsilon && std::fabs(m21 - other.m21) <= epsilon &&
            std::fabs(m22 - other.m22) <= epsilon && std::fabs(m23 - other.m23) <= epsilon &&
            std::fabs(m30 - other.m30) <= epsilon && std::fabs(m31 - other.m31) <= epsilon &&
            std::fabs(m32 - other.m32) <= epsilon && std::fabs(m33 - other.m33) <= epsilon;
    }

    /**
     * @brief Equality operator.
     *
     * Checks if this matrix equals another matrix with a small epsilon tolerance.
     *
     * @param other The matrix to compare with
     * @return True if matrices are approximately equal, false otherwise
     */
    bool operator==(const Matrix4D& other) const {
        return Equals(other);
    }

    /**
     * @brief Inequality operator.
     *
     * @param other The matrix to compare with
     * @return True if matrices are not approximately equal, false otherwise
     */
    bool operator!=(const Matrix4D& other) const {
        return !(*this == other);
    }

    /**
     * @brief Calculate the determinant of the matrix.
     *
     * @return The determinant value
     */
    [[nodiscard]] float Determinant() const {
        // Calculate cofactors for the first row
        float c00 = m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31);
        float c01 = m10 * (m22 * m33 - m23 * m32) - m12 * (m20 * m33 - m23 * m30) + m13 * (m20 * m32 - m22 * m30);
        float c02 = m10 * (m21 * m33 - m23 * m31) - m11 * (m20 * m33 - m23 * m30) + m13 * (m20 * m31 - m21 * m30);
        float c03 = m10 * (m21 * m32 - m22 * m31) - m11 * (m20 * m32 - m22 * m30) + m12 * (m20 * m31 - m21 * m30);

        // Calculate determinant using cofactors of the first row
        return m00 * c00 - m01 * c01 + m02 * c02 - m03 * c03;
    }

    /**
     * @brief Calculate the trace of the matrix (sum of diagonal elements).
     *
     * @return The trace value
     */
    [[nodiscard]] float Trace() const {
        return m00 + m11 + m22 + m33;
    }

    /**
     * @brief Transpose this matrix.
     *
     * @return The transposed matrix
     */
    [[nodiscard]] constexpr Matrix4D Transpose() const {
        return Matrix4D(
            m00, m10, m20, m30,
            m01, m11, m21, m31,
            m02, m12, m22, m32,
            m03, m13, m23, m33
        );
    }

    /**
     * @brief Transpose this matrix in place.
     */
    void TransposeInPlace() {
        std::swap(m01, m10);
        std::swap(m02, m20);
        std::swap(m03, m30);
        std::swap(m12, m21);
        std::swap(m13, m31);
        std::swap(m23, m32);
    }

    /**
     * @brief Calculate the adjoint (adjugate) of this matrix.
     *
     * The adjoint is the transpose of the cofactor matrix.
     *
     * @return The adjoint matrix
     */
    [[nodiscard]] Matrix4D Adjoint() const {
        Matrix4D result;

        // Calculate the cofactors and place them in the transposed position
        auto minor = [this](int i0, int j0) -> float {
            // Create a 3x3 submatrix by excluding row i0 and column j0
            float s[3][3];
            int si = 0;
            for (int i = 0; i < 4; i++) {
                if (i == i0) continue;
                int sj = 0;
                for (int j = 0; j < 4; j++) {
                    if (j == j0) continue;
                    s[si][sj] = GetElement(i, j);
                    sj++;
                }
                si++;
            }

            // Calculate the determinant of the 3x3 submatrix
            return s[0][0] * (s[1][1] * s[2][2] - s[1][2] * s[2][1]) -
                   s[0][1] * (s[1][0] * s[2][2] - s[1][2] * s[2][0]) +
                   s[0][2] * (s[1][0] * s[2][1] - s[1][1] * s[2][0]);
        };

        // Fill the result matrix with cofactors (transposed)
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // Cofactor sign: (-1)^(i+j)
                float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
                result.SetElement(j, i, sign * minor(i, j)); // Transposed position
            }
        }

        return result;
    }

    /**
     * @brief Calculate the inverse of this matrix.
     *
     * @return The inverse matrix
     * @throws std::runtime_error if the matrix is not invertible (determinant is zero)
     */
    [[nodiscard]] Matrix4D Inverse() const {
        float det = Determinant();
        if (std::fabs(det) < Constants::EPSILON) {
            throw std::runtime_error("Matrix is not invertible (determinant is zero)");
        }

        return Adjoint() / det;
    }

    /**
     * @brief Invert this matrix in place.
     *
     * @throws std::runtime_error if the matrix is not invertible (determinant is zero)
     */
    void InvertInPlace() {
        *this = Inverse();
    }

    /**
     * @brief Scale this matrix by the given factors.
     *
     * @param scaleX Scale factor along X axis
     * @param scaleY Scale factor along Y axis
     * @param scaleZ Scale factor along Z axis
     * @return The scaled matrix
     */
    [[nodiscard]] Matrix4D Scale(float scaleX, float scaleY, float scaleZ) const {
        Matrix4D result = *this;

        // Scale the first three columns
        result.m00 *= scaleX; result.m10 *= scaleX; result.m20 *= scaleX;
        result.m01 *= scaleY; result.m11 *= scaleY; result.m21 *= scaleY;
        result.m02 *= scaleZ; result.m12 *= scaleZ; result.m22 *= scaleZ;

        return result;
    }

    /**
     * @brief Scale this matrix by the given vector.
     *
     * @param scale 3D vector with scale factors for each axis
     * @return The scaled matrix
     */
    [[nodiscard]] Matrix4D Scale(const Vector3D& scale) const {
        return Scale(scale.x, scale.y, scale.z);
    }

    /**
     * @brief Scale this matrix uniformly by the given factor.
     *
     * @param scale Uniform scale factor for all axes
     * @return The scaled matrix
     */
    [[nodiscard]] Matrix4D Scale(float scale) const {
        return Scale(scale, scale, scale);
    }

    /**
     * @brief Translate this matrix by the given offsets.
     *
     * @param x Translation along X axis
     * @param y Translation along Y axis
     * @param z Translation along Z axis
     * @return The translated matrix
     */
    [[nodiscard]] Matrix4D Translate(float x, float y, float z) const {
        Matrix4D result = *this;

        // Apply translation to the fourth column
        result.m03 += m00 * x + m01 * y + m02 * z;
        result.m13 += m10 * x + m11 * y + m12 * z;
        result.m23 += m20 * x + m21 * y + m22 * z;
        result.m33 += m30 * x + m31 * y + m32 * z;

        return result;
    }

    /**
     * @brief Translate this matrix by the given vector.
     *
     * @param translation 3D vector with translation offsets
     * @return The translated matrix
     */
    [[nodiscard]] Matrix4D Translate(const Vector3D& translation) const {
        return Translate(translation.x, translation.y, translation.z);
    }

    /**
     * @brief Rotate this matrix around the X axis.
     *
     * @param angleRadians Rotation angle in radians
     * @return The rotated matrix
     */
    [[nodiscard]] Matrix4D RotateX(float angleRadians) const {
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        Matrix4D rotation;
        rotation.m11 = c;
        rotation.m12 = -s;
        rotation.m21 = s;
        rotation.m22 = c;

        return *this * rotation;
    }

    /**
     * @brief Rotate this matrix around the Y axis.
     *
     * @param angleRadians Rotation angle in radians
     * @return The rotated matrix
     */
    [[nodiscard]] Matrix4D RotateY(float angleRadians) const {
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        Matrix4D rotation;
        rotation.m00 = c;
        rotation.m02 = s;
        rotation.m20 = -s;
        rotation.m22 = c;

        return *this * rotation;
    }

    /**
     * @brief Rotate this matrix around the Z axis.
     *
     * @param angleRadians Rotation angle in radians
     * @return The rotated matrix
     */
    [[nodiscard]] Matrix4D RotateZ(float angleRadians) const {
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        Matrix4D rotation;
        rotation.m00 = c;
        rotation.m01 = -s;
        rotation.m10 = s;
        rotation.m11 = c;

        return *this * rotation;
    }

    /**
     * @brief Rotate this matrix around an arbitrary axis.
     *
     * @param axis Normalized rotation axis
     * @param angleRadians Rotation angle in radians
     * @return The rotated matrix
     */
    [[nodiscard]] Matrix4D Rotate(const Vector3D& axis, float angleRadians) const {
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);
        float t = 1.0f - c;

        // Normalize the axis
        Vector3D nAxis = axis.GetNormalized();
        float x = nAxis.x;
        float y = nAxis.y;
        float z = nAxis.z;

        // Create the rotation matrix
        Matrix4D rotation(
            // First row
            t * x * x + c,
            t * x * y - s * z,
            t * x * z + s * y,
            0.0f,

            // Second row
            t * x * y + s * z,
            t * y * y + c,
            t * y * z - s * x,
            0.0f,

            // Third row
            t * x * z - s * y,
            t * y * z + s * x,
            t * z * z + c,
            0.0f,

            // Fourth row
            0.0f, 0.0f, 0.0f, 1.0f
        );

        return *this * rotation;
    }

    /**
     * @brief Creates a perspective projection matrix.
     *
     * @param fovYRadians Vertical field of view in radians
     * @param aspectRatio Width divided by height of the viewport
     * @param nearPlane Distance to the near clipping plane (must be positive)
     * @param farPlane Distance to the far clipping plane (must be greater than nearPlane)
     * @return A perspective projection matrix
     * @throws std::invalid_argument if nearPlane <= 0 or farPlane <= nearPlane
     */
    [[nodiscard]] static Matrix4D CreatePerspective(float fovYRadians, float aspectRatio, float nearPlane, float farPlane) {
        if (nearPlane <= 0.0f) {
            throw std::invalid_argument("Near plane must be positive");
        }
        if (farPlane <= nearPlane) {
            throw std::invalid_argument("Far plane must be greater than near plane");
        }

        float tanHalfFovy = std::tan(fovYRadians * 0.5f);
        float f = 1.0f / tanHalfFovy;
        float nf = 1.0f / (nearPlane - farPlane);

        return Matrix4D(
            f / aspectRatio, 0.0f, 0.0f, 0.0f,
            0.0f, f, 0.0f, 0.0f,
            0.0f, 0.0f, (farPlane + nearPlane) * nf, -1.0f,
            0.0f, 0.0f, 2.0f * farPlane * nearPlane * nf, 0.0f
        );
    }

    /**
     * @brief Creates an orthographic projection matrix.
     *
     * @param left Left coordinate of the viewport
     * @param right Right coordinate of the viewport
     * @param bottom Bottom coordinate of the viewport
     * @param top Top coordinate of the viewport
     * @param nearPlane Distance to the near clipping plane
     * @param farPlane Distance to the far clipping plane
     * @return An orthographic projection matrix
     * @throws std::invalid_argument if left = right, bottom = top, or nearPlane = farPlane
     */
    [[nodiscard]] static Matrix4D CreateOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        if (left == right) {
            throw std::invalid_argument("Left cannot equal right");
        }
        if (bottom == top) {
            throw std::invalid_argument("Bottom cannot equal top");
        }
        if (nearPlane == farPlane) {
            throw std::invalid_argument("Near plane cannot equal far plane");
        }

        float invWidth = 1.0f / (right - left);
        float invHeight = 1.0f / (top - bottom);
        float invDepth = 1.0f / (farPlane - nearPlane);

        return Matrix4D(
            2.0f * invWidth, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f * invHeight, 0.0f, 0.0f,
            0.0f, 0.0f, -2.0f * invDepth, 0.0f,
            -(right + left) * invWidth, -(top + bottom) * invHeight, -(farPlane + nearPlane) * invDepth, 1.0f
        );
    }

    /**
     * @brief Creates a view matrix for looking at a target from a specific position.
     *
     * @param eye Position of the camera
     * @param target Position to look at
     * @param up Up vector (typically Vector3D(0, 1, 0))
     * @return A view matrix
     */
    [[nodiscard]] static Matrix4D CreateLookAt(const Vector3D& eye, const Vector3D& target, const Vector3D& up) {
        Vector3D f = (target - eye).GetNormalized();
        Vector3D s = f.Cross(up).GetNormalized();
        Vector3D u = s.Cross(f);

        return Matrix4D(
            s.x, s.y, s.z, -s.Dot(eye),
            u.x, u.y, u.z, -u.Dot(eye),
            -f.x, -f.y, -f.z, f.Dot(eye),
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    /**
     * @brief Creates a translation matrix.
     *
     * @param x Translation along X axis
     * @param y Translation along Y axis
     * @param z Translation along Z axis
     * @return A translation matrix
     */
    [[nodiscard]] static Matrix4D CreateTranslation(float x, float y, float z) {
        Matrix4D result;
        result.m03 = x;
        result.m13 = y;
        result.m23 = z;
        return result;
    }

    /**
     * @brief Creates a translation matrix.
     *
     * @param translation Vector with translation values for each axis
     * @return A translation matrix
     */
    [[nodiscard]] static Matrix4D CreateTranslation(const Vector3D& translation) {
        return CreateTranslation(translation.x, translation.y, translation.z);
    }

    /**
     * @brief Creates a scaling matrix.
     *
     * @param scaleX Scale factor along X axis
     * @param scaleY Scale factor along Y axis
     * @param scaleZ Scale factor along Z axis
     * @return A scaling matrix
     */
    [[nodiscard]] static Matrix4D CreateScale(float scaleX, float scaleY, float scaleZ) {
        Matrix4D result;
        result.m00 = scaleX;
        result.m11 = scaleY;
        result.m22 = scaleZ;
        return result;
    }

    /**
     * @brief Creates a scaling matrix.
     *
     * @param scale Vector with scale factors for each axis
     * @return A scaling matrix
     */
    [[nodiscard]] static Matrix4D CreateScale(const Vector3D& scale) {
        return CreateScale(scale.x, scale.y, scale.z);
    }

    /**
     * @brief Creates a uniform scaling matrix.
     *
     * @param scale Uniform scale factor for all axes
     * @return A uniform scaling matrix
     */
    [[nodiscard]] static Matrix4D CreateScale(float scale) {
        return CreateScale(scale, scale, scale);
    }

    /**
     * @brief Creates a rotation matrix around the X axis.
     *
     * @param angleRadians Rotation angle in radians
     * @return A rotation matrix
     */
    [[nodiscard]] static Matrix4D CreateRotationX(float angleRadians) {
    float cosAngle = std::cos(angleRadians);
    float sinAngle = std::sin(angleRadians);

    return Matrix4D(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosAngle, sinAngle, 0.0f,
        0.0f, -sinAngle, cosAngle, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

    /**
     * @brief Creates a rotation matrix around the Y axis.
     *
     * @param angleRadians Rotation angle in radians
     * @return A rotation matrix
     */
    [[nodiscard]] static Matrix4D CreateRotationY(float angleRadians) {
    float cosAngle = std::cos(angleRadians);
    float sinAngle = std::sin(angleRadians);

    return Matrix4D(
        cosAngle, 0.0f, -sinAngle, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sinAngle, 0.0f, cosAngle, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

    /**
     * @brief Creates a rotation matrix around the Z axis.
     *
     * @param angleRadians Rotation angle in radians
     * @return A rotation matrix
     */
    [[nodiscard]] static Matrix4D CreateRotationZ(float angleRadians) {
    float cosAngle = std::cos(angleRadians);
    float sinAngle = std::sin(angleRadians);

    return Matrix4D(
        cosAngle, sinAngle, 0.0f, 0.0f,
        -sinAngle, cosAngle, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

    /**
     * @brief Creates a rotation matrix around an arbitrary axis.
     *
     * @param axis Normalized rotation axis
     * @param angleRadians Rotation angle in radians
     * @return A rotation matrix
     */
    [[nodiscard]] static Matrix4D CreateRotation(const Vector3D& axis, float angleRadians) {
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);
        float t = 1.0f - c;

        // Normalize the axis
        Vector3D nAxis = axis.GetNormalized();
        float x = nAxis.x;
        float y = nAxis.y;
        float z = nAxis.z;

        return Matrix4D(
            // First row
            t * x * x + c,
            t * x * y - s * z,
            t * x * z + s * y,
            0.0f,

            // Second row
            t * x * y + s * z,
            t * y * y + c,
            t * y * z - s * x,
            0.0f,

            // Third row
            t * x * z - s * y,
            t * y * z + s * x,
            t * z * z + c,
            0.0f,

            // Fourth row
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    /**
     * @brief Creates a transformation matrix from a position, rotation axis and angle, and scale.
     *
     * @param position Translation vector
     * @param rotationAxis Normalized rotation axis
     * @param rotationAngleRadians Rotation angle in radians
     * @param scale Scale vector
     * @return A transformation matrix
     */
    [[nodiscard]] static Matrix4D CreateTransformation(
        const Vector3D& position,
        const Vector3D& rotationAxis,
        float rotationAngleRadians,
        const Vector3D& scale
    ) {
        Matrix4D scaleMatrix = CreateScale(scale);
        Matrix4D rotationMatrix = CreateRotation(rotationAxis, rotationAngleRadians);
        Matrix4D translationMatrix = CreateTranslation(position);

        // Combine transformations: first scale, then rotate, then translate
        return translationMatrix * rotationMatrix * scaleMatrix;
    }

    /**
     * @brief Output stream operator for debugging.
     *
     * @param os Output stream
     * @param matrix Matrix to output
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix4D& matrix) {
        os << "Matrix4D[\n"
           << "  [" << matrix.m00 << ", " << matrix.m01 << ", " << matrix.m02 << ", " << matrix.m03 << "]\n"
           << "  [" << matrix.m10 << ", " << matrix.m11 << ", " << matrix.m12 << ", " << matrix.m13 << "]\n"
           << "  [" << matrix.m20 << ", " << matrix.m21 << ", " << matrix.m22 << ", " << matrix.m23 << "]\n"
           << "  [" << matrix.m30 << ", " << matrix.m31 << ", " << matrix.m32 << ", " << matrix.m33 << "]\n"
           << "]";
        return os;
    }

    /**
     * @brief Convert the matrix to a string representation.
     *
     * @return String representation of the matrix
     */
    [[nodiscard]] std::string ToString() const {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    /**
     * @brief Returns an Identity matrix.
     *
     * @return Identity matrix
     */
    [[nodiscard]] static Matrix4D Identity() {
        return Matrix4D(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    /**
     * @brief Returns a zero matrix.
     *
     * @return Zero matrix
     */
    [[nodiscard]] static Matrix4D Zero() {
        return Matrix4D(
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        );
    }

    /**
     * @brief Tries to invert the matrix.
     *
     * @param outMatrix Reference to the output matrix
     * @return True if the matrix was inverted successfully, false otherwise
     */
    [[nodiscard]] bool TryInverse(Matrix4D& outMatrix) const {
        try {
            outMatrix = Inverse();
            return true;
        } catch (const std::runtime_error&) {
            return false;
        }
    }

};

} // namespace Math

#endif // MATRIX4D_H