//
// Created by James Lemkin on 10/27/19.
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

class Vertex;

struct rgb {
  float r, g, b;
};

rgb makeRGB(float r, float g, float b);

struct vector2 {
  int x, y;
};

vector2 makeVector2(int x, int y);

struct vector3 {
  float x, y, z;
};

vector3 makeVector3(float x, float y, float z);

struct size2 {
  int height, width;
};

size2 makeSize2(int height, int width);

//taken from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> split(const std::string& s, char delimiter);

static bool operator<(const vector2& l, const vector2& r) {
  return (l.x < r.x || (l.x == r.x && l.y < r.y));
}

static bool operator<(const rgb& l, const rgb& r) {
  return (l.r < r.r || (l.r == r.r && l.g < r.g) || (l.r == r.r && l.g == r.g && l.b < r.b));
}

vector3 negative(vector3 v);