//
// Created by James Lemkin on 11/17/19.
//

#include "Vector2f.h"
Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

Vector2i Vector2f::getNDC(int width, int height) {
  return Vector2i((int) (x * width), (int) (y * height));
}
