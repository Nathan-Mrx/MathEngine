//
// Created by natha on 2025-04-28.
//

#include <iostream>

#include "Matrix4DTests.h"
#include "TestUtils.h"
#include "../Math/Matrix4D.h"
#include "../Math/Vector3D.h"
#include "../Math/Constants.h"

// Matrix4D tests
bool RunMatrix4DTests() {
    std::cout << "\n=== Matrix4D Tests ===\n";
    bool allPassed = true;

    // Constructor tests
    runTest("Matrix4D Default Constructor", []() {
        Math::Matrix4D m;
        return m.m00 == 1.0f && m.m11 == 1.0f && m.m22 == 1.0f && m.m33 == 1.0f &&
               m.m01 == 0.0f && m.m02 == 0.0f && m.m03 == 0.0f &&
               m.m10 == 0.0f && m.m12 == 0.0f && m.m13 == 0.0f &&
               m.m20 == 0.0f && m.m21 == 0.0f && m.m23 == 0.0f &&
               m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f;
    });

    runTest("Matrix4D Constructor with Parameters", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );
        return m.m00 == 1.0f && m.m01 == 2.0f && m.m02 == 3.0f && m.m03 == 4.0f &&
               m.m10 == 5.0f && m.m11 == 6.0f && m.m12 == 7.0f && m.m13 == 8.0f &&
               m.m20 == 9.0f && m.m21 == 10.0f && m.m22 == 11.0f && m.m23 == 12.0f &&
               m.m30 == 13.0f && m.m31 == 14.0f && m.m32 == 15.0f && m.m33 == 16.0f;
    });

    runTest("Matrix4D Constructor with Vectors", []() {
        Math::Vector3D col0(1.0f, 2.0f, 3.0f);
        Math::Vector3D col1(4.0f, 5.0f, 6.0f);
        Math::Vector3D col2(7.0f, 8.0f, 9.0f);
        Math::Vector3D col3(10.0f, 11.0f, 12.0f);
        Math::Matrix4D m(col0, col1, col2, col3);

        return m.m00 == 1.0f && m.m01 == 4.0f && m.m02 == 7.0f && m.m03 == 10.0f &&
               m.m10 == 2.0f && m.m11 == 5.0f && m.m12 == 8.0f && m.m13 == 11.0f &&
               m.m20 == 3.0f && m.m21 == 6.0f && m.m22 == 9.0f && m.m23 == 12.0f &&
               m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f && m.m33 == 1.0f;
    });

    runTest("Matrix4D Constructor with Array", []() {
        std::array<float, 16> elements = {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        Math::Matrix4D m(elements);

        return m.m00 == 1.0f && m.m01 == 2.0f && m.m02 == 3.0f && m.m03 == 4.0f &&
               m.m10 == 5.0f && m.m11 == 6.0f && m.m12 == 7.0f && m.m13 == 8.0f &&
               m.m20 == 9.0f && m.m21 == 10.0f && m.m22 == 11.0f && m.m23 == 12.0f &&
               m.m30 == 13.0f && m.m31 == 14.0f && m.m32 == 15.0f && m.m33 == 16.0f;
    });

    // Element access tests
    runTest("Matrix4D GetElement", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        return m.GetElement(0, 0) == 1.0f && m.GetElement(0, 3) == 4.0f &&
               m.GetElement(2, 1) == 10.0f && m.GetElement(3, 3) == 16.0f;
    });

    runTest("Matrix4D SetElement", []() {
        Math::Matrix4D m;
        m.SetElement(1, 2, 42.0f);
        m.SetElement(3, 0, 24.0f);

        return m.m12 == 42.0f && m.m30 == 24.0f;
    });

    runTest("Matrix4D GetRow", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        std::array<float, 4> row0 = m.GetRow(0);
        std::array<float, 4> row2 = m.GetRow(2);

        return row0[0] == 1.0f && row0[1] == 2.0f && row0[2] == 3.0f && row0[3] == 4.0f &&
               row2[0] == 9.0f && row2[1] == 10.0f && row2[2] == 11.0f && row2[3] == 12.0f;
    });

    runTest("Matrix4D SetRow", []() {
        Math::Matrix4D m;
        m.SetRow(1, {5.0f, 6.0f, 7.0f, 8.0f});

        return m.m10 == 5.0f && m.m11 == 6.0f && m.m12 == 7.0f && m.m13 == 8.0f;
    });

    runTest("Matrix4D GetColumn", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        std::array<float, 4> col1 = m.GetColumn(1);
        std::array<float, 4> col3 = m.GetColumn(3);

        return col1[0] == 2.0f && col1[1] == 6.0f && col1[2] == 10.0f && col1[3] == 14.0f &&
               col3[0] == 4.0f && col3[1] == 8.0f && col3[2] == 12.0f && col3[3] == 16.0f;
    });

    runTest("Matrix4D SetColumn", []() {
        Math::Matrix4D m;
        m.SetColumn(2, {7.0f, 8.0f, 9.0f, 10.0f});

        return m.m02 == 7.0f && m.m12 == 8.0f && m.m22 == 9.0f && m.m32 == 10.0f;
    });

    runTest("Matrix4D ToArray", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        std::array<float, 16> arr = m.ToArray();

        return arr[0] == 1.0f && arr[1] == 2.0f && arr[2] == 3.0f && arr[3] == 4.0f &&
               arr[4] == 5.0f && arr[5] == 6.0f && arr[6] == 7.0f && arr[7] == 8.0f &&
               arr[8] == 9.0f && arr[9] == 10.0f && arr[10] == 11.0f && arr[11] == 12.0f &&
               arr[12] == 13.0f && arr[13] == 14.0f && arr[14] == 15.0f && arr[15] == 16.0f;
    });

    // Basic operation tests
    runTest("Matrix4D Multiplication", []() {
        Math::Matrix4D m1(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m2(
            17.0f, 18.0f, 19.0f, 20.0f,
            21.0f, 22.0f, 23.0f, 24.0f,
            25.0f, 26.0f, 27.0f, 28.0f,
            29.0f, 30.0f, 31.0f, 32.0f
        );

        Math::Matrix4D result = m1 * m2;

        return result.m00 == 250.0f && result.m01 == 260.0f && result.m02 == 270.0f && result.m03 == 280.0f &&
               result.m10 == 618.0f && result.m11 == 644.0f && result.m12 == 670.0f && result.m13 == 696.0f &&
               result.m20 == 986.0f && result.m21 == 1028.0f && result.m22 == 1070.0f && result.m23 == 1112.0f &&
               result.m30 == 1354.0f && result.m31 == 1412.0f && result.m32 == 1470.0f && result.m33 == 1528.0f;
    });

    runTest("Matrix4D Multiplication Assignment", []() {
        Math::Matrix4D m1(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m2(
            17.0f, 18.0f, 19.0f, 20.0f,
            21.0f, 22.0f, 23.0f, 24.0f,
            25.0f, 26.0f, 27.0f, 28.0f,
            29.0f, 30.0f, 31.0f, 32.0f
        );

        m1 *= m2;

        return m1.m00 == 250.0f && m1.m01 == 260.0f && m1.m02 == 270.0f && m1.m03 == 280.0f &&
               m1.m10 == 618.0f && m1.m11 == 644.0f && m1.m12 == 670.0f && m1.m13 == 696.0f &&
               m1.m20 == 986.0f && m1.m21 == 1028.0f && m1.m22 == 1070.0f && m1.m23 == 1112.0f &&
               m1.m30 == 1354.0f && m1.m31 == 1412.0f && m1.m32 == 1470.0f && m1.m33 == 1528.0f;
    });

    runTest("Matrix4D Vector Transformation (Point)", []() {
        Math::Matrix4D m(
            1.0f, 0.0f, 0.0f, 10.0f,
            0.0f, 1.0f, 0.0f, 20.0f,
            0.0f, 0.0f, 1.0f, 30.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );

        Math::Vector3D v(5.0f, 6.0f, 7.0f);
        Math::Vector3D result = m.TransformPoint(v);

        return vector3DEqual(result, Math::Vector3D(15.0f, 26.0f, 37.0f));
    });

    runTest("Matrix4D Vector Transformation (Vector)", []() {
        Math::Matrix4D m(
            2.0f, 0.0f, 0.0f, 10.0f,
            0.0f, 3.0f, 0.0f, 20.0f,
            0.0f, 0.0f, 4.0f, 30.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );

        Math::Vector3D v(5.0f, 6.0f, 7.0f);
        Math::Vector3D result = m.TransformVector(v);

        return vector3DEqual(result, Math::Vector3D(10.0f, 18.0f, 28.0f));
    });

    runTest("Matrix4D Addition", []() {
        Math::Matrix4D m1(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m2(
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        );

        Math::Matrix4D result = m1 + m2;

        return result.m00 == 2.0f && result.m01 == 3.0f && result.m02 == 4.0f && result.m03 == 5.0f &&
               result.m10 == 6.0f && result.m11 == 7.0f && result.m12 == 8.0f && result.m13 == 9.0f &&
               result.m20 == 10.0f && result.m21 == 11.0f && result.m22 == 12.0f && result.m23 == 13.0f &&
               result.m30 == 14.0f && result.m31 == 15.0f && result.m32 == 16.0f && result.m33 == 17.0f;
    });

    runTest("Matrix4D Addition Assignment", []() {
        Math::Matrix4D m1(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m2(
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        );

        m1 += m2;

        return m1.m00 == 2.0f && m1.m01 == 3.0f && m1.m02 == 4.0f && m1.m03 == 5.0f &&
               m1.m10 == 6.0f && m1.m11 == 7.0f && m1.m12 == 8.0f && m1.m13 == 9.0f &&
               m1.m20 == 10.0f && m1.m21 == 11.0f && m1.m22 == 12.0f && m1.m23 == 13.0f &&
               m1.m30 == 14.0f && m1.m31 == 15.0f && m1.m32 == 16.0f && m1.m33 == 17.0f;
    });

    runTest("Matrix4D Subtraction", []() {
        Math::Matrix4D m1(
            2.0f, 3.0f, 4.0f, 5.0f,
            6.0f, 7.0f, 8.0f, 9.0f,
            10.0f, 11.0f, 12.0f, 13.0f,
            14.0f, 15.0f, 16.0f, 17.0f
        );

        Math::Matrix4D m2(
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        );

        Math::Matrix4D result = m1 - m2;

        return result.m00 == 1.0f && result.m01 == 2.0f && result.m02 == 3.0f && result.m03 == 4.0f &&
               result.m10 == 5.0f && result.m11 == 6.0f && result.m12 == 7.0f && result.m13 == 8.0f &&
               result.m20 == 9.0f && result.m21 == 10.0f && result.m22 == 11.0f && result.m23 == 12.0f &&
               result.m30 == 13.0f && result.m31 == 14.0f && result.m32 == 15.0f && result.m33 == 16.0f;
    });

    runTest("Matrix4D Subtraction Assignment", []() {
        Math::Matrix4D m1(
            2.0f, 3.0f, 4.0f, 5.0f,
            6.0f, 7.0f, 8.0f, 9.0f,
            10.0f, 11.0f, 12.0f, 13.0f,
            14.0f, 15.0f, 16.0f, 17.0f
        );

        Math::Matrix4D m2(
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        );

        m1 -= m2;

        return m1.m00 == 1.0f && m1.m01 == 2.0f && m1.m02 == 3.0f && m1.m03 == 4.0f &&
               m1.m10 == 5.0f && m1.m11 == 6.0f && m1.m12 == 7.0f && m1.m13 == 8.0f &&
               m1.m20 == 9.0f && m1.m21 == 10.0f && m1.m22 == 11.0f && m1.m23 == 12.0f &&
               m1.m30 == 13.0f && m1.m31 == 14.0f && m1.m32 == 15.0f && m1.m33 == 16.0f;
    });

    runTest("Matrix4D Negation", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D result = -m;

        return result.m00 == -1.0f && result.m01 == -2.0f && result.m02 == -3.0f && result.m03 == -4.0f &&
               result.m10 == -5.0f && result.m11 == -6.0f && result.m12 == -7.0f && result.m13 == -8.0f &&
               result.m20 == -9.0f && result.m21 == -10.0f && result.m22 == -11.0f && result.m23 == -12.0f &&
               result.m30 == -13.0f && result.m31 == -14.0f && result.m32 == -15.0f && result.m33 == -16.0f;
    });

    runTest("Matrix4D Scalar Multiplication", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D result = m * 2.0f;

        return result.m00 == 2.0f && result.m01 == 4.0f && result.m02 == 6.0f && result.m03 == 8.0f &&
               result.m10 == 10.0f && result.m11 == 12.0f && result.m12 == 14.0f && result.m13 == 16.0f &&
               result.m20 == 18.0f && result.m21 == 20.0f && result.m22 == 22.0f && result.m23 == 24.0f &&
               result.m30 == 26.0f && result.m31 == 28.0f && result.m32 == 30.0f && result.m33 == 32.0f;
    });

    runTest("Matrix4D Scalar Multiplication Assignment", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        m *= 2.0f;

        return m.m00 == 2.0f && m.m01 == 4.0f && m.m02 == 6.0f && m.m03 == 8.0f &&
               m.m10 == 10.0f && m.m11 == 12.0f && m.m12 == 14.0f && m.m13 == 16.0f &&
               m.m20 == 18.0f && m.m21 == 20.0f && m.m22 == 22.0f && m.m23 == 24.0f &&
               m.m30 == 26.0f && m.m31 == 28.0f && m.m32 == 30.0f && m.m33 == 32.0f;
    });

    runTest("Matrix4D Scalar Division", []() {
        Math::Matrix4D m(
            2.0f, 4.0f, 6.0f, 8.0f,
            10.0f, 12.0f, 14.0f, 16.0f,
            18.0f, 20.0f, 22.0f, 24.0f,
            26.0f, 28.0f, 30.0f, 32.0f
        );

        Math::Matrix4D result = m / 2.0f;

        return result.m00 == 1.0f && result.m01 == 2.0f && result.m02 == 3.0f && result.m03 == 4.0f &&
               result.m10 == 5.0f && result.m11 == 6.0f && result.m12 == 7.0f && result.m13 == 8.0f &&
               result.m20 == 9.0f && result.m21 == 10.0f && result.m22 == 11.0f && result.m23 == 12.0f &&
               result.m30 == 13.0f && result.m31 == 14.0f && result.m32 == 15.0f && result.m33 == 16.0f;
    });

    runTest("Matrix4D Scalar Division Assignment", []() {
        Math::Matrix4D m(
            2.0f, 4.0f, 6.0f, 8.0f,
            10.0f, 12.0f, 14.0f, 16.0f,
            18.0f, 20.0f, 22.0f, 24.0f,
            26.0f, 28.0f, 30.0f, 32.0f
        );

        m /= 2.0f;

        return m.m00 == 1.0f && m.m01 == 2.0f && m.m02 == 3.0f && m.m03 == 4.0f &&
               m.m10 == 5.0f && m.m11 == 6.0f && m.m12 == 7.0f && m.m13 == 8.0f &&
               m.m20 == 9.0f && m.m21 == 10.0f && m.m22 == 11.0f && m.m23 == 12.0f &&
               m.m30 == 13.0f && m.m31 == 14.0f && m.m32 == 15.0f && m.m33 == 16.0f;
    });

    // Property tests
    runTest("Matrix4D Equals", []() {
        Math::Matrix4D m1(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m2(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m3(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.5f, 12.0f,  // Different value
            13.0f, 14.0f, 15.0f, 16.0f
        );

        return m1.Equals(m2) && !m1.Equals(m3);
    });

    runTest("Matrix4D Operator == and !=", []() {
        Math::Matrix4D m1(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m2(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D m3(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.5f, 12.0f,  // Different value
            13.0f, 14.0f, 15.0f, 16.0f
        );

        return (m1 == m2) && !(m1 == m3) && (m1 != m3) && !(m1 != m2);
    });

    // Static creation methods
    runTest("Matrix4D Identity", []() {
        Math::Matrix4D identity = Math::Matrix4D::Identity();

        return identity.m00 == 1.0f && identity.m11 == 1.0f && identity.m22 == 1.0f && identity.m33 == 1.0f &&
               identity.m01 == 0.0f && identity.m02 == 0.0f && identity.m03 == 0.0f &&
               identity.m10 == 0.0f && identity.m12 == 0.0f && identity.m13 == 0.0f &&
               identity.m20 == 0.0f && identity.m21 == 0.0f && identity.m23 == 0.0f &&
               identity.m30 == 0.0f && identity.m31 == 0.0f && identity.m32 == 0.0f;
    });

    runTest("Matrix4D Zero", []() {
        Math::Matrix4D zero = Math::Matrix4D::Zero();

        return zero.m00 == 0.0f && zero.m01 == 0.0f && zero.m02 == 0.0f && zero.m03 == 0.0f &&
               zero.m10 == 0.0f && zero.m11 == 0.0f && zero.m12 == 0.0f && zero.m13 == 0.0f &&
               zero.m20 == 0.0f && zero.m21 == 0.0f && zero.m22 == 0.0f && zero.m23 == 0.0f &&
               zero.m30 == 0.0f && zero.m31 == 0.0f && zero.m32 == 0.0f && zero.m33 == 0.0f;
    });

    // Matrix transformation methods
    runTest("Matrix4D Translation", []() {
        Math::Vector3D translation(2.0f, 3.0f, 4.0f);
        Math::Matrix4D m = Math::Matrix4D::CreateTranslation(translation);

        return m.m00 == 1.0f && m.m11 == 1.0f && m.m22 == 1.0f && m.m33 == 1.0f &&
               m.m03 == 2.0f && m.m13 == 3.0f && m.m23 == 4.0f &&
               m.m01 == 0.0f && m.m02 == 0.0f && m.m10 == 0.0f && m.m12 == 0.0f &&
               m.m20 == 0.0f && m.m21 == 0.0f && m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f;
    });

    runTest("Matrix4D Scale", []() {
        Math::Vector3D scale(2.0f, 3.0f, 4.0f);
        Math::Matrix4D m = Math::Matrix4D::CreateScale(scale);

        return m.m00 == 2.0f && m.m11 == 3.0f && m.m22 == 4.0f && m.m33 == 1.0f &&
               m.m01 == 0.0f && m.m02 == 0.0f && m.m03 == 0.0f &&
               m.m10 == 0.0f && m.m12 == 0.0f && m.m13 == 0.0f &&
               m.m20 == 0.0f && m.m21 == 0.0f && m.m23 == 0.0f &&
               m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f;
    });

    runTest("Matrix4D RotationX", []() {
        float angle = Math::Constants::PI / 2.0f;  // 90 degrees
        Math::Matrix4D m = Math::Matrix4D::CreateRotationX(angle);

        return std::abs(m.m00 - 1.0f) < Math::Constants::EPSILON &&
               std::abs(m.m11 - 0.0f) < Math::Constants::EPSILON &&
               std::abs(m.m12 - 1.0f) < Math::Constants::EPSILON &&
               std::abs(m.m21 - (-1.0f)) < Math::Constants::EPSILON &&
               std::abs(m.m22 - 0.0f) < Math::Constants::EPSILON &&
               std::abs(m.m33 - 1.0f) < Math::Constants::EPSILON;
    });

    runTest("Matrix4D RotationY", []() {
        float angle = Math::Constants::PI / 2.0f;  // 90 degrees
        Math::Matrix4D m = Math::Matrix4D::CreateRotationY(angle);

        return std::abs(m.m00 - 0.0f) < Math::Constants::EPSILON &&
               std::abs(m.m02 - (-1.0f)) < Math::Constants::EPSILON &&
               std::abs(m.m11 - 1.0f) < Math::Constants::EPSILON &&
               std::abs(m.m20 - 1.0f) < Math::Constants::EPSILON &&
               std::abs(m.m22 - 0.0f) < Math::Constants::EPSILON &&
               std::abs(m.m33 - 1.0f) < Math::Constants::EPSILON;
    });

    runTest("Matrix4D RotationZ", []() {
        float angle = Math::Constants::PI / 2.0f;  // 90 degrees
        Math::Matrix4D m = Math::Matrix4D::CreateRotationZ(angle);

        return std::abs(m.m00 - 0.0f) < Math::Constants::EPSILON &&
               std::abs(m.m01 - 1.0f) < Math::Constants::EPSILON &&
               std::abs(m.m10 - (-1.0f)) < Math::Constants::EPSILON &&
               std::abs(m.m11 - 0.0f) < Math::Constants::EPSILON &&
               std::abs(m.m22 - 1.0f) < Math::Constants::EPSILON &&
               std::abs(m.m33 - 1.0f) < Math::Constants::EPSILON;
    });

    runTest("Matrix4D Rotation (Arbitrary Axis)", []() {
        Math::Vector3D axis(1.0f, 1.0f, 1.0f);
        axis.Normalize();
        float angle = Math::Constants::PI / 4.0f;  // 45 degrees

        Math::Matrix4D m = Math::Matrix4D::CreateRotation(axis, angle);

        // Test by rotating a vector and checking the result
        Math::Vector3D v(1.0f, 0.0f, 0.0f);
        Math::Vector3D rotated = m.TransformVector(v);

        return rotated.Length() > 0.99f && rotated.Length() < 1.01f;  // Length should be preserved
    });

    runTest("Matrix4D LookAt", []() {
        Math::Vector3D eye(0.0f, 0.0f, 5.0f);
        Math::Vector3D target(0.0f, 0.0f, 0.0f);
        Math::Vector3D up(0.0f, 1.0f, 0.0f);

        Math::Matrix4D view = Math::Matrix4D::CreateLookAt(eye, target, up);

        // Transformed eye position should be at (0,0,-5) in view space
        Math::Vector3D transformedEye = view.TransformPoint(eye);

        return std::abs(transformedEye.x) < Math::Constants::EPSILON &&
               std::abs(transformedEye.y) < Math::Constants::EPSILON &&
               std::abs(transformedEye.z) < Math::Constants::EPSILON;
    });

    runTest("Matrix4D Perspective", []() {
        float fov = Math::Constants::PI / 4.0f;  // 45 degrees
        float aspect = 16.0f / 9.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;

        Math::Matrix4D proj = Math::Matrix4D::CreatePerspective(fov, aspect, nearPlane, farPlane);

        // Point at origin should remain at origin
        Math::Vector3D origin(0.0f, 0.0f, 0.0f);
        Math::Vector3D transformed = proj.TransformPoint(origin);

        return proj.m00 > 0 && proj.m11 > 0 && proj.m22 < 0 && proj.m32 < 0 && proj.m23 < 0;
    });

    runTest("Matrix4D Orthographic", []() {
        float left = -5.0f;
        float right = 5.0f;
        float bottom = -5.0f;
        float top = 5.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;

        Math::Matrix4D proj = Math::Matrix4D::CreateOrthographic(left, right, bottom, top, nearPlane, farPlane);

        return std::abs(proj.m00 - 0.2f) < Math::Constants::EPSILON &&
               std::abs(proj.m11 - 0.2f) < Math::Constants::EPSILON &&
               std::abs(proj.m22) > 0.0f &&
               std::abs(proj.m33 - 1.0f) < Math::Constants::EPSILON;
    });

    // Matrix operations
    runTest("Matrix4D Transpose", []() {
        Math::Matrix4D m(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D transposed = m.Transpose();

        return transposed.m00 == 1.0f && transposed.m01 == 5.0f && transposed.m02 == 9.0f && transposed.m03 == 13.0f &&
               transposed.m10 == 2.0f && transposed.m11 == 6.0f && transposed.m12 == 10.0f && transposed.m13 == 14.0f &&
               transposed.m20 == 3.0f && transposed.m21 == 7.0f && transposed.m22 == 11.0f && transposed.m23 == 15.0f &&
               transposed.m30 == 4.0f && transposed.m31 == 8.0f && transposed.m32 == 12.0f && transposed.m33 == 16.0f;
    });

    runTest("Matrix4D Determinant", []() {
        Math::Matrix4D identity = Math::Matrix4D::Identity();

        Math::Matrix4D scaleMatrix = Math::Matrix4D::CreateScale(Math::Vector3D(2.0f, 3.0f, 4.0f));

        Math::Matrix4D singular(
            1.0f, 2.0f, 3.0f, 4.0f,
            2.0f, 4.0f, 6.0f, 8.0f,  // Row 2 = 2 * Row 1
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        return std::abs(identity.Determinant() - 1.0f) < Math::Constants::EPSILON &&
               std::abs(scaleMatrix.Determinant() - 24.0f) < Math::Constants::EPSILON &&
               std::abs(singular.Determinant()) < Math::Constants::EPSILON;
    });

    runTest("Matrix4D Inverse", []() {
        Math::Matrix4D m(
            4.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 5.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 6.0f, 0.0f,
            1.0f, 2.0f, 3.0f, 1.0f
        );

        Math::Matrix4D inverse = m.Inverse();

        // Check that m * inverse = identity
        Math::Matrix4D product = m * inverse;

        return matrix4DEqual(product, Math::Matrix4D::Identity());
    });

    runTest("Matrix4D TryInverse", []() {
        Math::Matrix4D invertible(
            4.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 5.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 6.0f, 0.0f,
            1.0f, 2.0f, 3.0f, 1.0f
        );

        Math::Matrix4D singular(
            1.0f, 2.0f, 3.0f, 4.0f,
            2.0f, 4.0f, 6.0f, 8.0f,  // Row 2 = 2 * Row 1
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        Math::Matrix4D result1, result2;
        bool success1 = invertible.TryInverse(result1);
        bool success2 = singular.TryInverse(result2);

        return success1 && !success2 && matrix4DEqual(invertible * result1, Math::Matrix4D::Identity());
    });

    // Output success/failure summary
    std::cout << (allPassed ? "All tests passed!" : "Some tests failed!") << std::endl;
    return allPassed;
}