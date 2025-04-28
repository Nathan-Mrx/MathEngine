//
// Created by natha on 2025-04-26.
//

#include "Transform2DTests.h"
#include "../Math/Constants.h"
#include "../Math/Transform2D.h"
#include "TestUtils.h"
#include <iostream>
#include <functional>
#include <cmath>

bool RunTransform2DTests() {
    std::cout << "\n=== Running Transform2D Tests ===\n\n";

    // Test default constructor
    runTest("Transform2D Default Constructor", []() {
        Math::Transform2D transform;

        return transform.GetPosition() == Math::Vector2D(0.0f, 0.0f) &&
               transform.GetRotationRad() == 0.0f &&
               transform.GetScale() == Math::Vector2D(1.0f, 1.0f);
    });

    // Test parameterized constructor
    runTest("Transform2D Parameterized Constructor", []() {
        Math::Vector2D position(2.0f, 3.0f);
        float rotation = 1.0f;  // ~57.3 degrees
        Math::Vector2D scale(2.0f, 3.0f);

        Math::Transform2D transform(position, rotation, scale);

        return transform.GetPosition() == position &&
               std::abs(transform.GetRotationRad() - rotation) < 1e-6f &&
               transform.GetScale() == scale;
    });

    // Test constructor with uniform scale
    runTest("Transform2D Constructor with Uniform Scale", []() {
        Math::Vector2D position(2.0f, 3.0f);
        float rotation = 1.0f;
        float scale = 2.0f;

        Math::Transform2D transform(position, rotation, scale);

        return transform.GetPosition() == position &&
               std::abs(transform.GetRotationRad() - rotation) < 1e-6f &&
               transform.GetScale() == Math::Vector2D(scale, scale);
    });

    // Test identity factory
    runTest("Transform2D Identity Factory", []() {
        Math::Transform2D identity = Math::Transform2D::Identity();

        return identity.GetPosition() == Math::Vector2D(0.0f, 0.0f) &&
               identity.GetRotationRad() == 0.0f &&
               identity.GetScale() == Math::Vector2D(1.0f, 1.0f);
    });

    // Test position getter/setter
    runTest("Transform2D Position Getter/Setter", []() {
        Math::Transform2D transform;
        Math::Vector2D position(3.0f, 4.0f);

        transform.SetPosition(position);
        return transform.GetPosition() == position;
    });

    // Test rotation getter/setter (radians)
    runTest("Transform2D Rotation Getter/Setter (Radians)", []() {
        Math::Transform2D transform;
        float rotation = M_PI / 4.0f;  // 45 degrees

        transform.SetRotationRad(rotation);
        return std::abs(transform.GetRotationRad() - rotation) < 1e-6f;
    });

    // Test rotation getter/setter (degrees)
    runTest("Transform2D Rotation Getter/Setter (Degrees)", []() {
        Math::Transform2D transform;
        float rotationDeg = 45.0f;

        transform.SetRotationDeg(rotationDeg);
        return std::abs(transform.GetRotationDeg() - rotationDeg) < 1e-6f &&
               std::abs(transform.GetRotationRad() - (rotationDeg * M_PI / 180.0f)) < 1e-6f;
    });

    // Test scale getter/setter
    runTest("Transform2D Scale Getter/Setter (Vector)", []() {
        Math::Transform2D transform;
        Math::Vector2D scale(2.0f, 3.0f);

        transform.SetScale(scale);
        return transform.GetScale() == scale;
    });

    // Test scale getter/setter (uniform)
    runTest("Transform2D Scale Getter/Setter (Uniform)", []() {
        Math::Transform2D transform;
        float scale = 2.0f;

        transform.SetScale(scale);
        return transform.GetScale() == Math::Vector2D(scale, scale);
    });

    // Test translate operation
    runTest("Transform2D Translate", []() {
        Math::Transform2D transform;
        Math::Vector2D translation(2.0f, 3.0f);

        transform.Translate(translation);
        return transform.GetPosition() == translation;
    });

    // Test rotate operation (radians)
    runTest("Transform2D Rotate (Radians)", []() {
        Math::Transform2D transform;
        float rotation = M_PI / 4.0f;  // 45 degrees

        transform.RotateRad(rotation);
        return std::abs(transform.GetRotationRad() - rotation) < 1e-6f;
    });

    // Test rotate operation (degrees)
    runTest("Transform2D Rotate (Degrees)", []() {
        Math::Transform2D transform;
        float rotationDeg = 45.0f;

        transform.RotateDeg(rotationDeg);
        return std::abs(transform.GetRotationDeg() - rotationDeg) < 1e-6f;
    });

    // Test scale operation (vector)
    runTest("Transform2D Scale Operation (Vector)", []() {
        Math::Transform2D transform;
        Math::Vector2D scale(2.0f, 3.0f);

        transform.Scale(scale);
        return transform.GetScale() == scale;
    });

    // Test scale operation (uniform)
    runTest("Transform2D Scale Operation (Uniform)", []() {
        Math::Transform2D transform;
        float scale = 2.0f;

        transform.Scale(scale);
        return transform.GetScale() == Math::Vector2D(scale, scale);
    });

    // Test parent/child relationship
    runTest("Transform2D Parent/Child Relationship", []() {
        Math::Transform2D parent(
            Math::Vector2D(1.0f, 0.0f),
            0.0f,
            Math::Vector2D(2.0f, 2.0f)
        );

        Math::Transform2D child(
            Math::Vector2D(1.0f, 0.0f),
            0.0f,
            Math::Vector2D(1.0f, 1.0f)
        );

        child.SetParent(&parent);

        // The world position of the child should be parent.position + (parent.scale * child.position)
        Math::Vector2D expectedWorldPos(3.0f, 0.0f);  // 1 + (2 * 1), 0 + (2 * 0)

        // Transform a point at the origin through the child
        Math::Vector2D transformedPoint = child.TransformPoint(Math::Vector2D(0.0f, 0.0f));

        return transformedPoint == expectedWorldPos && child.GetParent() == &parent;
    });

    // Test TransformPoint
    runTest("Transform2D TransformPoint", []() {
        Math::Transform2D transform(
            Math::Vector2D(1.0f, 2.0f),
            M_PI / 2.0f,  // 90 degrees
            Math::Vector2D(2.0f, 2.0f)
        );

        Math::Vector2D point(1.0f, 0.0f);
        Math::Vector2D expected(1.0f, 4.0f);  // Translate(1,2) + Rotate90(Scale(2,2) * (1,0))

        Math::Vector2D transformed = transform.TransformPoint(point);

        return (transformed - expected).Length() < 1e-5f;
    });

    // Test TransformVector
    runTest("Transform2D TransformVector", []() {
        Math::Transform2D transform(
            Math::Vector2D(1.0f, 2.0f),
            M_PI / 2.0f,  // 90 degrees
            Math::Vector2D(2.0f, 2.0f)
        );

        Math::Vector2D vector(1.0f, 0.0f);
        Math::Vector2D expected(0.0f, 2.0f);  // Rotate90(Scale(2,2) * (1,0)) - no translation

        Math::Vector2D transformed = transform.TransformVector(vector);

        return (transformed - expected).Length() < 1e-5f;
    });

    // Test TransformDirection (alias for TransformVector)
    runTest("Transform2D TransformDirection", []() {
        Math::Transform2D transform(
            Math::Vector2D(1.0f, 2.0f),
            M_PI / 2.0f,  // 90 degrees
            Math::Vector2D(2.0f, 2.0f)
        );

        Math::Vector2D direction(1.0f, 0.0f);
        Math::Vector2D expected(0.0f, 2.0f);  // Rotate90(Scale(2,2) * (1,0)) - no translation

        Math::Vector2D transformed = transform.TransformDirection(direction);

        return (transformed - expected).Length() < 1e-5f;
    });

    // Test InverseTransformPoint
    runTest("Transform2D InverseTransformPoint", []() {
        Math::Transform2D transform(
            Math::Vector2D(1.0f, 2.0f),
            M_PI / 2.0f,  // 90 degrees
            Math::Vector2D(2.0f, 2.0f)
        );

        Math::Vector2D original(3.0f, 4.0f);
        // First transform the point
        Math::Vector2D transformed = transform.TransformPoint(original);
        // Then inverse transform it - should get back the original
        Math::Vector2D inverseTransformed = transform.InverseTransformPoint(transformed);

        return (inverseTransformed - original).Length() < 1e-5f;
    });

    // Test IsUniform
    runTest("Transform2D IsUniform", []() {
        Math::Transform2D uniform(
            Math::Vector2D(0.0f, 0.0f),
            0.0f,
            Math::Vector2D(2.0f, 2.0f)
        );

        Math::Transform2D nonUniform(
            Math::Vector2D(0.0f, 0.0f),
            0.0f,
            Math::Vector2D(2.0f, 3.0f)
        );

        return uniform.IsUniform() && !nonUniform.IsUniform();
    });

    // Test IsIdentity
    runTest("Transform2D IsIdentity", []() {
        Math::Transform2D identity = Math::Transform2D::Identity();

        Math::Transform2D nonIdentity(
            Math::Vector2D(1.0f, 0.0f),
            0.0f,
            Math::Vector2D(1.0f, 1.0f)
        );

        return identity.IsIdentity() && !nonIdentity.IsIdentity();
    });

    // Test HasValidRotation
    runTest("Transform2D HasValidRotation", []() {
        Math::Transform2D validRotation(
            Math::Vector2D(0.0f, 0.0f),
            M_PI / 4.0f,
            Math::Vector2D(1.0f, 1.0f)
        );

        return validRotation.HasValidRotation();
    });

    // Test HasValidScale
    runTest("Transform2D HasValidScale", []() {
        Math::Transform2D validScale(
            Math::Vector2D(0.0f, 0.0f),
            0.0f,
            Math::Vector2D(2.0f, 3.0f)
        );

        return validScale.HasValidScale();
    });

    // Test Translation factory
    runTest("Transform2D Translation Factory", []() {
        Math::Vector2D translation(3.0f, 4.0f);
        Math::Transform2D transform = Math::Transform2D::Translation(translation);

        return transform.GetPosition() == translation &&
               transform.GetRotationRad() == 0.0f &&
               transform.GetScale() == Math::Vector2D(1.0f, 1.0f);
    });

    // Test RotationRad factory
    runTest("Transform2D RotationRad Factory", []() {
        float rotation = M_PI / 4.0f;  // 45 degrees
        Math::Transform2D transform = Math::Transform2D::RotationRad(rotation);

        return transform.GetPosition() == Math::Vector2D(0.0f, 0.0f) &&
               std::abs(transform.GetRotationRad() - rotation) < 1e-6f &&
               transform.GetScale() == Math::Vector2D(1.0f, 1.0f);
    });

    // Test RotationDeg factory
    runTest("Transform2D RotationDeg Factory", []() {
        float rotationDeg = 45.0f;
        Math::Transform2D transform = Math::Transform2D::RotationDeg(rotationDeg);

        return transform.GetPosition() == Math::Vector2D(0.0f, 0.0f) &&
               std::abs(transform.GetRotationDeg() - rotationDeg) < 1e-6f &&
               transform.GetScale() == Math::Vector2D(1.0f, 1.0f);
    });

    // Test Scaling factory (vector)
    runTest("Transform2D Scaling Factory (Vector)", []() {
        Math::Vector2D scale(2.0f, 3.0f);
        Math::Transform2D transform = Math::Transform2D::Scaling(scale);

        return transform.GetPosition() == Math::Vector2D(0.0f, 0.0f) &&
               transform.GetRotationRad() == 0.0f &&
               transform.GetScale() == scale;
    });

    // Test Scaling factory (uniform)
    runTest("Transform2D Scaling Factory (Uniform)", []() {
        float scale = 2.0f;
        Math::Transform2D transform = Math::Transform2D::Scaling(scale);

        return transform.GetPosition() == Math::Vector2D(0.0f, 0.0f) &&
               transform.GetRotationRad() == 0.0f &&
               transform.GetScale() == Math::Vector2D(scale, scale);
    });

    // Test Lerp
    runTest("Transform2D Lerp", []() {
        Math::Transform2D t1(
            Math::Vector2D(0.0f, 0.0f),
            0.0f,
            Math::Vector2D(1.0f, 1.0f)
        );

        Math::Transform2D t2(
            Math::Vector2D(10.0f, 20.0f),
            M_PI / 2.0f,  // 90 degrees
            Math::Vector2D(3.0f, 3.0f)
        );

        Math::Transform2D halfway = Math::Transform2D::Lerp(t1, t2, 0.5f);

        return halfway.GetPosition() == Math::Vector2D(5.0f, 10.0f) &&
               std::abs(halfway.GetRotationRad() - (M_PI / 4.0f)) < 1e-6f &&
               halfway.GetScale() == Math::Vector2D(2.0f, 2.0f);
    });

    // Test Equality/Inequality Operators
    runTest("Transform2D Equality Operators", []() {
        Math::Transform2D t1(
            Math::Vector2D(1.0f, 2.0f),
            M_PI / 4.0f,
            Math::Vector2D(2.0f, 3.0f)
        );

        Math::Transform2D t2(
            Math::Vector2D(1.0f, 2.0f),
            M_PI / 4.0f,
            Math::Vector2D(2.0f, 3.0f)
        );

        Math::Transform2D t3(
            Math::Vector2D(2.0f, 2.0f),
            M_PI / 4.0f,
            Math::Vector2D(2.0f, 3.0f)
        );

        return (t1 == t2) && (t1 != t3) && !(t1 == t3) && !(t1 != t2);
    });

    // Test Compose & Operator*
    runTest("Transform2D Compose & Operator*", []() {
        Math::Transform2D t1 = Math::Transform2D::Translation(Math::Vector2D(1.0f, 0.0f));
        Math::Transform2D t2 = Math::Transform2D::RotationRad(M_PI / 2.0f);  // 90 degrees

        Math::Transform2D composed1 = t1.Compose(t2);
        Math::Transform2D composed2 = t1 * t2;

        // For composed transform: first apply t2, then t1
        Math::Vector2D point(1.0f, 0.0f);
        Math::Vector2D expected(1.0f, 1.0f);  // Rotate (1,0) by 90 degrees = (0,1), then translate by (1,0)

        return composed1 == composed2 &&
               (composed1.TransformPoint(point) - expected).Length() < 1e-5f;
    });

    // Test Operator*=
    runTest("Transform2D Operator*=", []() {
        Math::Transform2D transform = Math::Transform2D::Translation(Math::Vector2D(1.0f, 0.0f));
        Math::Transform2D rotation = Math::Transform2D::RotationRad(M_PI / 2.0f);  // 90 degrees

        transform *= rotation;

        Math::Vector2D point(1.0f, 0.0f);
        Math::Vector2D expected(1.0f, 1.0f);  // Rotate (1,0) by 90 degrees = (0,1), then translate by (1,0)

        return (transform.TransformPoint(point) - expected).Length() < 1e-5f;
    });

    // Test Chaining Operations
    runTest("Transform2D Chaining Operations", []() {
        Math::Transform2D transform;

        transform.Translate(Math::Vector2D(10.0f, 0.0f));  // Position is now (10, 0)
        transform.RotateRad(M_PI / 2.0f);                  // 90 degrees rotation
        transform.Scale(2.0f);                             // Scale is now (2, 2)
        transform.Translate(Math::Vector2D(0.0f, 5.0f));   // Add (0, 5) to position

        Math::Vector2D point(1.0f, 0.0f);
        // Expected transformation: scale by 2, rotate by 90, translate by (10, 5)
        // (1, 0) -> (2, 0) -> (0, 2) -> (10, 7)
        Math::Vector2D expected(10.0f, 7.0f);

        return (transform.TransformPoint(point) - expected).Length() < 1e-5f;
    });

    std::cout << "\n=== End of Transform2D Tests ===\n";
    return true;
}