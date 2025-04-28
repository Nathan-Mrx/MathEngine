#include <iostream>
#include <cassert>
#include <cmath>
#include <functional>
#include <string>
#include <iomanip>
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Matrix2D.h"

// Utility functions for testing
const float EPSILON = 1e-5f; // Tolerance for floating-point comparisons

bool floatEqual(float a, float b, float epsilon = EPSILON) {
    return std::fabs(a - b) < epsilon;
}

bool vector2DEqual(const Math::Vector2D& a, const Math::Vector2D& b, float epsilon = EPSILON) {
    return floatEqual(a.x, b.x, epsilon) && floatEqual(a.y, b.y, epsilon);
}

bool vector3DEqual(const Math::Vector3D& a, const Math::Vector3D& b, float epsilon = EPSILON) {
    return floatEqual(a.x, b.x, epsilon) && floatEqual(a.y, b.y, epsilon) && floatEqual(a.z, b.z, epsilon);
}

bool matrix2DEqual(const Math::Matrix2D& a, const Math::Matrix2D& b, float epsilon = EPSILON) {
    return floatEqual(a.m00, b.m00, epsilon) && floatEqual(a.m01, b.m01, epsilon) &&
           floatEqual(a.m10, b.m10, epsilon) && floatEqual(a.m11, b.m11, epsilon);
}

// Test runner to execute and report test results
void runTest(const std::string& testName, std::function<bool()> testFunc) {
    std::cout << "Running test: " << std::left << std::setw(50) << testName << " - ";
    bool result = testFunc();
    std::cout << (result ? "PASSED" : "FAILED") << std::endl;
    if (!result) {
        std::cerr << "    Test failure in '" << testName << "'" << std::endl;
    }
}

// Vector2D tests
void testVector2D() {
    std::cout << "\n=== Vector2D Tests ===\n";

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
}

// Vector3D tests
void testVector3D() {
    std::cout << "\n=== Vector3D Tests ===\n";

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
}

// Matrix2D tests
void testMatrix2D() {
    std::cout << "\n=== Matrix2D Tests ===\n";

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
}

int main() {
    std::cout << "=== Math Library Unit Tests ===\n";
    
    testVector2D();
    testVector3D();
    testMatrix2D();
    
    std::cout << "\nAll tests completed.\n";
    return 0;
}
