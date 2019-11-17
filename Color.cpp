//
// Created by James Lemkin on 11/16/19.
//

#include "Color.h"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {

}
Color Color::mult(float n) const {
  return Color((int) ((float) r * n), (int) ((float) g * n), (int) ((float) b * n));
}
Color Color::add(Color c2) const {
  return Color(r + c2.r, b + c2.b, g + c2.g);
}
