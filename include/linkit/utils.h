//
// Created by carlos on 9/29/25.
//

#ifndef LINKIT_UTILS_H
#define LINKIT_UTILS_H
#include "vector4.h"
#include "vector3.h"

inline linkit::Vector4 to_vector4(const linkit::Vector3& vec, const linkit::real w = 1) {
    return linkit::Vector4(vec.x, vec.y, vec.z, w);
}

inline linkit::Vector3 to_vector3(const linkit::Vector4& vec) {
    return linkit::Vector3(vec.x, vec.y, vec.z);
}

#endif //LINKIT_UTILS_H