#include <iostream>
#include "Math/Constants.h"
#include "Tests/Vector2DTests.h"
#include "Tests/Vector3DTests.h"
#include "Tests/Matrix2DTests.h"
#include "Tests/Matrix3DTests.h"
#include "Tests/Matrix4DTests.h"
#include "Tests/Transform2DTests.h"

int main() {
    std::cout << "Running all tests...\n";

    RunVector2DTests();
    RunVector3DTests();
    RunMatrix2DTests();
    RunMatrix3DTests();
    RunMatrix4DTests();
    RunTransform2DTests();

    std::cout << "\nAll tests completed.\n";
    return 0;
}