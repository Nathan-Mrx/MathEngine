//
// Created by natha on 2025-04-26.
//

#ifndef VECTOR3_H
#define VECTOR3_H
#include <cmath>

namespace Math {
    struct Vector3D {
        float x, y, z;

        constexpr Vector3D() = default;

        constexpr Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

        /**
         * Adds two 3D vectors.
         * @param OtherVector The vector to add.
         * @return The sum of the two vectors.
         */
        constexpr Vector3D operator+(const Vector3D& OtherVector) const {
            return {x + OtherVector.x, y + OtherVector.y, z + OtherVector.z};
        }

        /**
         * Adds another vector to this vector.
         * @param OtherVector The vector to add.
         */
        inline void operator+=(const Vector3D& OtherVector) {
            x += OtherVector.x;
            y += OtherVector.y;
            z += OtherVector.z;
        }

        /**
         * Subtracts two 3D vectors.
         * @param OtherVector The vector to subtract.
         * @return The difference of the two vectors.
         */
        constexpr Vector3D operator-(const Vector3D& OtherVector) const {
            return {x - OtherVector.x, y - OtherVector.y, z - OtherVector.z};
        }

        /**
         * Subtracts another vector from this vector.
         * @param OtherVector The vector to subtract.
         */
        inline void operator-=(const Vector3D& OtherVector) {
            x -= OtherVector.x;
            y -= OtherVector.y;
            z -= OtherVector.z;
        }

        /**
         * Multiplies this vector by a scalar.
         * @param Scalar The scalar to multiply by.
         * @return The product of the vector and the scalar.
         */
        constexpr Vector3D operator*(float Scalar) const {
            return {x * Scalar, y * Scalar, z * Scalar};
        }

        /**
         * Multiplies this vector by a scalar.
         * @param Scalar The scalar to multiply by.
         */
        inline void operator*=(float Scalar) {
            x *= Scalar;
            y *= Scalar;
            z *= Scalar;
        }

        /**
         * Divides this vector by a scalar.
         * @param Scalar The scalar to divide by.
         * @return The quotient of the vector and the scalar.
         */
        constexpr Vector3D operator/(float Scalar) const {
            return {x / Scalar, y / Scalar, z / Scalar};
        }

        /**
         * Divides this vector by a scalar.
         * @param Scalar The scalar to divide by.
         */
        inline void operator/=(float Scalar) {
            x /= Scalar;
            y /= Scalar;
            z /= Scalar;
        }

        /**
         * Calculates the dot product of two 3D vectors.
         *
         * The dot product is a scalar value that represents the cosine of the angle between the two vectors
         * The dot product is calculated as:
         *          Dot(A, B) = Ax * Bx + Ay * By + Az * Bz
         *
         * @param OtherVector The vector to dot with.
         * @return The dot product of the two vectors.
         */
        [[nodiscard]] constexpr float Dot(const Vector3D& OtherVector) const {
            return x * OtherVector.x + y * OtherVector.y + z * OtherVector.z;
        }

        /**
         * Calculates the length (magnitude) of the vector.
         *
         * The length of a vector is calculated as:
         *          Length = sqrt(x^2 + y^2 + z^2)
         *
         * @return The length of the vector.
         */
        [[nodiscard]] inline float Length() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        /**
         * Normalizes the vector.
         *
         * The normalized vector has a length of 1 and points in the same direction as the original vector.
         * If the length is zero, it returns a zero vector.
         *
         * @return The normalized vector.
         */
        [[nodiscard]] inline Vector3D Normalize() const {
            float length = Length();
            if (length == 0) {
                return {0, 0, 0}; // Avoid division by zero
            }
            return {x / length, y / length, z / length};
        }

        /**
         * Calculates the angle between two 3D vectors in radians.
         *
         * The angle is calculated using the dot product and the lengths of the vectors:
         *          Angle = acos(Dot(A, B) / (Length(A) * Length(B)))
         *
         * @param OtherVector The vector to calculate the angle with.
         * @return The angle between the two vectors in radians.
         */
        [[nodiscard]] inline float AngleRad(const Vector3D& OtherVector) const {
            float dotProduct = Dot(OtherVector);
            float lengths = Length() * OtherVector.Length();
            if (lengths == 0) {
                return 0; // Avoid division by zero
            }
            return std::acos(dotProduct / lengths);
        }
        /**
         * Calculates the distance between two 3D vectors.
         *
         * The distance is calculated as:
         *          Distance = sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
         *
         * @param OtherVector The vector to calculate the distance to.
         * @return The distance between the two vectors.
         */
        [[nodiscard]] inline float Distance(const Vector3D& OtherVector) const {
            return std::sqrt((OtherVector.x - x) * (OtherVector.x - x) +
                             (OtherVector.y - y) * (OtherVector.y - y) +
                             (OtherVector.z - z) * (OtherVector.z - z));
        }

        /**
         * Calculates the cross product of two 3D vectors.
         *
         * The cross product is a vector that is perpendicular to both input vectors.
         * The cross product is calculated as:
         *          Cross(A, B) = (Ay * Bz - Az * By, Az * Bx - Ax * Bz, Ax * By - Ay * Bx)
         *
         * @param OtherVector The vector to cross with.
         * @return The cross product of the two vectors.
         */
        [[nodiscard]] constexpr Vector3D Cross(const Vector3D& OtherVector) const {
            return {y * OtherVector.z - z * OtherVector.y,
                            z * OtherVector.x - x * OtherVector.z,
                            x * OtherVector.y - y * OtherVector.x};
        }

        /**
         * Calculates the triple product of three 3D vectors.
         *
         * The triple product is a scalar value that represents the volume of the parallelepiped formed by the three vectors.
         * Scalar triple product represents signed volume.
         * The triple product is calculated as:
         *           TripleProduct(A, B, C) = A . (B x C)
         *
         * @param OtherVector1 The first vector.
         * @param OtherVector2 The second vector.
         * @return The triple product of the three vectors.
         */
        [[nodiscard]] inline float TripleProduct(const Vector3D& OtherVector1, const Vector3D& OtherVector2) const {
            return Dot(OtherVector1.Cross(OtherVector2));
        }

        /**
         * Calculates the angle between two 3D vectors in degrees.
         *
         * The angle is calculated using the dot product and the lengths of the vectors:
         *         Angle = acos(Dot(A, B) / (Length(A) * Length(B))) * (180 / PI)
         *
         * @param OtherVector The vector to calculate the angle with.
         * @return The angle between the two vectors in degrees.
         */
        [[nodiscard]] inline float AngleDeg(const Vector3D& OtherVector) const {
            return AngleRad(OtherVector) * (180.0f / M_PI);
        }

        /**
         * @brief Returns a zero vector (0, 0, 0).
         *
         * @return A zero vector.
         */
        static Vector3D Zero() {
            return {0, 0, 0};
        }

        /**
         * @brief Returns a unit vector (1, 1, 1).
         *
         * @return A unit vector.
         */
        static Vector3D Unit() {
            return {1, 1, 1};
        }

        /**
         *  @brief Returns whether the vector is a zero vector.
         *
         *  @return True if the vector is a zero vector, false otherwise.
         */
        [[nodiscard]] inline bool IsZero() const {
            return (x == 0 && y == 0 && z == 0);
        }
    };
};
#endif //VECTOR3_H
