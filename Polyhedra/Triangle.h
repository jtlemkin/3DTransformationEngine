//
// Created by James Lemkin on 11/17/19.
//

#ifndef HW2_TRIANGLE_H
#define HW2_TRIANGLE_H

#include "Polyhedron.h"

class Triangle {
 public:
  // These indices are important so that we can access the corresponding vertices in transformed vectors with
  // transformed vertices
  int id;
  int v1ID, v2ID, v3ID;
  float specularity;

  Triangle(int id, int v1ID, int v2ID, int v3ID, float specularity);
};

#endif //HW2_TRIANGLE_H
