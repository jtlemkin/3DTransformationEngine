//
// Created by James Lemkin on 10/27/19.
//

#include "Util.h"

pixel makePixel(float r, float g, float b) {
  pixel pix;
  pix.r = r;
  pix.g = g;
  pix.b = b;

  return pix;
}

vector2 makeVector2(int x, int y) {
  vector2 v2;
  v2.x = x;
  v2.y = y;

  return v2;
}

size2 makeSize2(int height, int width) {
  size2 s2;
  s2.height = height;
  s2.width = width;

  return s2;
}

bounds makeBounds(float min, float max) {
  bounds b;
  b.min = min;
  b.max = max;

  return b;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

bool equals(pixel color1, pixel color2) {
  return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b;
}

bool equals(vector2 v1, vector2 v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

vector2 negative(vector2 v) {
  v.x = -v.x;
  v.y = -v.y;

  return v;
}