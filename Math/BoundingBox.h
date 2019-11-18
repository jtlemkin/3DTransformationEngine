//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_BOUNDINGBOX_H
#define HW2_BOUNDINGBOX_H

#include "Vector3f.h"
#include <limits>
#include <algorithm>

class BoundingBox {
 public:
  float min, max;

  BoundingBox();

  void addPoint(Vector3f p);

 private:
  float xMin, xMax, yMin, yMax, zMin, zMax;

  void computeMargins();
};

#endif //HW2_BOUNDINGBOX_H
