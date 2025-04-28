//
// Created on 2025-04-27.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>

namespace Math {

    /**
     * @brief Mathematical constants and utility values
     */
    namespace Constants {

        // Common mathematical constants

        /**
         * @brief Pi: The ratio of a circle's circumference to its diameter
         */
        constexpr float PI = 3.14159265358979323846f;

        /**
         * @brief Tau: Equal to 2π, represents a full circle in radians
         */
        constexpr float TAU = 2.0f * PI;

        /**
         * @brief Half Pi: π/2, represents a quarter circle in radians (90 degrees)
         */
        constexpr float HALF_PI = PI / 2.0f;

        /**
         * @brief Quarter Pi: π/4, represents an eighth of a circle in radians (45 degrees)
         */
        constexpr float QUARTER_PI = PI / 4.0f;

        /**
         * @brief Inverse Pi: 1/π
         */
        constexpr float INV_PI = 1.0f / PI;

        /**
         * @brief E: The base of natural logarithms
         */
        constexpr float E = 2.71828182845904523536f;

        /**
         * @brief Euler-Mascheroni constant
         */
        constexpr float EULER = 0.57721566490153286060f;

        /**
         * @brief Golden ratio: (1 + sqrt(5)) / 2
         */
        constexpr float GOLDEN_RATIO = 1.61803398874989484820f;

        /**
         * @brief Square root of 2
         */
        constexpr float SQRT_2 = 1.41421356237309504880f;

        /**
         * @brief Square root of 3
         */
        constexpr float SQRT_3 = 1.73205080756887729352f;

        /**
         * @brief Infinity: Represents a value that is larger than any finite value
         */
        constexpr float INFINITY_F = std::numeric_limits<float>::infinity();

        // Conversion factors

        /**
         * @brief Conversion factor from degrees to radians: π/180
         */
        constexpr float DEG_TO_RAD = PI / 180.0f;

        /**
         * @brief Conversion factor from radians to degrees: 180/π
         */
        constexpr float RAD_TO_DEG = 180.0f / PI;

        // Epsilon values for comparisons

        /**
         * @brief Small epsilon value for floating point comparisons
         */
        constexpr float EPSILON = 1e-6f;

        /**
         * @brief Medium epsilon value for floating point comparisons
         */
        constexpr float EPSILON_MEDIUM = 1e-5f;

        /**
         * @brief Large epsilon value for floating point comparisons
         */
        constexpr float EPSILON_LARGE = 1e-4f;

        /**
         * @brief Machine epsilon: The difference between 1.0 and the next representable floating-point value
         */
        constexpr float MACHINE_EPSILON = std::numeric_limits<float>::epsilon();

        // Limits

        /**
         * @brief Maximum value for a floating-point number
         */
        constexpr float MAX_FLOAT = std::numeric_limits<float>::max();

        /**
         * @brief Minimum positive value for a floating-point number
         */
        constexpr float MIN_FLOAT = std::numeric_limits<float>::min();

        /**
         * @brief Minimum value for a floating-point number
         */
        constexpr float LOWEST_FLOAT = std::numeric_limits<float>::lowest();

        // Common angles in radians

        /**
         * @brief 30 degrees in radians
         */
        constexpr float RADIANS_30 = PI / 6.0f;

        /**
         * @brief 45 degrees in radians
         */
        constexpr float RADIANS_45 = PI / 4.0f;

        /**
         * @brief 60 degrees in radians
         */
        constexpr float RADIANS_60 = PI / 3.0f;

        /**
         * @brief 90 degrees in radians
         */
        constexpr float RADIANS_90 = PI / 2.0f;

        /**
         * @brief 180 degrees in radians
         */
        constexpr float RADIANS_180 = PI;

        /**
         * @brief 270 degrees in radians
         */
        constexpr float RADIANS_270 = 3.0f * PI / 2.0f;

        /**
         * @brief 360 degrees in radians
         */
        constexpr float RADIANS_360 = 2.0f * PI;

        // Utility functions

        /**
         * @brief Checks if two floating-point values are approximately equal
         *
         * @param a First value
         * @param b Second value
         * @param epsilon Tolerance (default is EPSILON)
         * @return True if the values are approximately equal
         */
        inline bool FloatEquals(float a, float b, float epsilon = EPSILON) {
            return std::fabs(a - b) <= epsilon;
        }

        /**
         * @brief Checks if a floating-point value is approximately zero
         *
         * @param value Value to check
         * @param epsilon Tolerance (default is EPSILON)
         * @return True if the value is approximately zero
         */
        inline bool IsZero(float value, float epsilon = EPSILON) {
            return std::fabs(value) <= epsilon;
        }

        /**
         * @brief Checks if a floating-point value is approximately one
         *
         * @param value Value to check
         * @param epsilon Tolerance (default is EPSILON)
         * @return True if the value is approximately one
         */
        inline bool IsOne(float value, float epsilon = EPSILON) {
            return std::fabs(value - 1.0f) <= epsilon;
        }

    } // namespace Constants

} // namespace Math

#endif // CONSTANTS_H