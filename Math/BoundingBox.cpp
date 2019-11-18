//
// Created by James Lemkin on 11/2/19.
//

#include "BoundingBox.h"

BoundingBox::BoundingBox() {
  xMin = std::numeric_limits<float>::max();
  xMax = std::numeric_limits<float>::min();

  yMin = std::numeric_limits<float>::max();
  yMax = std::numeric_limits<float>::min();

  zMin = std::numeric_limits<float>::max();
  zMax = std::numeric_limits<float>::min();

  computeMargins();
}

void BoundingBox::addPoint(Vector3f p) {
  xMin = p.x < xMin ? p.x : xMin;
  yMin = p.y < yMin ? p.y : yMin;
  zMin = p.z < zMin ? p.z: zMin;

  xMax = p.x > xMax ? p.x : xMax;
  yMax = p.y > yMax ? p.y : yMax;
  zMax = p.z > zMax ? p.z : zMax;

  computeMargins();
}

void BoundingBox::computeMargins() {
  min = std::min(zMin, std::min(xMin, yMin));
  max = std::max(zMax, std::max(xMax, yMax));

  auto range = max - min;

  float marginSize = 0.1;

  min -= marginSize * range;
  max += marginSize * range;
}
