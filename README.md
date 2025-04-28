# MathEngine

A modern, modular C++20 mathematics library built for 2D and 3D game engine development.

---

## ✨ Features

- **Vector2D** and **Vector3D** with comprehensive operations
- **Matrix2D** and **Matrix3D** implementations
- **Transform2D** for position, rotation, and scale in 2D space
- **Clean architecture** with modern C++20 practices
- **Comprehensive unit tests** for reliability
- **Auto-generated documentation** with Doxygen
- **Full MIT license** for commercial and personal use

### 🚀 Coming Soon
- **Matrix4x4** for 3D transformations and projections
- **Quaternions** for 3D rotation without gimbal lock
- **Transform3D** for 3D space manipulations
- **Math utilities** library with common functions
- **Entity Component System** foundations
- **Camera systems** for 2D and 3D rendering

---

## 🛠️ Project Structure
```
/Math - Core mathematics classes Vector2D.h - 2D vector operations Vector3D.h - 3D vector operations Matrix2D.h - 2×2 matrix operations Matrix3D.h - 3×3 matrix operations Transform2D.h - 2D transformation (position, rotation, scale) Constants.h - Mathematical constants /Tests - Comprehensive test suite Vector2DTests - Tests for 2D vector operations Vector3DTests - Tests for 3D vector operations Matrix2DTests - Tests for 2×2 matrix operations Matrix3DTests - Tests for 3×3 matrix operations Transform2DTests - Tests for 2D transformations /Docs - Generated documentation /.github - CI/CD workflows ROADMAP.md - Development plan and future features
``` 

---

## 🚀 Getting Started

### Build Requirements
- C++20 compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)
- CMake 3.16+
- Doxygen (optional, for documentation generation)

### Building with CMake
```
bash mkdir build cd build cmake .. make
``` 

### Running Tests

The project includes a comprehensive test suite. After building:
```
bash ./GameEngineMathematics
``` 

This will run all tests and report their status.

---

## 📚 Documentation

Documentation is automatically generated with **Doxygen** and deployed via **GitHub Pages**.

To generate locally:
```
bash doxygen Doxyfile
``` 

The documentation will be available in the `/Docs/html/` directory.

---

## 🗺️ Roadmap

See [ROADMAP.md](ROADMAP.md) for detailed development plans, including:
- Matrix4x4 implementation
- Quaternion support
- Transform3D class
- MathUtils library
- Entity component system
- Scene management
- Camera systems

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
