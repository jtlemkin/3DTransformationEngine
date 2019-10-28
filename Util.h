//
// Created by James Lemkin on 10/27/19.
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

struct pixel {
  float r, g, b;
};

pixel makePixel(float r, float g, float b);

struct vector2 {
  int x, y;
};

vector2 makeVector2(int x, int y);

struct size2 {
  int height, width;
};

size2 makeSize2(int height, int width);

struct bounds {
  int min, max;
};

bounds makeBounds(int min, int max);

//taken from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> split(const std::string& s, char delimiter);

bool equals(pixel color1, pixel color2);
bool equals(vector2 v1, vector2 v2);

static bool operator<(const vector2& l, const vector2& r) {
  return (l.x < r.x || (l.x == r.x && l.y < r.y));
}

static bool operator<(const pixel& l, const pixel& r) {
  return (l.r < r.r || (l.r == r.r && l.g < r.g) || (l.r == r.r && l.g == r.g && l.b < r.b));
}

vector2 negative(vector2 v);
