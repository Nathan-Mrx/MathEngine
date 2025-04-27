#include <iostream>
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"

int main() {
    // Vector2D Tests
    Math::Vector2D vec2A(3.0f, 4.0f);
    Math::Vector2D vec2B(1.0f, 2.0f);
    Math::Vector2D vec2C = vec2A + vec2B;

    std::cout << "Vector2D Addition: (" << vec2C.x << ", " << vec2C.y << ")\n";
    std::cout << "Vector2D Length: " << vec2A.Length() << "\n";
    std::cout << "Vector2D Angle: " << vec2A.AngleDeg(vec2B) << " degrees\n";
    std::cout << "Vector2D Dot Product: " << vec2A.Dot(vec2B) << "\n";
    std::cout << "Vector2D Cross Product: " << vec2A.Cross(vec2B) << "\n";
    std::cout << "Vector2D Distance: " << vec2A.Distance(vec2B) << "\n";
    std::cout << "Vector2D Normalized: (" << vec2A.Normalize().x << ", " << vec2A.Normalize().y << ")\n";
    std::cout << "Vector2D Angle in Radians: " << vec2A.AngleRad(vec2B) << " radians\n";

    // Vector3D Tests
    Math::Vector3D vec3A(1.0f, 2.0f, 3.0f);
    Math::Vector3D vec3B(4.0f, 5.0f, 6.0f);
    Math::Vector3D vec3C = vec3A + vec3B;

    std::cout << "Vector3D Addition: (" << vec3C.x << ", " << vec3C.y << ", " << vec3C.z << ")\n";
    std::cout << "Vector3D Length: " << vec3A.Length() << "\n";
    std::cout << "Vector3D Angle: " << vec3A.AngleDeg(vec3B) << " degrees\n";
    std::cout << "Vector3D Dot Product: " << vec3A.Dot(vec3B) << "\n";
    std::cout << "Vector3D Cross Product: (" << vec3A.Cross(vec3B).x << ", " << vec3A.Cross(vec3B).y << ", " << vec3A.Cross(vec3B).z << ")\n";
    std::cout << "Vector3D Distance: " << vec3A.Distance(vec3B) << "\n";
    std::cout << "Vector3D Normalized: (" << vec3A.Normalize().x << ", " << vec3A.Normalize().y << ", " << vec3A.Normalize().z << ")\n";
    std::cout << "Vector3D Triple Product: " << vec3A.TripleProduct(vec3B, Math::Vector3D(7.0f, 8.0f, 9.0f)) << "\n";
    std::cout << "Vector3D Zero: (" << Math::Vector3D::Zero().x << ", " << Math::Vector3D::Zero().y << ", " << Math::Vector3D::Zero().z << ")\n";
    std::cout << "Vector3D Angle in Degrees: " << vec3A.AngleDeg(vec3B) << " degrees\n";
    std::cout << "Vector3D Angle in Radians: " << vec3A.AngleRad(vec3B) << " radians\n";


    return 0;
}