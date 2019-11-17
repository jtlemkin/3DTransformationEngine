//
// Created by James Lemkin on 11/3/19.
//

#ifndef HW2_MATRIX4X4_H
#define HW2_MATRIX4X4_H

#include "../Vertex.h"

class Vertex;

class Matrix4x4 {
 public:
  float m[4][4];

  Matrix4x4();

  float& at(int i, int j);

  Vertex mult(Vertex v);
  Matrix4x4 mult(Matrix4x4 m2);
  Matrix4x4 transpose();
  void display();
};

#endif //HW2_MATRIX4X4_H
