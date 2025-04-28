//
// Created by natha on 2025-04-26.
//

#include "Transform2D.h"
#include "Constants.h"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace Math {

    // Private helper to update the transformation matrix
    void Transform2D::UpdateMatrix() const {
        if (m_IsDirty) {
            // Create rotation matrix
            float cosTheta = std::cos(m_Rotation);
            float sinTheta = std::sin(m_Rotation);

            // Build transformation matrix (scale, then rotate, then translate)
            m_LocalMatrix = Matrix3D(
                m_Scale.x * cosTheta, -m_Scale.y * sinTheta, m_Position.x,
                m_Scale.x * sinTheta,  m_Scale.y * cosTheta, m_Position.y,
                0.0f,                  0.0f,                 1.0f
            );

            m_IsDirty = false;
        }
    }

    // Default constructor - creates identity transform
    Transform2D::Transform2D()
        : m_Position(0.0f, 0.0f),
          m_Rotation(0.0f),
          m_Scale(1.0f, 1.0f),
          m_IsDirty(true),
          m_Parent(nullptr)
    {
    }

    // Parameterized constructor with position, rotation, and scale
    Transform2D::Transform2D(const Vector2D& position, float rotation, const Vector2D& scale)
        : m_Position(position),
          m_Rotation(rotation),
          m_Scale(scale),
          m_IsDirty(true),
          m_Parent(nullptr)
    {
    }

    // Parameterized constructor with uniform scale
    Transform2D::Transform2D(const Vector2D& position, float rotation, float uniformScale)
        : m_Position(position),
          m_Rotation(rotation),
          m_Scale(uniformScale, uniformScale),
          m_IsDirty(true),
          m_Parent(nullptr)
    {
    }

    // Static factory methods

    Transform2D Transform2D::Identity() {
        return Transform2D();
    }

    Transform2D Transform2D::Translation(const Vector2D& translation) {
        return Transform2D(translation, 0.0f, Vector2D(1.0f, 1.0f));
    }

    Transform2D Transform2D::RotationRad(float radians) {
        return Transform2D(Vector2D(0.0f, 0.0f), radians, Vector2D(1.0f, 1.0f));
    }

    Transform2D Transform2D::RotationDeg(float degrees) {
        return Transform2D(Vector2D(0.0f, 0.0f), degrees * Constants::DEG_TO_RAD, Vector2D(1.0f, 1.0f));
    }

    Transform2D Transform2D::Scaling(const Vector2D& scale) {
        return Transform2D(Vector2D(0.0f, 0.0f), 0.0f, scale);
    }

    Transform2D Transform2D::Scaling(float uniformScale) {
        return Transform2D(Vector2D(0.0f, 0.0f), 0.0f, Vector2D(uniformScale, uniformScale));
    }

    Transform2D Transform2D::Lerp(const Transform2D& a, const Transform2D& b, float t) {
        // Clamp t to the range [0, 1]
        t = std::max(0.0f, std::min(1.0f, t));

        // Linearly interpolate position and scale
        Vector2D position = a.m_Position + (b.m_Position - a.m_Position) * t;
        Vector2D scale = a.m_Scale + (b.m_Scale - a.m_Scale) * t;

        // For rotation, we need to handle wrapping properly
        float rotA = a.m_Rotation;
        float rotB = b.m_Rotation;

        // Ensure shortest path rotation
        while (rotB - rotA > Constants::PI) rotA += Constants::TAU;
        while (rotA - rotB > Constants::PI) rotB += Constants::TAU;

        float rotation = rotA + (rotB - rotA) * t;

        // Create interpolated transform
        return Transform2D(position, rotation, scale);
    }

    // Setters and Getters

    void Transform2D::SetPosition(const Vector2D& position) {
        m_Position = position;
        m_IsDirty = true;
    }

    void Transform2D::SetRotationRad(float radians) {
        m_Rotation = radians;
        m_IsDirty = true;
    }

    void Transform2D::SetRotationDeg(float degrees) {
        m_Rotation = degrees * Constants::DEG_TO_RAD;
        m_IsDirty = true;
    }

    void Transform2D::SetScale(const Vector2D& scale) {
        m_Scale = scale;
        m_IsDirty = true;
    }

    void Transform2D::SetScale(float uniformScale) {
        m_Scale.x = m_Scale.y = uniformScale;
        m_IsDirty = true;
    }

    void Transform2D::SetParent(Transform2D* parent) {
        m_Parent = parent;
    }

    const Vector2D& Transform2D::GetPosition() const {
        return m_Position;
    }

    float Transform2D::GetRotationRad() const {
        return m_Rotation;
    }

    float Transform2D::GetRotationDeg() const {
        return m_Rotation * Constants::RAD_TO_DEG;
    }

    const Vector2D& Transform2D::GetScale() const {
        return m_Scale;
    }

    Transform2D* Transform2D::GetParent() const {
        return m_Parent;
    }

    // Transform operations

    void Transform2D::Translate(const Vector2D& translation) {
        m_Position += translation;
        m_IsDirty = true;
    }

    void Transform2D::RotateRad(float radians) {
        m_Rotation += radians;
        m_IsDirty = true;
    }

    void Transform2D::RotateDeg(float degrees) {
        m_Rotation += degrees * Constants::DEG_TO_RAD;
        m_IsDirty = true;
    }

    void Transform2D::Scale(const Vector2D& scale) {
        m_Scale.x *= scale.x;
        m_Scale.y *= scale.y;
        m_IsDirty = true;
    }

    void Transform2D::Scale(float uniformScale) {
        m_Scale.x *= uniformScale;
        m_Scale.y *= uniformScale;
        m_IsDirty = true;
    }

    Vector2D Transform2D::TransformPoint(const Vector2D& point) const {
        Matrix3D worldMatrix = GetWorldMatrix();

        // Convert point to homogeneous coordinates, multiply by matrix, then convert back
        return Vector2D(
            worldMatrix(0, 0) * point.x + worldMatrix(0, 1) * point.y + worldMatrix(0, 2),
            worldMatrix(1, 0) * point.x + worldMatrix(1, 1) * point.y + worldMatrix(1, 2)
        );
    }


    Vector2D Transform2D::TransformVector(const Vector2D& vector) const {
        Matrix3D worldMatrix = GetWorldMatrix();

        // For vectors, we ignore translation (last column)
        return Vector2D(
            worldMatrix(0, 0) * vector.x + worldMatrix(0, 1) * vector.y,
            worldMatrix(1, 0) * vector.x + worldMatrix(1, 1) * vector.y
        );
    }


    Vector2D Transform2D::TransformDirection(const Vector2D& direction) const {
        // Direction vectors are transformed the same way as regular vectors
        return TransformVector(direction);
    }

    Vector2D Transform2D::InverseTransformPoint(const Vector2D& point) const {
        // Get the inverse of the world matrix
        Transform2D inverse = Inverse();

        // Use the inverse transform to transform the point
        return inverse.TransformPoint(point);
    }

    Vector2D Transform2D::InverseTransformVector(const Vector2D& vector) const {
        // Get the inverse of the world matrix
        Transform2D inverse = Inverse();

        // Use the inverse transform to transform the vector
        return inverse.TransformVector(vector);
    }

    Transform2D Transform2D::Inverse() const {
        // For a TRS matrix, the inverse has these properties:
        // - Inverse position = -R^T * T (where R^T is transpose of rotation and T is translation)
        // - Inverse rotation = -R (negative of original rotation)
        // - Inverse scale = 1/S (reciprocal of original scale)

        float invRotation = -m_Rotation;
        Vector2D invScale(1.0f / m_Scale.x, 1.0f / m_Scale.y);

        // Calculate the inverse position
        float cosTheta = std::cos(invRotation);
        float sinTheta = std::sin(invRotation);

        Vector2D invPosition(
            -(cosTheta * m_Position.x - sinTheta * m_Position.y) * invScale.x,
            -(sinTheta * m_Position.x + cosTheta * m_Position.y) * invScale.y
        );

        // Create the inverse transform
        Transform2D inverse(invPosition, invRotation, invScale);

        // If there's a parent, we need to get the world transform's inverse
        if (m_Parent) {
            // First get our world transform
            Matrix3D worldMatrix = GetWorldMatrix();

            // For proper handling with parents, we should invert the world matrix
            // This is a simplified approach; a proper implementation would invert the full matrix
            Transform2D parentInverse = m_Parent->Inverse();
            return inverse * parentInverse;
        }

        return inverse;
    }

    Transform2D Transform2D::Compose(const Transform2D& other) const {
        // Get matrices for both transforms
        Matrix3D thisMat = GetLocalMatrix();
        Matrix3D otherMat = other.GetLocalMatrix();

        // Multiply matrices to compose the transforms
        Matrix3D resultMat = thisMat * otherMat;

        // Extract TRS components from the resulting matrix
        // This is an approximation and may lose precision for complex transformations

        // Extract position from the last column
        Vector2D position(resultMat(0, 2), resultMat(1, 2));

        // Extract scale (length of the first two column vectors)
        float scaleX = std::sqrt(resultMat(0, 0) * resultMat(0, 0) + resultMat(1, 0) * resultMat(1, 0));
        float scaleY = std::sqrt(resultMat(0, 1) * resultMat(0, 1) + resultMat(1, 1) * resultMat(1, 1));


        // Extract rotation (atan2 of the normalized first column)
        float rotation = std::atan2(resultMat(1, 0) / scaleX, resultMat(0, 0) / scaleX);

        return Transform2D(position, rotation, Vector2D(scaleX, scaleY));
    }

    Transform2D Transform2D::operator*(const Transform2D& other) const {
        return Compose(other);
    }

    Transform2D& Transform2D::operator*=(const Transform2D& other) {
        *this = Compose(other);
        return *this;
    }

    Matrix3D Transform2D::GetLocalMatrix() const {
        UpdateMatrix(); // Update matrix if needed
        return m_LocalMatrix;
    }

    Matrix3D Transform2D::GetWorldMatrix() const {
        if (m_Parent) {
            // If there's a parent, we need to multiply our local matrix by the parent's world matrix
            return m_Parent->GetWorldMatrix() * GetLocalMatrix();
        } else {
            // If no parent, world matrix is the same as local matrix
            return GetLocalMatrix();
        }
    }

    Matrix2D Transform2D::ToMatrix2D() const {
        // Extract just the rotation and scale part (top-left 2x2 submatrix)
        Matrix3D matrix = GetLocalMatrix();
        return Matrix2D(
            matrix(0, 0), matrix(0, 1),
            matrix(1, 0), matrix(1, 1)
        );
    }

    // Utilities

    bool Transform2D::IsIdentity(float epsilon) const {
        return m_Position.Length() < epsilon &&
               std::abs(m_Rotation) < epsilon &&
               std::abs(m_Scale.x - 1.0f) < epsilon &&
               std::abs(m_Scale.y - 1.0f) < epsilon;
    }

    bool Transform2D::IsUniform() const {
        // Check if x and y scales are equal (within a small epsilon)
        const float epsilon = 1e-6f;
        return std::abs(m_Scale.x - m_Scale.y) < epsilon;
    }

    bool Transform2D::HasValidRotation() const {
        // Check if rotation is a valid number (not NaN or Infinity)
        return std::isfinite(m_Rotation);
    }

    bool Transform2D::HasValidScale() const {
        // Check if scale values are valid (not zero, NaN, or Infinity)
        return std::isfinite(m_Scale.x) && std::isfinite(m_Scale.y) &&
               std::abs(m_Scale.x) > 1e-6f && std::abs(m_Scale.y) > 1e-6f;
    }

    bool Transform2D::operator==(const Transform2D& other) const {
        // Epsilon comparison for floating point values
        const float epsilon = 1e-6f;

        return (m_Position - other.m_Position).Length() < epsilon &&
               std::abs(m_Rotation - other.m_Rotation) < epsilon &&
               (m_Scale - other.m_Scale).Length() < epsilon;
    }

    bool Transform2D::operator!=(const Transform2D& other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& os, const Transform2D& transform) {
        os << "Transform2D(Position: " << transform.m_Position
           << ", Rotation: " << transform.m_Rotation
           << " rad (" << transform.GetRotationDeg() << " deg)"
           << ", Scale: " << transform.m_Scale << ")";
        return os;
    }

} // namespace Math