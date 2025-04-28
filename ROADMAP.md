# MathEngine Development Roadmap
## 1. 📐 Matrix4x4
### ✅ Why first?
- Needed for 3D transforms, cameras, projections
- Without it, you can't move anything in 3D

### What to implement:
- Constructors (identity, from elements)
- Matrix × Matrix multiplication
- Matrix × Vector3D multiplication
- Determinant
- Inverse
- Transpose
- Build perspective, orthographic matrices (future)

## 2. 🎡 Quaternion
### ✅ Why second?
- 3D rotation without gimbal lock
- Essential for 3D Transform

### What to implement:
- Identity quaternion
- From axis-angle
- Normalize
- Inverse
- Quaternion × Quaternion
- Quaternion × Vector3D
- Slerp (spherical interpolation)

## 3. 🚀 Transform3D
### ✅ Why third?
- Combines Matrix4x4 + Quaternion + Vector3D into position/rotation/scale
- All your entities will use this to move in 3D space

### What to implement:
- Local Position, Rotation (Quaternion), Scale
- Local matrix generation
- Parent/child transform hierarchy
- Global transform computation

(Basically what you did in Transform2D but in 3D.)
## 4. 📚 MathUtils.h
### ✅ Why next?
- Small helper functions used everywhere
- (Clamp, Lerp, Min, Max, SmoothStep, etc.)

### What to implement:
- Clamp(T value, T min, T max)
- Lerp(float a, float b, float t)
- SmoothStep(float edge0, float edge1, float x)
- Saturate(float value) (Clamp to [0,1])
- Maybe DegreesToRadians, RadiansToDegrees

## 5. 🧱 Entity
### ✅ Why now?
- GameObject, actors, players — all are Entities
- Holds a Transform2D or Transform3D

### What to implement:
- Transform
- Update function (virtual)
- Unique ID (maybe)

## 6. 🌎 Scene
### ✅ Why here?
- Scene manages a list of Entities
- You update them, render them, manage the game world

### What to implement:
- List of Entities
- Update all Entities
- Add/Remove Entities
- (Maybe save/load later)

## 7. 🎥 Camera2D / Camera3D
### ✅ Finally cameras:
- View transformations to project world into screen

### What to implement for Camera2D:
- Position
- Zoom
- Build view matrix (Matrix2x2 or Matrix3x3)

### What to implement for Camera3D:
- Position
- Orientation (Quaternion)
- View matrix (Matrix4x4)
- Projection matrix (perspective or orthographic)
