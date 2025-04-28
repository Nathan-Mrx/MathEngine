//
// Created by natha on 2025-04-28.
//

#include "TestUtils.h"
#include <iomanip> // For std::setw

bool floatEqual(float a, float b, float epsilon) {
    return std::fabs(a - b) < epsilon;
}

bool vector2DEqual(const Math::Vector2D& a, const Math::Vector2D& b, float epsilon) {
    return floatEqual(a.x, b.x, epsilon) && floatEqual(a.y, b.y, epsilon);
}

bool vector3DEqual(const Math::Vector3D& a, const Math::Vector3D& b, float epsilon) {
    return floatEqual(a.x, b.x, epsilon) && floatEqual(a.y, b.y, epsilon) && floatEqual(a.z, b.z, epsilon);
}

bool matrix2DEqual(const Math::Matrix2D& a, const Math::Matrix2D& b, float epsilon) {
    return floatEqual(a.m00, b.m00, epsilon) && floatEqual(a.m01, b.m01, epsilon) &&
           floatEqual(a.m10, b.m10, epsilon) && floatEqual(a.m11, b.m11, epsilon);
}

// Remove the default parameter from the implementation
bool matrix3DEqual(const Math::Matrix3D& a, const Math::Matrix3D& b, float epsilon) {
    // Implementation remains the same, but without the default parameter
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (std::abs(a.GetElement(i, j) - b.GetElement(i, j)) > epsilon) {
                return false;
            }
        }
    }
    return true;
}

bool matrix4DEqual(const Math::Matrix4D& a, const Math::Matrix4D& b, float epsilon) {
    return a.Equals(b, epsilon);
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