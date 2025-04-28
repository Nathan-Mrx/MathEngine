
//
// Created on 2025-04-27.
//

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <string>
#include <functional>
#include "../Math/Constants.h"
#include "../Math/Vector2D.h"
#include "../Math/Vector3D.h"
#include "../Math/Matrix2D.h"
#include "../Math/Matrix3D.h"


// Utility functions for tests
bool floatEqual(float a, float b, float epsilon = Math::Constants::EPSILON);
bool vector2DEqual(const Math::Vector2D& a, const Math::Vector2D& b, float epsilon = Math::Constants::EPSILON);
bool vector3DEqual(const Math::Vector3D& a, const Math::Vector3D& b, float epsilon = Math::Constants::EPSILON);
bool matrix2DEqual(const Math::Matrix2D& a, const Math::Matrix2D& b, float epsilon = Math::Constants::EPSILON);
bool matrix3DEqual(const Math::Matrix3D& a, const Math::Matrix3D& b, float epsilon = Math::Constants::EPSILON);
void runTest(const std::string& testName, std::function<bool()> testFunc);

#endif // TEST_UTILS_H