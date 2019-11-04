//
// Created by James Lemkin on 11/2/19.
//

#include <cmath>
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

Matrix4x4 getTranslationMatrix(vector3 v) {
  Matrix4x4 m;

  m.at(0,0) = 1;
  m.at(1,1) = 1;
  m.at(2,2) = 1;
  m.at(3,3) = 1;
  m.at(3,0) = v.x;
  m.at(3,1) = v.y;
  m.at(3,2) = v.z;

  return m;
}

Matrix4x4 getRotationIntoXZPlaneMatrix(float b, float c, float d) {
  Matrix4x4 m;

  m.at(0,0) = 1;
  m.at(1,1) = c / d;
  m.at(2,1) = -b / d;
  m.at(1,2) = b / d;
  m.at(2,2) = c / d;
  m.at(3,3) = 1;

  return m;
}

Matrix4x4 getRotationIntoZAxisMatrix(float a, float d) {
  Matrix4x4 m;

  m.at(0,0) = d;
  m.at(0,2) = -a;
  m.at(1,1) = 1;
  m.at(2,0) = a;
  m.at(2,2) = d;
  m.at(3,3) = 1;

  return m;
}

Matrix4x4 getRotationAroundZAxisMatrix(float alpha) {
  Matrix4x4 m;

  m.at(0,0) = cos(alpha);
  m.at(0,1) = sin(alpha);
  m.at(1,0) = -sin(alpha);
  m.at(1,1) = cos(alpha);
  m.at(2,2) = 1;
  m.at(3,3) = 1;

  return m;
}

void Vertex3f::translate(vector3 v) {
  Matrix4x4 m = getTranslationMatrix(v);

  ColVector pp = m.mult(ColVector(*this));

  this->x = pp.at(0);
  this->y = pp.at(1);
  this->z = pp.at(2);
}

void Vertex3f::rotate_around_axis(float alpha, vector3 p1, vector3 p2) {
  float a, b, c, d;
  float lenX, lenY, lenZ, lenV;

  lenX = p2.x - p1.x;
  lenY = p2.y - p1.y;
  lenZ = p2.z - p1.z;

  lenV = sqrt(pow(lenX, 2) + pow(lenY, 2) + pow(lenZ, 2));

  a = lenX / lenV;
  b = lenY / lenV;
  c = lenZ / lenV;
  d = sqrt(pow(b, 2) + pow(c, 2));

  Matrix4x4 m = getTranslationMatrix(makeVector3(p1.x, p1.y, p1.z));

  //m.display();

  if (lenY != 0) {
    Matrix4x4 rotIntoXZ = getRotationIntoXZPlaneMatrix(b, c, d);

    rotIntoXZ.display();

    m = m.mult(rotIntoXZ.transpose());

    //m.display();
  }

  Matrix4x4 rotIntoZ = getRotationIntoZAxisMatrix(a, d);

  rotIntoZ.display();

  m = m.mult(rotIntoZ.transpose());

  //m.display();

  Matrix4x4 rotAroundZ = getRotationAroundZAxisMatrix(alpha * M_PI / 180);

  rotAroundZ.display();

  m = m.mult(rotAroundZ);

  //m.display();

  m = m.mult(rotIntoZ);

  //m.display();

  if (lenY != 0) {
    Matrix4x4 rotIntoXZ = getRotationIntoXZPlaneMatrix(b, c, d);

    rotIntoXZ.display();

    m = m.mult(rotIntoXZ);

    //m.display();
  }

  Matrix4x4 translateBack = getTranslationMatrix(makeVector3(-p1.x, -p1.y, -p1.z));

  translateBack.display();

  m = m.mult(translateBack);

  //m.display();

  ColVector pp = m.mult(ColVector(*this));

  this->x = pp.at(0);
  this->y = pp.at(1);
  this->z = pp.at(2);
}

Matrix4x4 getScaleMatrix(float factor) {
  Matrix4x4 m;

  for(int i = 0; i < 3; i++) {
    m.at(i, i) = factor;
  }

  m.at(3, 3) = 1;

  return m;
}

void Vertex3f::scale(float factor, vector3 centroid) {
  ColVector pp = getTranslationMatrix(negative(centroid)).mult(ColVector(*this));
  pp = getScaleMatrix(factor).mult(pp);
  pp = getTranslationMatrix(centroid).mult(pp);

  this->x = pp.at(0);
  this->y = pp.at(1);
  this->z = pp.at(2);
}

Vertex2i Vertex2f::pixelize(size2 screenSize) const {
  auto newX = (int) round((screenSize.width - 1) * x);
  auto newY = (int) round((screenSize.height - 1) * y);

  return Vertex2i(newX, newY);
}
Vertex2f::Vertex2f(float x, float y) : x(x), y(y) {}
Vertex2i::Vertex2i(int x, int y) : x(x), y(y) {}
