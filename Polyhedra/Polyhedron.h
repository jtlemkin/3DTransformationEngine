//
// Created by James Lemkin on 10/31/19.
//

#ifndef HW2_POLYGON_H
#define HW2_POLYGON_H

#include <vector>
#include "Vertex.h"
#include "../Util/glDrawing.h"
#include "../Math/Dimension.h"
#include "../Scene.h"
#include "../Math/BoundingBox.h"
#include "Triangle.h"

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

class Vertex;

class Scene;

class Polyhedron {
 public:

  std::vector<Vertex> vertices;
  std::vector<Triangle> triangles;

  Polyhedron();

  void render(Scene& scene, BoundingBox& boundingBox, Dimension toIgnore) const;
  void renderTriangle(int triangleID, Scene& scene, Dimension toIgnore) const;

  Vector3f getVertexNormal(int vertexID);
  Vector3f getFaceNormal(int triangleID);
  int getVertexSpecularity(int vertexID);
  RGB getVertexColor(int vertexID, Vector3f& eyeLoc, LightSource light, RGB ambientColor);

  //void translate(float x, float y, float z);
  //void rotate(float angle, vector3 p1, vector3 p2);
  //void scale(float factor);

  //vector3 getCentroid();
 private:
  std::vector<Triangle> insertionSort(Dimension toSort) const;
  float getTriangleMin(int triangleID, Dimension toSort) const;
};

#endif //HW2_POLYGON_H
