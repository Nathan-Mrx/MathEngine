//
// Created by natha on 2025-04-28.
//

#include "Vector3DTests.h"
#include "TestUtils.h"
#include "../Math/Vector3D.h"
#include <iostream>

// Vector3D tests
bool RunVector3DTests() {
    std::cout << "\n=== Vector3D Tests ===\n";
    bool allPassed = true;

    // Constructor tests
    runTest("Vector3D Default Constructor", []() {
        Math::Vector3D v;
        // The default constructor doesn't initialize values, so we can't check specific values
        return true; // Just verify it compiles and runs
    });

    runTest("Vector3D Constructor with Parameters", []() {
        Math::Vector3D v(1.0f, 2.0f, 3.0f);
        return v.x == 1.0f && v.y == 2.0f && v.z == 3.0f;
    });

    // Operator tests
    runTest("Vector3D Addition", []() {
        Math::Vector3D v1(1.0f, 2.0f, 3.0f);
        Math::Vector3D v2(4.0f, 5.0f, 6.0f);
        Math::Vector3D result = v1 + v2;
        return vector3DEqual(result, Math::Vector3D(5.0f, 7.0f, 9.0f));
    });

    runTest("Vector3D Addition Assignment", []() {
        Math::Vector3D v1(1.0f, 2.0f, 3.0f);
        Math::Vector3D v2(4.0f, 5.0f, 6.0f);
        v1 += v2;
        return vector3DEqual(v1, Math::Vector3D(5.0f, 7.0f, 9.0f));
    });

    runTest("Vector3D Subtraction", []() {
        Math::Vector3D v1(5.0f, 7.0f, 9.0f);
        Math::Vector3D v2(1.0f, 2.0f, 3.0f);
        Math::Vector3D result = v1 - v2;
        return vector3DEqual(result, Math::Vector3D(4.0f, 5.0f, 6.0f));
    });

    runTest("Vector3D Subtraction Assignment", []() {
        Math::Vector3D v1(5.0f, 7.0f, 9.0f);
        Math::Vector3D v2(1.0f, 2.0f, 3.0f);
        v1 -= v2;
        return vector3DEqual(v1, Math::Vector3D(4.0f, 5.0f, 6.0f));
    });

    runTest("Vector3D Scalar Multiplication", []() {
        Math::Vector3D v(2.0f, 3.0f, 4.0f);
        Math::Vector3D result = v * 2.0f;
        return vector3DEqual(result, Math::Vector3D(4.0f, 6.0f, 8.0f));
    });

    runTest("Vector3D Scalar Multiplication Assignment", []() {
        Math::Vector3D v(2.0f, 3.0f, 4.0f);
        v *= 2.0f;
        return vector3DEqual(v, Math::Vector3D(4.0f, 6.0f, 8.0f));
    });

    runTest("Vector3D Scalar Division", []() {
        Math::Vector3D v(4.0f, 6.0f, 8.0f);
        Math::Vector3D result = v / 2.0f;
        return vector3DEqual(result, Math::Vector3D(2.0f, 3.0f, 4.0f));
    });

    runTest("Vector3D Scalar Division Assignment", []() {
        Math::Vector3D v(4.0f, 6.0f, 8.0f);
        v /= 2.0f;
        return vector3DEqual(v, Math::Vector3D(2.0f, 3.0f, 4.0f));
    });

    // Method tests
    runTest("Vector3D Dot Product", []() {
        Math::Vector3D v1(1.0f, 2.0f, 3.0f);
        Math::Vector3D v2(4.0f, 5.0f, 6.0f);
        float dot = v1.Dot(v2);
        return floatEqual(dot, 32.0f);
    });

    runTest("Vector3D Length", []() {
        Math::Vector3D v(3.0f, 4.0f, 0.0f);
        float length = v.Length();
        return floatEqual(length, 5.0f);
    });

    runTest("Vector3D Normalize", []() {
        Math::Vector3D v(3.0f, 0.0f, 4.0f);
        Math::Vector3D normalized = v.Normalize();
        return vector3DEqual(normalized, Math::Vector3D(0.6f, 0.0f, 0.8f));
    });

    runTest("Vector3D Normalize Zero Vector", []() {
        Math::Vector3D v(0.0f, 0.0f, 0.0f);
        Math::Vector3D normalized = v.Normalize();
        return vector3DEqual(normalized, Math::Vector3D(0.0f, 0.0f, 0.0f));
    });

    runTest("Vector3D Cross Product", []() {
        Math::Vector3D v1(1.0f, 0.0f, 0.0f);
        Math::Vector3D v2(0.0f, 1.0f, 0.0f);
        Math::Vector3D cross = v1.Cross(v2);
        return vector3DEqual(cross, Math::Vector3D(0.0f, 0.0f, 1.0f));
    });

    runTest("Vector3D Triple Product", []() {
        Math::Vector3D v1(1.0f, 2.0f, 3.0f);
        Math::Vector3D v2(4.0f, 5.0f, 6.0f);
        Math::Vector3D v3(7.0f, 8.0f, 9.0f);
        float triple = v1.TripleProduct(v2, v3);
        return floatEqual(triple, 0.0f); // Vectors are linearly dependent
    });

    runTest("Vector3D Distance", []() {
        Math::Vector3D v1(1.0f, 1.0f, 1.0f);
        Math::Vector3D v2(4.0f, 5.0f, 1.0f);
        float distance = v1.Distance(v2);
        return floatEqual(distance, 5.0f);
    });

    runTest("Vector3D Angle (Radians)", []() {
        Math::Vector3D v1(1.0f, 0.0f, 0.0f);
        Math::Vector3D v2(0.0f, 1.0f, 0.0f);
        float angle = v1.AngleRad(v2);
        return floatEqual(angle, M_PI / 2.0f);
    });

    runTest("Vector3D Angle (Degrees)", []() {
        Math::Vector3D v1(1.0f, 0.0f, 0.0f);
        Math::Vector3D v2(0.0f, 1.0f, 0.0f);
        float angle = v1.AngleDeg(v2);
        return floatEqual(angle, 90.0f);
    });

    runTest("Vector3D Zero", []() {
        Math::Vector3D zero = Math::Vector3D::Zero();
        return vector3DEqual(zero, Math::Vector3D(0.0f, 0.0f, 0.0f));
    });

    runTest("Vector3D Unit", []() {
        Math::Vector3D unit = Math::Vector3D::Unit();
        return vector3DEqual(unit, Math::Vector3D(1.0f, 1.0f, 1.0f));
    });

    runTest("Vector3D IsZero", []() {
        Math::Vector3D zero(0.0f, 0.0f, 0.0f);
        Math::Vector3D nonZero(0.0f, 0.1f, 0.0f);
        return zero.IsZero() && !nonZero.IsZero();
    });

    return allPassed;
}