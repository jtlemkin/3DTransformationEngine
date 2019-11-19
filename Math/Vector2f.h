//
// Created by James Lemkin on 11/17/19.
//

#ifndef HW2_VECTOR2F_H
#define HW2_VECTOR2F_H

#include "Vector2i.h"

class Vector2i;

class Vector2f {
 public:
  float x, y;

  Vector2f(float x, float y);

  Vector2i getNDC(int width, int height);
};

#endif //HW2_VECTOR2F_H
