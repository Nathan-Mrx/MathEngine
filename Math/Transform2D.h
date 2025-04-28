//
// Created by natha on 2025-04-26.
//

#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include <cmath>
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Matrix3D.h"

namespace Math {

    /**
     * @class Transform2D
     * @brief Represents a 2D transformation with position, rotation, and scale.
     *
     * The Transform2D class encapsulates a complete 2D transformation, including:
     * - Translation (position)
     * - Rotation (in radians)
     * - Scale (non-uniform)
     *
     * It provides methods for transforming points and vectors between spaces,
     * composing transformations, and converting to/from matrices.
     * It also supports parent-child hierarchies for nested transformations.
     */
    class Transform2D {
    private:
        /** The position (translation) component */
        Vector2D m_Position;

        /** The rotation component in radians */
        float m_Rotation;

        /** The scale component (x and y scales) */
        Vector2D m_Scale;

        /** Cached local transformation matrix */
        mutable Matrix3D m_LocalMatrix;

        /** Flag indicating whether the cached matrix needs updating */
        mutable bool m_IsDirty;

        /** Pointer to parent transform (optional for hierarchy) */
        Transform2D* m_Parent;

    private:
        /**
         * @brief Updates the internal transformation matrix if it's marked as dirty.
         */
        void UpdateMatrix() const;

    public:
        /**
         * @brief Default constructor - creates an identity transform.
         */
        Transform2D();

        /**
         * @brief Parameterized constructor with position, rotation, and scale.
         * @param position Initial position
         * @param rotation Initial rotation in radians (default = 0)
         * @param scale Initial scale (default = (1,1))
         */
        Transform2D(const Vector2D& position, float rotation = 0.0f, const Vector2D& scale = Vector2D(1.0f, 1.0f));

        /**
         * @brief Constructor with uniform scale - creates a transform with the same scale for x and y.
         * @param position Initial position
         * @param rotation Initial rotation in radians
         * @param uniformScale Value for both x and y scale
         */
        Transform2D(const Vector2D& position, float rotation, float uniformScale);

        // Static factory methods

        /**
         * @brief Creates an identity transform (no translation, rotation, or scaling).
         * @return Identity transform
         */
        static Transform2D Identity();

        /**
         * @brief Creates a transform with only translation.
         * @param translation The translation vector
         * @return A transform representing the translation
         */
        static Transform2D Translation(const Vector2D& translation);

        /**
         * @brief Creates a transform with only rotation (in radians).
         * @param radians The rotation angle in radians
         * @return A transform representing the rotation
         */
        static Transform2D RotationRad(float radians);

        /**
         * @brief Creates a transform with only rotation (in degrees).
         * @param degrees The rotation angle in degrees
         * @return A transform representing the rotation
         */
        static Transform2D RotationDeg(float degrees);

        /**
         * @brief Creates a transform with only non-uniform scaling.
         * @param scale The scale vector (x and y scale)
         * @return A transform representing the scaling
         */
        static Transform2D Scaling(const Vector2D& scale);

        /**
         * @brief Creates a transform with only uniform scaling.
         * @param uniformScale The scale value to apply to both x and y
         * @return A transform representing the uniform scaling
         */
        static Transform2D Scaling(float uniformScale);

        /**
         * @brief Linearly interpolates between two transforms.
         * @param a First transform
         * @param b Second transform
         * @param t Interpolation parameter (0-1)
         * @return Interpolated transform
         */
        static Transform2D Lerp(const Transform2D& a, const Transform2D& b, float t);

        // Setters and Getters

        /**
         * @brief Sets the position component.
         * @param position New position
         */
        void SetPosition(const Vector2D& position);

        /**
         * @brief Sets the rotation component in radians.
         * @param radians New rotation in radians
         */
        void SetRotationRad(float radians);

        /**
         * @brief Sets the rotation component in degrees.
         * @param degrees New rotation in degrees
         */
        void SetRotationDeg(float degrees);

        /**
         * @brief Sets the scale component (x and y).
         * @param scale New scale vector
         */
        void SetScale(const Vector2D& scale);

        /**
         * @brief Sets a uniform scale for both x and y.
         * @param uniformScale New scale value for both x and y
         */
        void SetScale(float uniformScale);

        /**
         * @brief Sets the parent transform for hierarchical transformations.
         * @param parent Pointer to the parent transform
         */
        void SetParent(Transform2D* parent);

        /**
         * @brief Gets the current position.
         * @return Reference to the position vector
         */
        const Vector2D& GetPosition() const;

        /**
         * @brief Gets the current rotation in radians.
         * @return Rotation in radians
         */
        float GetRotationRad() const;

        /**
         * @brief Gets the current rotation in degrees.
         * @return Rotation in degrees
         */
        float GetRotationDeg() const;

        /**
         * @brief Gets the current scale.
         * @return Reference to the scale vector
         */
        const Vector2D& GetScale() const;

        /**
         * @brief Gets the parent transform.
         * @return Pointer to the parent transform (nullptr if no parent)
         */
        Transform2D* GetParent() const;

        // Transform operations

        /**
         * @brief Translates (moves) the transform by the given vector.
         * @param translation The vector to translate by
         */
        void Translate(const Vector2D& translation);

        /**
         * @brief Rotates the transform by the given angle in radians.
         * @param radians The angle to rotate by in radians
         */
        void RotateRad(float radians);

        /**
         * @brief Rotates the transform by the given angle in degrees.
         * @param degrees The angle to rotate by in degrees
         */
        void RotateDeg(float degrees);

        /**
         * @brief Scales the transform by the given non-uniform scale factors.
         * @param scale The scale factors for x and y
         */
        void Scale(const Vector2D& scale);

        /**
         * @brief Scales the transform uniformly by the given factor.
         * @param uniformScale The scale factor to apply to both x and y
         */
        void Scale(float uniformScale);

        /**
         * @brief Transforms a point from local space to this transform's space.
         * @param point The point in local space
         * @return The transformed point
         */
        Vector2D TransformPoint(const Vector2D& point) const;

        /**
         * @brief Transforms a vector from local space to this transform's space.
         * Vectors are not affected by translation, only rotation and scale.
         * @param vector The vector in local space
         * @return The transformed vector
         */
        Vector2D TransformVector(const Vector2D& vector) const;

        /**
         * @brief Transforms a direction vector from local space to this transform's space.
         * Alias for TransformVector for better readability in some contexts.
         * @param direction The direction vector in local space
         * @return The transformed direction vector
         */
        Vector2D TransformDirection(const Vector2D& direction) const;

        /**
         * @brief Transforms a point from this transform's space back to local space.
         * @param point The point in this transform's space
         * @return The point in local space
         */
        Vector2D InverseTransformPoint(const Vector2D& point) const;

        /**
         * @brief Transforms a vector from this transform's space back to local space.
         * @param vector The vector in this transform's space
         * @return The vector in local space
         */
        Vector2D InverseTransformVector(const Vector2D& vector) const;

        /**
         * @brief Calculates the inverse of this transform.
         * @return The inverse transform
         */
        Transform2D Inverse() const;

        /**
         * @brief Composes this transform with another (this * other).
         * @param other The other transform to compose with
         * @return The composed transform
         */
        Transform2D Compose(const Transform2D& other) const;

        /**
         * @brief Operator * to compose transforms (equivalent to Compose).
         * @param other The other transform to compose with
         * @return The composed transform
         */
        Transform2D operator*(const Transform2D& other) const;

        /**
         * @brief Operator *= to compose transforms in-place.
         * @param other The other transform to compose with
         * @return Reference to this (modified) transform
         */
        Transform2D& operator*=(const Transform2D& other);

        /**
         * @brief Gets the local transformation matrix (excluding parent).
         * @return 3x3 transformation matrix
         */
        Matrix3D GetLocalMatrix() const;

        /**
         * @brief Gets the world transformation matrix (including parent).
         * @return 3x3 transformation matrix
         */
        Matrix3D GetWorldMatrix() const;

        /**
         * @brief Converts the transform to a 2x2 matrix (rotation and scale only).
         * @return 2x2 matrix representing rotation and scale
         */
        Matrix2D ToMatrix2D() const;

        // Utilities

        /**
         * @brief Checks if this transform is approximately an identity transform.
         * @param epsilon Tolerance for floating point comparison
         * @return true if the transform is approximately identity
         */
        bool IsIdentity(float epsilon = 1e-6f) const;

        /**
         * @brief Checks if this transform has the same value for x and y scale.
         * @return true if x and y scale are equal
         */
        bool IsUniform() const;

        /**
         * @brief Checks if the rotation is a valid value (not NaN or Infinity).
         * @return true if rotation is valid
         */
        bool HasValidRotation() const;

        /**
         * @brief Checks if scale values are valid (not zero, NaN, or Infinity).
         * @return true if scale is valid
         */
        bool HasValidScale() const;

        /**
         * @brief Equality comparison operator.
         * @param other Transform to compare with
         * @return true if transforms are equal
         */
        bool operator==(const Transform2D& other) const;

        /**
         * @brief Inequality comparison operator.
         * @param other Transform to compare with
         * @return true if transforms are not equal
         */
        bool operator!=(const Transform2D& other) const;

        /**
         * @brief Output stream operator for debugging.
         * @param os Output stream
         * @param transform Transform to output
         * @return Reference to the output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const Transform2D& transform);
    };

} // namespace Math

#endif // TRANSFORM2D_H