//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VERTEX2F_H
#define HW2_VERTEX2F_H

#include "Structs/Util.h"
#include "Math/Matrix4x4.h"
#include "Polyhedron.h"
#include "Math/Dimension.h"
#include "Math/Vector3f.h"
#include "Color.h"
#include <math.h>

class Face;

class Vertex {
 public:
  float pos[4];

  Color diffuseColor;

  float x() const;
  float y() const;
  float z() const;

  rgb color;

  explicit Vertex(float x=0, float y=0, float z=0, Color diffuseColor = Color(0,0,0));

  void flatten(Dimension d);

  //TODO fix broken transformation functions
  void translate(vector3 v);
  void rotate_around_axis(float alpha, vector3 p1, vector3 p2);
  void scale(float factor, vector3 centroid);

  void addFace(Face& face);

  Vector3f getNormal();
  int getSpecularity();

 private:
  std::vector<Face> faces;
};

#endif //HW2_VERTEX2F_H
