//
// Created by natha on 2025-04-29.
//

#include <iostream>

#include "Matrix3DTests.h"
#include "TestUtils.h"
#include "../Math/Matrix3D.h"
#include "../Math/Vector3D.h"
#include "../Math/Constants.h"

// Matrix3D tests
bool RunMatrix3DTests() {
    std::cout << "\n=== Matrix3D Tests ===\n";
    bool allPassed = true;

    // Constructor tests
    runTest("Matrix3D Default Constructor", []() {
        Math::Matrix3D m;
        // The default constructor doesn't initialize values, so we can't check specific values
        return true; // Just verify it compiles and runs
    });

    runTest("Matrix3D Constructor with Parameters", []() {
        Math::Matrix3D m(1.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f);
        return m.m00 == 1.0f && m.m01 == 2.0f && m.m02 == 3.0f &&
               m.m10 == 4.0f && m.m11 == 5.0f && m.m12 == 6.0f &&
               m.m20 == 7.0f && m.m21 == 8.0f && m.m22 == 9.0f;
    });

    // Static method tests
    runTest("Matrix3D Identity", []() {
        Math::Matrix3D identity = Math::Matrix3D::Identity();
        return matrix3DEqual(identity, Math::Matrix3D(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        ));
    });

    runTest("Matrix3D Zero", []() {
        Math::Matrix3D zero = Math::Matrix3D::Zero();
        return matrix3DEqual(zero, Math::Matrix3D(
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        ));
    });

    runTest("Matrix3D RotationX (Radians)", []() {
        Math::Matrix3D rot = Math::Matrix3D::RotationXRad(M_PI / 2.0f);
        return matrix3DEqual(rot, Math::Matrix3D(
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f
        ), 1e-5f);
    });

    runTest("Matrix3D RotationX (Degrees)", []() {
        Math::Matrix3D rot = Math::Matrix3D::RotationXDeg(90.0f);
        return matrix3DEqual(rot, Math::Matrix3D(
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f
        ), 1e-5f);
    });

    runTest("Matrix3D RotationY (Radians)", []() {
        Math::Matrix3D rot = Math::Matrix3D::RotationYRad(M_PI / 2.0f);
        return matrix3DEqual(rot, Math::Matrix3D(
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, 0.0f
        ), 1e-5f);
    });

    runTest("Matrix3D RotationY (Degrees)", []() {
        Math::Matrix3D rot = Math::Matrix3D::RotationYDeg(90.0f);
        return matrix3DEqual(rot, Math::Matrix3D(
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, 0.0f
        ), 1e-5f);
    });

    runTest("Matrix3D RotationZ (Radians)", []() {
        Math::Matrix3D rot = Math::Matrix3D::RotationZRad(M_PI / 2.0f);
        return matrix3DEqual(rot, Math::Matrix3D(
            0.0f, -1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        ), 1e-5f);
    });

    runTest("Matrix3D RotationZ (Degrees)", []() {
        Math::Matrix3D rot = Math::Matrix3D::RotationZDeg(90.0f);
        return matrix3DEqual(rot, Math::Matrix3D(
            0.0f, -1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        ), 1e-5f);
    });

    // Operator tests
    runTest("Matrix3D Multiplication", []() {
        Math::Matrix3D m1(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m2(
            9.0f, 8.0f, 7.0f,
            6.0f, 5.0f, 4.0f,
            3.0f, 2.0f, 1.0f
        );
        Math::Matrix3D result = m1 * m2;
        return matrix3DEqual(result, Math::Matrix3D(
            30.0f, 24.0f, 18.0f,
            84.0f, 69.0f, 54.0f,
            138.0f, 114.0f, 90.0f
        ));
    });

    runTest("Matrix3D Multiplication Assignment", []() {
        Math::Matrix3D m1(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m2(
            9.0f, 8.0f, 7.0f,
            6.0f, 5.0f, 4.0f,
            3.0f, 2.0f, 1.0f
        );
        m1 *= m2;
        return matrix3DEqual(m1, Math::Matrix3D(
            30.0f, 24.0f, 18.0f,
            84.0f, 69.0f, 54.0f,
            138.0f, 114.0f, 90.0f
        ));
    });

    runTest("Matrix3D Vector Multiplication", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Vector3D v(2.0f, 3.0f, 4.0f);
        Math::Vector3D result = m * v;
        return vector3DEqual(result, Math::Vector3D(20.0f, 47.0f, 74.0f));
    });

    runTest("Matrix3D Addition", []() {
        Math::Matrix3D m1(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m2(
            9.0f, 8.0f, 7.0f,
            6.0f, 5.0f, 4.0f,
            3.0f, 2.0f, 1.0f
        );
        Math::Matrix3D result = m1 + m2;
        return matrix3DEqual(result, Math::Matrix3D(
            10.0f, 10.0f, 10.0f,
            10.0f, 10.0f, 10.0f,
            10.0f, 10.0f, 10.0f
        ));
    });

    runTest("Matrix3D Addition Assignment", []() {
        Math::Matrix3D m1(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m2(
            9.0f, 8.0f, 7.0f,
            6.0f, 5.0f, 4.0f,
            3.0f, 2.0f, 1.0f
        );
        m1 += m2;
        return matrix3DEqual(m1, Math::Matrix3D(
            10.0f, 10.0f, 10.0f,
            10.0f, 10.0f, 10.0f,
            10.0f, 10.0f, 10.0f
        ));
    });

    runTest("Matrix3D Subtraction", []() {
        Math::Matrix3D m1(
            10.0f, 10.0f, 10.0f,
            10.0f, 10.0f, 10.0f,
            10.0f, 10.0f, 10.0f
        );
        Math::Matrix3D m2(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D result = m1 - m2;
        return matrix3DEqual(result, Math::Matrix3D(
            9.0f, 8.0f, 7.0f,
            6.0f, 5.0f, 4.0f,
            3.0f, 2.0f, 1.0f
        ));
    });

    runTest("Matrix3D Subtraction Assignment", []() {
    Math::Matrix3D m1(
        10.0f, 10.0f, 10.0f,
        10.0f, 10.0f, 10.0f,
        10.0f, 10.0f, 10.0f
    );
    Math::Matrix3D m2(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    );
    m1 -= m2;
    return matrix3DEqual(m1, Math::Matrix3D(
        9.0f, 8.0f, 7.0f,
        6.0f, 5.0f, 4.0f,
        3.0f, 2.0f, 1.0f
    ));
});


    runTest("Matrix3D Scalar Multiplication", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D result = m * 2.0f;
        return matrix3DEqual(result, Math::Matrix3D(
            2.0f, 4.0f, 6.0f,
            8.0f, 10.0f, 12.0f,
            14.0f, 16.0f, 18.0f
        ));
    });

    runTest("Matrix3D Scalar Multiplication Assignment", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        m *= 2.0f;
        return matrix3DEqual(m, Math::Matrix3D(
            2.0f, 4.0f, 6.0f,
            8.0f, 10.0f, 12.0f,
            14.0f, 16.0f, 18.0f
        ));
    });

    runTest("Matrix3D Scalar Division", []() {
        Math::Matrix3D m(
            2.0f, 4.0f, 6.0f,
            8.0f, 10.0f, 12.0f,
            14.0f, 16.0f, 18.0f
        );
        Math::Matrix3D result = m / 2.0f;
        return matrix3DEqual(result, Math::Matrix3D(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        ));
    });

    runTest("Matrix3D Scalar Division Assignment", []() {
        Math::Matrix3D m(
            2.0f, 4.0f, 6.0f,
            8.0f, 10.0f, 12.0f,
            14.0f, 16.0f, 18.0f
        );
        m /= 2.0f;
        return matrix3DEqual(m, Math::Matrix3D(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        ));
    });

    // Method tests
    runTest("Matrix3D Determinant", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        float det = m.Determinant();
        return floatEqual(det, 0.0f); // This matrix is singular
    });

    runTest("Matrix3D Determinant Non-Singular", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            0.0f, 1.0f, 4.0f,
            5.0f, 6.0f, 0.0f
        );
        float det = m.Determinant();
        return floatEqual(det, 1.0f);
    });

    runTest("Matrix3D Transpose", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D transposed = m.Transpose();
        return matrix3DEqual(transposed, Math::Matrix3D(
            1.0f, 4.0f, 7.0f,
            2.0f, 5.0f, 8.0f,
            3.0f, 6.0f, 9.0f
        ));
    });

    runTest("Matrix3D Inverse", []() {
        // Using a matrix with a known inverse
        Math::Matrix3D m(
            1.0f, 0.0f, 1.0f,
            0.0f, 2.0f, 0.0f,
            2.0f, 0.0f, 3.0f
        );
        Math::Matrix3D inverse = m.Inverse();
        Math::Matrix3D identity = m * inverse;
        return matrix3DEqual(identity, Math::Matrix3D::Identity(), 1e-5f);
    });

    runTest("Matrix3D IsInvertible", []() {
        Math::Matrix3D invertible(
            1.0f, 0.0f, 1.0f,
            0.0f, 2.0f, 0.0f,
            2.0f, 0.0f, 3.0f
        );
        Math::Matrix3D nonInvertible(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        return invertible.IsInvertible() && !nonInvertible.IsInvertible();
    });

    runTest("Matrix3D IsZero", []() {
        Math::Matrix3D zero = Math::Matrix3D::Zero();
        Math::Matrix3D nonZero(
            0.0f, 0.0f, 0.0f,
            0.0f, 0.1f, 0.0f,
            0.0f, 0.0f, 0.0f
        );
        return zero.IsZero() && !nonZero.IsZero();
    });

    runTest("Matrix3D IsIdentity", []() {
        Math::Matrix3D identity = Math::Matrix3D::Identity();
        Math::Matrix3D nonIdentity(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.1f, 0.0f,
            0.0f, 0.0f, 1.0f
        );
        return identity.IsIdentity() && !nonIdentity.IsIdentity();
    });

    runTest("Matrix3D GetScaled", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D scaled = m.GetScaled(2.0f, 3.0f, 4.0f);
        return matrix3DEqual(scaled, Math::Matrix3D(
            2.0f, 6.0f, 12.0f,
            8.0f, 15.0f, 24.0f,
            14.0f, 24.0f, 36.0f
        ));
    });

    runTest("Matrix3D GetScaledUniform", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D scaled = m.GetScaled(2.0f);
        return matrix3DEqual(scaled, Math::Matrix3D(
            2.0f, 4.0f, 6.0f,
            8.0f, 10.0f, 12.0f,
            14.0f, 16.0f, 18.0f
        ));
    });

    runTest("Matrix3D ScaleInPlace", []() {
        Math::Matrix3D m(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        m.Scale(2.0f, 3.0f, 4.0f);
        return matrix3DEqual(m, Math::Matrix3D(
            2.0f, 6.0f, 12.0f,
            8.0f, 15.0f, 24.0f,
            14.0f, 24.0f, 36.0f
        ));
    });

    runTest("Matrix3D GetRotatedX", []() {
        Math::Matrix3D m = Math::Matrix3D::Identity();
        Math::Matrix3D rotated = m.GetRotatedXRad(M_PI / 2.0f);
        return matrix3DEqual(rotated, Math::Matrix3D::RotationXRad(M_PI / 2.0f), 1e-5f);
    });

    runTest("Matrix3D GetRotatedY", []() {
        Math::Matrix3D m = Math::Matrix3D::Identity();
        Math::Matrix3D rotated = m.GetRotatedYRad(M_PI / 2.0f);
        return matrix3DEqual(rotated, Math::Matrix3D::RotationYRad(M_PI / 2.0f), 1e-5f);
    });

    runTest("Matrix3D GetRotatedZ", []() {
        Math::Matrix3D m = Math::Matrix3D::Identity();
        Math::Matrix3D rotated = m.GetRotatedZRad(M_PI / 2.0f);
        return matrix3DEqual(rotated, Math::Matrix3D::RotationZRad(M_PI / 2.0f), 1e-5f);
    });

    runTest("Matrix3D RotateXInPlace", []() {
        Math::Matrix3D m = Math::Matrix3D::Identity();
        m.RotateXRad(M_PI / 2.0f);
        return matrix3DEqual(m, Math::Matrix3D::RotationXRad(M_PI / 2.0f), 1e-5f);
    });

    runTest("Matrix3D RotateYInPlace", []() {
        Math::Matrix3D m = Math::Matrix3D::Identity();
        m.RotateYRad(M_PI / 2.0f);
        return matrix3DEqual(m, Math::Matrix3D::RotationYRad(M_PI / 2.0f), 1e-5f);
    });

    runTest("Matrix3D RotateZInPlace", []() {
        Math::Matrix3D m = Math::Matrix3D::Identity();
        m.RotateZRad(M_PI / 2.0f);
        return matrix3DEqual(m, Math::Matrix3D::RotationZRad(M_PI / 2.0f), 1e-5f);
    });

    runTest("Matrix3D Equality", []() {
        Math::Matrix3D m1(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m2(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m3(
            1.1f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        return (m1 == m2) && !(m1 == m3);
    });

    runTest("Matrix3D Inequality", []() {
        Math::Matrix3D m1(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m2(
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        Math::Matrix3D m3(
            1.1f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        );
        return !(m1 != m2) && (m1 != m3);
    });

    return allPassed;
}