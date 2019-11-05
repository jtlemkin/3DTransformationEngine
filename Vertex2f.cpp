//
// Created by James Lemkin on 11/2/19.
//

#include <cmath>
#include "Vertex2f.h"

//Flattens a vertex3f to make a vertex2f
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

//Constructor
Vertex3f::Vertex3f(float x, float y, float z) : x(x), y(y), z(z) {}

//Removes a dimension from vertex
Vertex2f Vertex3f::flatten(Dimension d) const {
  return Vertex2f(*this, d);
}

//Creates a translation matrix
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

//Creates a matrix to rotate a vector into the XZ plane
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

//Creates a matrix to rotate a vector from the XZ plane to the Z axis
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

//Creates a matrix to rotate a point around the Z axis
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

//Translates a vertex
void Vertex3f::translate(vector3 v) {
  Matrix4x4 m = getTranslationMatrix(v);

  ColVector pp = m.mult(ColVector(*this));

  this->x = pp.at(0);
  this->y = pp.at(1);
  this->z = pp.at(2);
}

//Rotates a vertex around an arbitrary axis through 7 matrix multiplications
void Vertex3f::rotate_around_axis(float alpha, vector3 p1, vector3 p2) {
  float a, b, c, d;
  float lenX, lenY, lenZ, lenV;

  //Calculates x, y, and z components of axis vector
  lenX = p2.x - p1.x;
  lenY = p2.y - p1.y;
  lenZ = p2.z - p1.z;

  //Calculates length of the axis vector
  lenV = sqrt(pow(lenX, 2) + pow(lenY, 2) + pow(lenZ, 2));

  //Calculates normalized x, y, z components of axis vector
  a = lenX / lenV;
  b = lenY / lenV;
  c = lenZ / lenV;

  //This is the length of the axis vector projected onto the yz plane
  d = sqrt(pow(b, 2) + pow(c, 2));

  Matrix4x4 m = getTranslationMatrix(makeVector3(p1.x, p1.y, p1.z));

  //m.display();

  if (lenY != 0) {
    Matrix4x4 rotIntoXZ = getRotationIntoXZPlaneMatrix(b, c, d);

    //rotIntoXZ.display();

    m = m.mult(rotIntoXZ.transpose());

    //m.display();
  }

  Matrix4x4 rotIntoZ = getRotationIntoZAxisMatrix(a, d);

  //rotIntoZ.display();

  m = m.mult(rotIntoZ.transpose());

  //m.display();

  Matrix4x4 rotAroundZ = getRotationAroundZAxisMatrix(alpha * M_PI / 180);

  //rotAroundZ.display();

  m = m.mult(rotAroundZ);

  //m.display();

  m = m.mult(rotIntoZ);

  //m.display();

  if (lenY != 0) {
    Matrix4x4 rotIntoXZ = getRotationIntoXZPlaneMatrix(b, c, d);

    //rotIntoXZ.display();

    m = m.mult(rotIntoXZ);

    //m.display();
  }

  Matrix4x4 translateBack = getTranslationMatrix(makeVector3(-p1.x, -p1.y, -p1.z));

  //translateBack.display();

  m = m.mult(translateBack);

  //m.display();

  ColVector pp = m.mult(ColVector(*this));

  this->x = pp.at(0);
  this->y = pp.at(1);
  this->z = pp.at(2);
}

//Creates a matrix to scale a vector by a constant factor
Matrix4x4 getScaleMatrix(float factor) {
  Matrix4x4 m;

  for(int i = 0; i < 3; i++) {
    m.at(i, i) = factor;
  }

  m.at(3, 3) = 1;

  return m;
}

//Scales the vertex of a polygon with respect to its centroid
void Vertex3f::scale(float factor, vector3 centroid) {
  ColVector pp = getTranslationMatrix(negative(centroid)).mult(ColVector(*this));
  pp = getScaleMatrix(factor).mult(pp);
  pp = getTranslationMatrix(centroid).mult(pp);

  this->x = pp.at(0);
  this->y = pp.at(1);
  this->z = pp.at(2);
}

//Constructors
Vertex2f::Vertex2f(float x, float y) : x(x), y(y) {}
Vertex2i::Vertex2i(int x, int y) : x(x), y(y) {}
