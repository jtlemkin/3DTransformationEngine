//
// Created by James Lemkin on 11/17/19.
//

#include "RGB.h"

RGB::RGB(float r, float g, float b) : r(r), g(g), b(b) {

}
RGB RGB::mult(float n) {
  return RGB(n * r, n * g, n * b);
}
RGB RGB::add(RGB rgb2) {
  return RGB(r + rgb2.r, g + rgb2.g, b + rgb2.b);
}
