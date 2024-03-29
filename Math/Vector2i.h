//
// Created by James Lemkin on 11/17/19.
//

#ifndef HW2_VECTOR2I_H
#define HW2_VECTOR2I_H

#include "Vector2f.h"

class Vector2f;

class Vector2i {
 public:
  Vector2i(int x, int y);

  int x, y;

  Vector2f toNDC(int screenWidth, int screenHeight);
};

#endif //HW2_VECTOR2I_H
