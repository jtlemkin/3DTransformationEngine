//
// Created by James Lemkin on 11/3/19.
//

#ifndef HW2_MATRIX4X4_H
#define HW2_MATRIX4X4_H

#include "Vertex2f.h"

class Vertex3f;

class ColVector {
 public:
  explicit ColVector(Vertex3f p);
  ColVector();
  float v[4];

  float& at(int i);
};

class Matrix4x4 {
 public:
  float m[4][4];

  Matrix4x4();

  float& at(int i, int j);

  ColVector mult(ColVector v);
  Matrix4x4 mult(Matrix4x4 m2);
  Matrix4x4 transpose();
  void display();
};

#endif //HW2_MATRIX4X4_H
