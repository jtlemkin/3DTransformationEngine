//
// Created by James Lemkin on 11/2/19.
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(std::vector<Polyhedron>& polyhedra) {
  xMin = std::numeric_limits<float>::max();
  xMax = std::numeric_limits<float>::min();

  yMin = std::numeric_limits<float>::max();
  yMax = std::numeric_limits<float>::min();

  zMin = std::numeric_limits<float>::max();
  zMax = std::numeric_limits<float>::min();

  for (const auto& polyhedron : polyhedra) {
    for (int i = 0; i < polyhedron.numVertices; i++) {
      xMin = polyhedron.vertices[i].x < xMin ? polyhedron.vertices[i].x: xMin;
      yMin = polyhedron.vertices[i].y < yMin ? polyhedron.vertices[i].y: yMin;
      zMin = polyhedron.vertices[i].z < zMin ? polyhedron.vertices[i].z: zMin;

      xMax = polyhedron.vertices[i].x > xMax ? polyhedron.vertices[i].x: xMax;
      yMax = polyhedron.vertices[i].y > yMax ? polyhedron.vertices[i].y: yMax;
      zMax = polyhedron.vertices[i].z > zMax ? polyhedron.vertices[i].z: zMax;
    }
  }

  min = std::min(zMin, std::min(xMin, yMin));
  max = std::max(zMax, std::max(xMax, yMax));

  auto range = max - min;

  float marginSize = 0.1;

  min -= marginSize * range;
  max += marginSize * range;
}