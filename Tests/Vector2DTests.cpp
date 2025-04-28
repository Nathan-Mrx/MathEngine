//
// Created by natha on 2025-04-28.
//

#include "Vector2DTests.h"
#include "TestUtils.h"
#include "../Math/Vector2D.h"
#include <iostream>




// Vector2D tests
bool RunVector2DTests() {
    std::cout << "\n=== Vector2D Tests ===\n";
    bool allPassed = true;

    // Constructor tests
    runTest("Vector2D Default Constructor", []() {
        Math::Vector2D v;
        // The default constructor doesn't initialize values, so we can't check specific values
        return true; // Just verify it compiles and runs
    });

    runTest("Vector2D Constructor with Parameters", []() {
        Math::Vector2D v(3.0f, 4.0f);
        return v.x == 3.0f && v.y == 4.0f;
    });

    // Operator tests
    runTest("Vector2D Addition", []() {
        Math::Vector2D v1(1.0f, 2.0f);
        Math::Vector2D v2(3.0f, 4.0f);
        Math::Vector2D result = v1 + v2;
        return vector2DEqual(result, Math::Vector2D(4.0f, 6.0f));
    });

    runTest("Vector2D Addition Assignment", []() {
        Math::Vector2D v1(1.0f, 2.0f);
        Math::Vector2D v2(3.0f, 4.0f);
        v1 += v2;
        return vector2DEqual(v1, Math::Vector2D(4.0f, 6.0f));
    });

    runTest("Vector2D Subtraction", []() {
        Math::Vector2D v1(5.0f, 7.0f);
        Math::Vector2D v2(2.0f, 3.0f);
        Math::Vector2D result = v1 - v2;
        return vector2DEqual(result, Math::Vector2D(3.0f, 4.0f));
    });

    runTest("Vector2D Subtraction Assignment", []() {
        Math::Vector2D v1(5.0f, 7.0f);
        Math::Vector2D v2(2.0f, 3.0f);
        v1 -= v2;
        return vector2DEqual(v1, Math::Vector2D(3.0f, 4.0f));
    });

    runTest("Vector2D Scalar Multiplication", []() {
        Math::Vector2D v(2.0f, 3.0f);
        Math::Vector2D result = v * 2.0f;
        return vector2DEqual(result, Math::Vector2D(4.0f, 6.0f));
    });

    runTest("Vector2D Scalar Multiplication Assignment", []() {
        Math::Vector2D v(2.0f, 3.0f);
        v *= 2.0f;
        return vector2DEqual(v, Math::Vector2D(4.0f, 6.0f));
    });

    runTest("Vector2D Scalar Division", []() {
        Math::Vector2D v(4.0f, 6.0f);
        Math::Vector2D result = v / 2.0f;
        return vector2DEqual(result, Math::Vector2D(2.0f, 3.0f));
    });

    runTest("Vector2D Scalar Division Assignment", []() {
        Math::Vector2D v(4.0f, 6.0f);
        v /= 2.0f;
        return vector2DEqual(v, Math::Vector2D(2.0f, 3.0f));
    });

    // Method tests
    runTest("Vector2D Dot Product", []() {
        Math::Vector2D v1(1.0f, 2.0f);
        Math::Vector2D v2(3.0f, 4.0f);
        float dot = v1.Dot(v2);
        return floatEqual(dot, 11.0f);
    });

    runTest("Vector2D Length", []() {
        Math::Vector2D v(3.0f, 4.0f);
        float length = v.Length();
        return floatEqual(length, 5.0f);
    });

    runTest("Vector2D Normalize", []() {
        Math::Vector2D v(3.0f, 4.0f);
        Math::Vector2D normalized = v.Normalize();
        return vector2DEqual(normalized, Math::Vector2D(0.6f, 0.8f));
    });

    runTest("Vector2D Normalize Zero Vector", []() {
        Math::Vector2D v(0.0f, 0.0f);
        Math::Vector2D normalized = v.Normalize();
        return vector2DEqual(normalized, Math::Vector2D(0.0f, 0.0f));
    });

    runTest("Vector2D Distance", []() {
        Math::Vector2D v1(1.0f, 1.0f);
        Math::Vector2D v2(4.0f, 5.0f);
        float distance = v1.Distance(v2);
        return floatEqual(distance, 5.0f);
    });

    runTest("Vector2D Cross Product", []() {
        Math::Vector2D v1(1.0f, 2.0f);
        Math::Vector2D v2(3.0f, 4.0f);
        float cross = v1.Cross(v2);
        return floatEqual(cross, -2.0f);
    });

    runTest("Vector2D Angle (Radians)", []() {
        Math::Vector2D v1(1.0f, 0.0f);
        Math::Vector2D v2(0.0f, 1.0f);
        float angle = v1.AngleRad(v2);
        return floatEqual(angle, M_PI / 2.0f);
    });

    runTest("Vector2D Angle (Degrees)", []() {
        Math::Vector2D v1(1.0f, 0.0f);
        Math::Vector2D v2(0.0f, 1.0f);
        float angle = v1.AngleDeg(v2);
        return floatEqual(angle, 90.0f);
    });

    return allPassed;
}