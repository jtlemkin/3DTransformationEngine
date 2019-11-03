//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_BOUNDINGBOX_H
#define HW2_BOUNDINGBOX_H

#include "Polyhedron.h"

class Polyhedron;

class BoundingBox {
 public:
  float min, max;

  explicit BoundingBox(std::vector<Polyhedron>& polyhedra);
 private:
  float xMin, xMax, yMin, yMax, zMin, zMax;
};

#endif //HW2_BOUNDINGBOX_H
