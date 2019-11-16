//
// Created by James Lemkin on 10/31/19.
//

#ifndef HW2_POLYGON_H
#define HW2_POLYGON_H

#include "Vertex.h"
#include "BoundingBox.h"
#include "Structs/glDrawing.h"
#include "Dimension.h"
#include "Vector3f.h"

/*
   * Testing
   *
   * Every vertex is end point for at least two edges
   *
   * Every edge is part of at least one triangle
   *
   * Every polygon is closed
   *
   * Each polygon has at least one shared edge
   *
   * If edge table contains pointers to polygons, every edge linked by polygon has reciprocal link back to the polygon
   */

class BoundingBox;

class Vertex;

class Face {
 private:
  std::vector<Vertex>& vertices;

 public:
  int p1;
  int p2;
  int p3;

  Face(int p1, int p2, int p3, float specularity, std::vector<Vertex>& vertices);

  Vertex getP1() const;
  Vertex getP2() const;
  Vertex getP3() const;

  float specularity;

  Vector3f getNormal() const;
};

class Polyhedron {
 public:

  std::vector<Vertex> vertices;
  std::vector<Face> faces;

  Polyhedron(std::vector<Vertex> vertices, std::vector<Face> faces);

  void render(BoundingBox boundingBox, size2 screensize, Dimension toIgnore) const;

  void translate(float x, float y, float z);
  void rotate(float angle, vector3 p1, vector3 p2);
  void scale(float factor);

  vector3 getCentroid();
};

#endif //HW2_POLYGON_H
