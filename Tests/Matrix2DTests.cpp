//
// Created by natha on 2025-04-28.
//

#include <iostream>

#include "Matrix2DTests.h"
#include "TestUtils.h"
#include "../Math/Matrix2D.h"

// Matrix2D tests
bool RunMatrix2DTests() {
    std::cout << "\n=== Matrix2D Tests ===\n";
    bool allPassed = true;


    // Constructor tests
    runTest("Matrix2D Default Constructor", []() {
        Math::Matrix2D m;
        // The default constructor doesn't initialize values, so we can't check specific values
        return true; // Just verify it compiles and runs
    });

    runTest("Matrix2D Constructor with Parameters", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        return m.m00 == 1.0f && m.m01 == 2.0f && m.m10 == 3.0f && m.m11 == 4.0f;
    });

    // Static method tests
    runTest("Matrix2D Identity", []() {
        Math::Matrix2D identity = Math::Matrix2D::Identity();
        return matrix2DEqual(identity, Math::Matrix2D(1.0f, 0.0f, 0.0f, 1.0f));
    });

    runTest("Matrix2D Zero", []() {
        Math::Matrix2D zero = Math::Matrix2D::Zero();
        return matrix2DEqual(zero, Math::Matrix2D(0.0f, 0.0f, 0.0f, 0.0f));
    });

    runTest("Matrix2D Rotation (Radians)", []() {
        Math::Matrix2D rot = Math::Matrix2D::RotationRad(M_PI / 2.0f);
        return matrix2DEqual(rot, Math::Matrix2D(0.0f, -1.0f, 1.0f, 0.0f), 1e-5f);
    });

    runTest("Matrix2D Rotation (Degrees)", []() {
        Math::Matrix2D rot = Math::Matrix2D::RotationDeg(90.0f);
        return matrix2DEqual(rot, Math::Matrix2D(0.0f, -1.0f, 1.0f, 0.0f), 1e-5f);
    });

    // Operator tests
    runTest("Matrix2D Multiplication", []() {
        Math::Matrix2D m1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m2(5.0f, 6.0f, 7.0f, 8.0f);
        Math::Matrix2D result = m1 * m2;
        return matrix2DEqual(result, Math::Matrix2D(19.0f, 22.0f, 43.0f, 50.0f));
    });

    runTest("Matrix2D Multiplication Assignment", []() {
        Math::Matrix2D m1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m2(5.0f, 6.0f, 7.0f, 8.0f);
        m1 *= m2;
        return matrix2DEqual(m1, Math::Matrix2D(19.0f, 22.0f, 43.0f, 50.0f));
    });

    runTest("Matrix2D Vector Multiplication", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Vector2D v(5.0f, 6.0f);
        Math::Vector2D result = m * v;
        return vector2DEqual(result, Math::Vector2D(17.0f, 39.0f));
    });

    runTest("Matrix2D Addition", []() {
        Math::Matrix2D m1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m2(5.0f, 6.0f, 7.0f, 8.0f);
        Math::Matrix2D result = m1 + m2;
        return matrix2DEqual(result, Math::Matrix2D(6.0f, 8.0f, 10.0f, 12.0f));
    });

    runTest("Matrix2D Addition Assignment", []() {
        Math::Matrix2D m1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m2(5.0f, 6.0f, 7.0f, 8.0f);
        m1 += m2;
        return matrix2DEqual(m1, Math::Matrix2D(6.0f, 8.0f, 10.0f, 12.0f));
    });

    runTest("Matrix2D Subtraction", []() {
        Math::Matrix2D m1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::Matrix2D m2(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D result = m1 - m2;
        return matrix2DEqual(result, Math::Matrix2D(4.0f, 4.0f, 4.0f, 4.0f));
    });

    runTest("Matrix2D Subtraction Assignment", []() {
        Math::Matrix2D m1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::Matrix2D m2(1.0f, 2.0f, 3.0f, 4.0f);
        m1 -= m2;
        return matrix2DEqual(m1, Math::Matrix2D(4.0f, 4.0f, 4.0f, 4.0f));
    });

    runTest("Matrix2D Scalar Division", []() {
        Math::Matrix2D m(2.0f, 4.0f, 6.0f, 8.0f);
        Math::Matrix2D result = m / 2.0f;
        return matrix2DEqual(result, Math::Matrix2D(1.0f, 2.0f, 3.0f, 4.0f));
    });

    runTest("Matrix2D Scalar Division Assignment", []() {
        Math::Matrix2D m(2.0f, 4.0f, 6.0f, 8.0f);
        m /= 2.0f;
        return matrix2DEqual(m, Math::Matrix2D(1.0f, 2.0f, 3.0f, 4.0f));
    });

    // Method tests
    runTest("Matrix2D Determinant", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        float det = m.Determinant();
        return floatEqual(det, -2.0f);
    });

    runTest("Matrix2D Transpose", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D transposed = m.Transpose();
        return matrix2DEqual(transposed, Math::Matrix2D(1.0f, 3.0f, 2.0f, 4.0f));
    });

    runTest("Matrix2D Inverse", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D inverse = m.Inverse();
        Math::Matrix2D identity = m * inverse;
        return matrix2DEqual(identity, Math::Matrix2D::Identity(), 1e-5f);
    });

    runTest("Matrix2D IsInvertible", []() {
        Math::Matrix2D invertible(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D nonInvertible(1.0f, 2.0f, 2.0f, 4.0f);
        return invertible.IsInvertible() && !nonInvertible.IsInvertible();
    });

    runTest("Matrix2D IsZero", []() {
        Math::Matrix2D zero = Math::Matrix2D::Zero();
        Math::Matrix2D nonZero(0.0f, 0.1f, 0.0f, 0.0f);
        return zero.IsZero() && !nonZero.IsZero();
    });

    runTest("Matrix2D IsIdentity", []() {
        Math::Matrix2D identity = Math::Matrix2D::Identity();
        Math::Matrix2D nonIdentity(1.0f, 0.1f, 0.0f, 1.0f);
        return identity.IsIdentity() && !nonIdentity.IsIdentity();
    });

    runTest("Matrix2D Adjoint", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D adjoint = m.Adjoint();
        return matrix2DEqual(adjoint, Math::Matrix2D(4.0f, -2.0f, -3.0f, 1.0f));
    });

    // Updated tests for the renamed methods
    runTest("Matrix2D GetScaled", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D scaled = m.GetScaled(2.0f, 3.0f);
        return matrix2DEqual(scaled, Math::Matrix2D(2.0f, 6.0f, 6.0f, 12.0f));
    });

    runTest("Matrix2D GetScaledUniform", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D scaled = m.GetScaled(2.0f);
        return matrix2DEqual(scaled, Math::Matrix2D(2.0f, 4.0f, 6.0f, 8.0f));
    });

    runTest("Matrix2D ScaleInPlace", []() {
        Math::Matrix2D m(1.0f, 2.0f, 3.0f, 4.0f);
        m.Scale(2.0f, 3.0f);
        return matrix2DEqual(m, Math::Matrix2D(2.0f, 6.0f, 6.0f, 12.0f));
    });

    // Updated tests for GetSheared and ShearInPlace
    runTest("Matrix2D GetSheared", []() {
        Math::Matrix2D m = Math::Matrix2D::Identity();
        Math::Matrix2D sheared = m.GetSheared(0.5f, 0.5f);

        // For a properly implemented GetSheared, we expect a standard 2D shear matrix
        // when applied to the identity matrix.
        // For a shear of (0.5, 0.5), the result should be [1, 0.5; 0.5, 1]
        return matrix2DEqual(sheared, Math::Matrix2D(1.0f, 0.5f, 0.5f, 1.0f));
    });

    runTest("Matrix2D ShearInPlace", []() {
        Math::Matrix2D m = Math::Matrix2D::Identity();
        m.Shear(0.5f, 0.5f);

        // For a properly implemented Shear, we expect the same result as GetSheared
        // For a shear of (0.5, 0.5), the result should be [1, 0.5; 0.5, 1]
        return matrix2DEqual(m, Math::Matrix2D(1.0f, 0.5f, 0.5f, 1.0f));
    });

    // Additional test to verify shearing with non-identity matrix
    runTest("Matrix2D GetSheared Non-Identity", []() {
        Math::Matrix2D m(2.0f, 1.0f, 3.0f, 4.0f);
        Math::Matrix2D sheared = m.GetSheared(0.5f, 0.5f);

        // For a non-identity matrix with shear of (0.5, 0.5), the result should include
        // the proper shearing transformation
        return matrix2DEqual(sheared, Math::Matrix2D(3.5f, 3.0f, 4.0f, 4.5f));
    });

    runTest("Matrix2D ShearInPlace Non-Identity", []() {
        Math::Matrix2D m(2.0f, 1.0f, 3.0f, 4.0f);
        m.Shear(0.5f, 0.5f);

        // For a non-identity matrix with in-place shear of (0.5, 0.5)
        // The result should match the GetSheared version
        return matrix2DEqual(m, Math::Matrix2D(3.5f, 3.0f, 4.0f, 4.5f));
    });

    runTest("Matrix2D Equality", []() {
        Math::Matrix2D m1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m2(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m3(1.1f, 2.0f, 3.0f, 4.0f);
        return (m1 == m2) && !(m1 == m3);
    });

    runTest("Matrix2D Inequality", []() {
        Math::Matrix2D m1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m2(1.0f, 2.0f, 3.0f, 4.0f);
        Math::Matrix2D m3(1.1f, 2.0f, 3.0f, 4.0f);
        return !(m1 != m2) && (m1 != m3);
    });

    runTest("Matrix2D GetRotatedRad", []() {
        Math::Matrix2D m = Math::Matrix2D::Identity();
        Math::Matrix2D rotated = m.GetRotatedRad(M_PI / 2.0f);
        return matrix2DEqual(rotated, Math::Matrix2D(0.0f, -1.0f, 1.0f, 0.0f), 1e-5f);
    });

    runTest("Matrix2D GetRotatedDeg", []() {
        Math::Matrix2D m = Math::Matrix2D::Identity();
        Math::Matrix2D rotated = m.GetRotatedDeg(90.0f);
        return matrix2DEqual(rotated, Math::Matrix2D(0.0f, -1.0f, 1.0f, 0.0f), 1e-5f);
    });

    runTest("Matrix2D RotateRad", []() {
        Math::Matrix2D m = Math::Matrix2D::Identity();
        m.RotateRad(M_PI / 2.0f);
        return matrix2DEqual(m, Math::Matrix2D(0.0f, -1.0f, 1.0f, 0.0f), 1e-5f);
    });

    runTest("Matrix2D RotateDeg", []() {
        Math::Matrix2D m = Math::Matrix2D::Identity();
        m.RotateDeg(90.0f);
        return matrix2DEqual(m, Math::Matrix2D(0.0f, -1.0f, 1.0f, 0.0f), 1e-5f);
    });

    return allPassed;
}