//
// Created by James Lemkin on 11/17/19.
//

#include "Vector2i.h"
Vector2i::Vector2i(int x, int y) : x(x), y(y) {}

Vector2f Vector2i::toNDC(int screenWidth, int screenHeight) {
  float xf = x;
  float yf = y;

  return Vector2f((xf / screenWidth - 0.5f) * 2, (yf / screenHeight - 0.5f) * 2);
}

