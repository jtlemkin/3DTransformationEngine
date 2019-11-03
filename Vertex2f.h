//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VERTEX2F_H
#define HW2_VERTEX2F_H

#include "Structs/Util.h"
#include <math.h>

enum Dimension {X, Y, Z};

class Vertex3f;
class Vertex2i;

class Vertex2f {
 public:
  Vertex2f(Vertex3f vertex, Dimension toIgnore);

  Vertex2i pixelize(size2 screenSize) const;

  friend bool operator<(const Vertex2f &lhs, const Vertex2f &rhs);
  friend bool operator>(const Vertex2f &lhs, const Vertex2f &rhs);
  friend bool operator<=(const Vertex2f &lhs, const Vertex2f &rhs);
  friend bool operator>=(const Vertex2f &lhs, const Vertex2f &rhs);
  float x, y;
};

class Vertex3f {
 public:
  Vertex3f(float x, float y, float z);
 public:
  float x, y, z;

  Vertex2f flatten(Dimension d) const;
};

class Vertex2i {
 public:
  Vertex2i(int x, int y);
  int x, y;
};

bool operator<(const Vertex2f &lhs, const Vertex2f &rhs);
bool operator>(const Vertex2f &lhs, const Vertex2f &rhs);
bool operator<=(const Vertex2f &lhs, const Vertex2f &rhs);
bool operator>=(const Vertex2f &lhs, const Vertex2f &rhs);

#endif //HW2_VERTEX2F_H
