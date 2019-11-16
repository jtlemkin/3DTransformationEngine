//
// Created by James Lemkin on 11/2/19.
//

#include <cmath>
#include "Vertex.h"

Vertex::Vertex(float x, float y, float z, rgb color) : color(color) {
  pos[0] = x;
  pos[1] = y;
  pos[2] = z;
  pos[3] = 1;

  faces = std::vector<Face>({});
}

//Flattens a vertex3f to make a vertex2f
void Vertex::flatten(Dimension d) {
  pos[d] = 0;
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
void Vertex::translate(vector3 v) {
  Matrix4x4 m = getTranslationMatrix(v);

  m.display();

  *this = m.mult(*this);
}

//Rotates a vertex around an arbitrary axis through 7 matrix multiplications
void Vertex::rotate_around_axis(float alpha, vector3 p1, vector3 p2) {
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

  *this = m.mult(*this);
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
void Vertex::scale(float factor, vector3 centroid) {
  *this = getTranslationMatrix(negative(centroid)).mult(*this);
  *this = getScaleMatrix(factor).mult(*this);
  *this = getTranslationMatrix(centroid).mult(*this);
}
float Vertex::x() const {
  return pos[0];
}
float Vertex::y() const {
  return pos[1];
}
float Vertex::z() const {
  return pos[2];
}
void Vertex::addFace(Face& face) {
  faces.push_back(face);
}
