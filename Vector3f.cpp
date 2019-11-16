//
// Created by James Lemkin on 11/16/19.
//

#include <cmath>
#include "Vector3f.h"
Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3f Vector3f::add(const Vector3f v2) const {
  return Vector3f(x + v2.x, y + v2.y, z + v2.z);
}

Vector3f Vector3f::divideBy(float n) const {
  return Vector3f(x/n, y/n, z/n);
}

float Vector3f::magnitude() const {
  return std::sqrt(x * x + y * y + z * z);
}
Vector3f Vector3f::normalize() const {
  return divideBy(magnitude());
}
