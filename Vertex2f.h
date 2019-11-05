//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VERTEX2F_H
#define HW2_VERTEX2F_H

#include "Structs/Util.h"
#include "Matrix4x4.h"
#include <math.h>

enum Dimension {X, Y, Z};

class Vertex3f;
class Vertex2i;

class Vertex2f {
 public:
  Vertex2f(Vertex3f vertex, Dimension toIgnore);
  Vertex2f(float x, float y);

  float x, y;
};

class Vertex3f {
 public:
  Vertex3f(float x, float y, float z);
  float x, y, z;

  Vertex2f flatten(Dimension d) const;

  void translate(vector3 v);
  void rotate_around_axis(float alpha, vector3 p1, vector3 p2);
  void scale(float factor, vector3 centroid);
};

class Vertex2i {
 public:
  Vertex2i(int x, int y);
  int x, y;
};

#endif //HW2_VERTEX2F_H
