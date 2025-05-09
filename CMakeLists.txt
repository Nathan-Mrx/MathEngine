cmake_minimum_required(VERSION 3.10)
project(GameEngineMathematics)

set(CMAKE_CXX_STANDARD 20)

# Add all math source files
set(MATH_SOURCES
        Math/Transform2D.cpp
)

# Add all test source files
set(TEST_SOURCES
    Tests/TestUtils.cpp
    Tests/Vector2DTests.cpp
    Tests/Vector3DTests.cpp
    Tests/Matrix2DTests.cpp
    Tests/Matrix3DTests.cpp
    Tests/Matrix4DTests.cpp
    Tests/Transform2DTests.cpp
)

# Add executable with all source files
add_executable(GameEngineMathematics 
    main.cpp
    ${MATH_SOURCES}
    ${TEST_SOURCES}
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})