//
// Created by James Lemkin on 11/16/19.
//

#ifndef HW2_VECTOR3F_H
#define HW2_VECTOR3F_H

class Vector3f {
 public:

  float x, y, z;

  Vector3f(float x, float y, float z);

  Vector3f add(const Vector3f v2) const;
  Vector3f minus(const Vector3f v2) const;
  Vector3f divideBy(float n) const;
  Vector3f multiply(float n) const;
  float magnitude() const;
  Vector3f normalize() const;
  float dot(Vector3f v2) const;
};

#endif //HW2_VECTOR3F_H
