//
// Created by James Lemkin on 11/2/19.
//

#include "Vertex2f.h"

Vertex2f::Vertex2f(Vertex3f vertex, Dimension toIgnore) {
  switch (toIgnore) {
    case Z:
      x = vertex.x;
      y = vertex.y;
      break;
    case Y:
      x = vertex.x;
      y = vertex.z;
      break;
    case X:
      x = vertex.y;
      y = vertex.z;
      break;
  }
}
bool operator<(const Vertex2f &lhs, const Vertex2f &rhs) {
  if (lhs.x < rhs.x)
    return true;
  if (rhs.x < lhs.x)
    return false;
  return lhs.y < rhs.y;
}
bool operator>(const Vertex2f &lhs, const Vertex2f &rhs) {
  return rhs < lhs;
}
bool operator<=(const Vertex2f &lhs, const Vertex2f &rhs) {
  return !(rhs < lhs);
}
bool operator>=(const Vertex2f &lhs, const Vertex2f &rhs) {
  return !(lhs < rhs);
}
Vertex3f::Vertex3f(float x, float y, float z) : x(x), y(y), z(z) {}

Vertex2f Vertex3f::flatten(Dimension d) const {
  return Vertex2f(*this, d);
}

Vertex2i Vertex2f::pixelize(size2 screenSize) const {
  int newX = (int) round((screenSize.width - 1) * x);
  int newY = (int) round((screenSize.height - 1) * y);

  return Vertex2i(newX, newY);
}
Vertex2i::Vertex2i(int x, int y) : x(x), y(y) {}
