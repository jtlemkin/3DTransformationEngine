//
// Created by James Lemkin on 10/31/19.
//

#ifndef HW2_POLYGON_H
#define HW2_POLYGON_H

#include "Vertex.h"
#include "BoundingBox.h"
#include "Structs/DrawPix.h"

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

class Polyhedron {
 public:

  int numVertices;
  std::vector<Vertex> vertices;
  int numEdges;
  std::vector<vector2> edges;

  Polyhedron(int numVertices, std::vector<Vertex> vertices, int numEdges, std::vector<vector2> edges);

  void render(BoundingBox boundingBox, size2 screensize, Dimension toIgnore) const;

  void translate(float x, float y, float z);
  void rotate(float angle, vector3 p1, vector3 p2);
  void scale(float factor);

  vector3 getCentroid();
};

#endif //HW2_POLYGON_H
