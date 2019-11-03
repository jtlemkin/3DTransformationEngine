//
// Created by James Lemkin on 10/31/19.
//

#ifndef HW2_POLYGON_H
#define HW2_POLYGON_H

#include <set>
#include <vector>
#include "Vertex2f.h"
#include "Structs/Util.h"
#include <limits>
#include "BoundingBox.h"

#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

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
  std::vector<Vertex3f> vertices;

  Polyhedron(int numVertices, std::vector<Vertex3f> vertices);

  void renderXY(BoundingBox boundingBox, size2 screensize) const;
  void renderXZ(BoundingBox boundingBox, size2 screensize) const;
  void renderYZ(BoundingBox boundingBox, size2 screensize) const;
};

#endif //HW2_POLYGON_H
