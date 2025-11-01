# linkit

`linkit` is a lightweight and easy-to-use C++ library for 3D mathematics, designed to provide essential tools for graphics and physics applications. It includes classes for vectors, matrices, and quaternions, along with a rich set of mathematical operations.

## Features

- **Vector Operations:** `Vector3` and `Vector4` classes with support for dot products, cross products, normalization, and more.
- **Matrix Transformations:** `Matrix3` and `Matrix4` classes for creating and combining transformations like translation, rotation, and scaling.
- **Quaternion Rotations:** A `Quaternion` class for smooth and efficient rotations.
- **High Precision:** Uses a configurable `real` type for floating-point calculations, allowing for easy switching between `float` and `double`.
- **Operator Overloading:** Intuitive and clean syntax through operator overloading for mathematical operations.

## Core Components

### `Vector3` and `Vector4`

The vector classes provide the foundation for representing points and directions in 3D space.

- **Creation:**
  ```cpp
  linkit::Vector3 v(1.0, 2.0, 3.0);
  ```
- **Operations:**
  - Magnitude and Normalization: `magnitude()`, `normalize()`
  - Dot and Cross Product: `*`, `%`
  - Scalar and Vector Arithmetic: `+`, `-`, `*`, `/`

### `Matrix3` and `Matrix4`

The matrix classes are essential for transformations in 3D graphics.

- **Creation:**
  ```cpp
  linkit::Matrix4 m; // Identity matrix
  ```
- **Transformations:**
  - `Matrix4::translate(Vector3(x, y, z))`
  - `Matrix4::scale(Vector3(x, y, z))`
  - `Matrix4::rotate(angle, Vector3(axis))`
- **Operations:**
  - Matrix-Matrix and Matrix-Vector Multiplication: `*`
  - Determinant: `determinant()`

## Getting Started

To use `linkit` in your project, include the main header file:

```cpp
#include <linkit/linkit.h>
```

### Example Usage

Here's a simple example of how to create and use a transformation matrix:

```cpp
#include <iostream>
#include <linkit/linkit.h>

int main() {
    // Create a vector
    linkit::Vector3 point(1.0, 0.0, 0.0);

    // Create a transformation matrix
    linkit::Matrix4 rotation = linkit::Matrix4::rotate(linkit::PI / 2.0, linkit::Vector3(0.0, 1.0, 0.0)); // 90-degree rotation around Y-axis
    linkit::Matrix4 translation = linkit::Matrix4::translate(linkit::Vector3(0.0, 0.0, 5.0));

    // Combine transformations
    linkit::Matrix4 transform = translation * rotation;

    // Apply the transformation
    linkit::Vector3 transformed_point = transform * point;

    // Print the result
    std::cout << "Transformed point: " << transformed_point.to_string() << std::endl;

    return 0;
}
```

## Building and Testing

`linkit` uses CMake for building the project.

### Build

To build the library and tests, run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

### Run Tests

To run the tests, execute the following command from the `build` directory:

```bash
./test_linkit
```

