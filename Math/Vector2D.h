//
// Created by natha on 2025-04-26.
//

#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>

namespace Math {
    struct Vector2D {
        float x, y;

        constexpr Vector2D() = default;

        constexpr Vector2D(float x, float y) : x(x), y(y) {}

        /**
         * Adds two 2D vectors.
         * @param OtherVector The vector to add.
         * @return The sum of the two vectors.
         */
        constexpr Vector2D operator+(const Vector2D& OtherVector) const {
            return Vector2D(x + OtherVector.x, y + OtherVector.y);
        }

        /**
         * Adds another vector to this vector.
         * @param OtherVector The vector to add.
         */
        inline void operator+=(const Vector2D& OtherVector) {
            x += OtherVector.x;
            y += OtherVector.y;
        }

        /**
         * Subtracts two 2D vectors.
         * @param OtherVector The vector to subtract.
         * @return The difference of the two vectors.
         */
        constexpr Vector2D operator-(const Vector2D& OtherVector) const {
            return Vector2D(x - OtherVector.x, y - OtherVector.y);
        }

        /**
         * Subtracts another vector from this vector.
         * @param OtherVector The vector to subtract.
         */
        inline void operator-=(const Vector2D& OtherVector) {
            x -= OtherVector.x;
            y -= OtherVector.y;
        }

        /**
         * Multiplies this vector by a scalar.
         * @param Scalar The scalar to multiply by.
         * @return The product of the vector and the scalar.
         */
        constexpr Vector2D operator*(float Scalar) const {
            return Vector2D(x * Scalar, y * Scalar);
        }

        /**
         * Multiplies this vector by a scalar.
         * @param Scalar The scalar to multiply by.
         */
        inline void operator*=(float Scalar) {
            x *= Scalar;
            y *= Scalar;
        }

        /**
         * Divides this vector by a scalar.
         * @param Scalar The scalar to divide by.
         * @return The quotient of the vector and the scalar.
         */
        constexpr Vector2D operator/(float Scalar) const {
            return Vector2D(x / Scalar, y / Scalar);
        }

        /**
         * Divides this vector by a scalar.
         * @param Scalar The scalar to divide by.
         */
        inline void operator/=(float Scalar) {
            x /= Scalar;
            y /= Scalar;
        }

        /**
         * @brief Calculates the dot product of two 2D vectors.
         *
         * The dot product is a scalar value that represents the cosine of the angle between the two vectors
         * The dot product is calculated as:
         *          Dot(A, B) = Ax * Bx + Ay * By
         *
         * @param OtherVector The vector to dot with.
         * @return The dot product of the two vectors.
         */
        constexpr float Dot(const Vector2D& OtherVector) const {
            return x * OtherVector.x + y * OtherVector.y;
        }

        /**
         * @brief Calculates the length (magnitude) of the vector.
         *
         * The length of a vector is calculated as:
         *          Length = sqrt(x^2 + y^2)
         *
         * @return The length of the vector.
         */
        inline float Length() const {
            return std::sqrt(x * x + y * y);
        }

        /**
         * @brief Normalizes the vector.
         *
         * Normalization scales the vector to have a length of 1.
         * The normalized vector is calculated as:
         *          Normalized = Vector / Length
         *
         * @return The normalized vector.
         */
        inline Vector2D Normalize() const {
            float length = Length();
            if (length == 0) {
                return Vector2D(0, 0); // Avoid division by zero
            }
            return Vector2D(x / length, y / length);
        }

        /**
         * @brief Calculates the distance between two 2D vectors.
         *
         * The distance is calculated as:
         *          Distance = sqrt((x2 - x1)^2 + (y2 - y1)^2)
         *
         * @param OtherVector The vector to calculate the distance to.
         * @return The distance between the two vectors.
         */
        inline float Distance(const Vector2D& OtherVector) const {
            return std::sqrt((OtherVector.x - x) * (OtherVector.x - x) +
                             (OtherVector.y - y) * (OtherVector.y - y));
        };

        /**
         * @brief Calculates the cross product of two 2D vectors.
         *
         * In 2D, the cross product results in a scalar representing the magnitude of a pseudo-vector perpendicular to the plane.
         * The cross product is calculated as:
         *          Cross(A, B) = Ax * By - Ay * Bx
         *
         * @param OtherVector The vector to cross with.
         * @return The cross product of the two vectors.
         */
        constexpr float Cross(const Vector2D& OtherVector) const {
            return x * OtherVector.y - y * OtherVector.x;
        }

        /**
         * @brief Calculates the angle between two 2D vectors.
         *
         * The angle is calculated using the dot product and the lengths of the vectors:
         *          Angle = acos(Dot(A, B) / (Length(A) * Length(B)))
         *
         * @param OtherVector The vector to calculate the angle with.
         * @return The angle between the two vectors in radians.
         */
        inline float AngleRad(const Vector2D& OtherVector) const {
            float dotProduct = Dot(OtherVector);
            float lengths = Length() * OtherVector.Length();
            if (lengths == 0) {
                return 0; // Avoid division by zero
            }
            return std::acos(dotProduct / lengths);
        }

        /**
         * @brief Calculates the angle between two 2D vectors in degrees.
         *
         * The angle is calculated using the dot product and the lengths of the vectors:
         *          Angle = acos(Dot(A, B) / (Length(A) * Length(B))) * (180 / PI)
         *
         * @param OtherVector The vector to calculate the angle with.
         * @return The angle between the two vectors in degrees.
         */
        inline float AngleDeg(const Vector2D& OtherVector) const {
            float angleInRadians = AngleRad(OtherVector);
            return angleInRadians * (180.0f / M_PI);
        }
    };
};

#endif //VECTOR2D_H
