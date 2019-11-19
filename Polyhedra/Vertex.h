//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VERTEX2F_H
#define HW2_VERTEX2F_H

#include "../Math/Matrix4x4.h"
#include "Polyhedron.h"
#include "../Math/Dimension.h"
#include "../Math/Vector3f.h"
#include "../Lighting/Color.h"
#include "../Scene.h"
#include "../Lighting/LightSource.h"
#include "../Math/Vector2f.h"
#include <cmath>


class Triangle;

class Vertex {
 public:
  int id;

  float pos[4];

  Color diffuseColor;
  Color color;

  std::vector<int> triangleIDs;

  float x() const;
  float y() const;
  float z() const;

  explicit Vertex(int id, float x=0, float y=0, float z=0, Color diffuseColor = Color(0,0,0));

  Vector2f flatten(Dimension d);
  void addTriangle(int triangleID);

  //TODO fix broken transformation functions
  //void translate(vector3 v);
  //void rotate_around_axis(float alpha, vector3 p1, vector3 p2);
  //void scale(float factor, vector3 centroid);
};

#endif //HW2_VERTEX2F_H
