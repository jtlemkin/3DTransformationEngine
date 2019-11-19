//
// Created by James Lemkin on 11/17/19.
//

#include "Util.h"

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

int computeIntersection(int y, Vector2i p1, Vector2i p2) {
  //If p1 and p2 are the same point and the scan line intersects with the point, just return the point
  if (p1.x == p2.x && p1.y == p2.y && p1.y == y) {
    return p1.x;
  }

  int start, end;

  if (p1.x < p2.x) {
    start = p1.x;
    end = p2.x;
  } else {
    start = p2.x;
    end = p1.x;
  }

  float dx = p2.x - p1.x;
  float dy = p2.y - p1.y;

  //If the line is horizontal and the scan line intersects with it
  if ((int) dy == 0) {
    //Implies that the edge is a straight line
    return -2;
  }

  float x = dx * (float) (y - p1.y) / dy + (float) p1.x;

  if (x >= start && x <= end) {
    return (int) x;
  } else {
    //Implies that there's no intersection with the line
    return -1;
  }
}

void getXRange(int y, Vector2i p1, Vector2i p2, Vector2i p3, int* xMin, int* xMax) {
  int i1 = computeIntersection(y, p1, p2);
  int i2 = computeIntersection(y, p2, p3);
  int i3 = computeIntersection(y, p3, p1);

  //No special cases
  if (i1 >= 0 && i2 >= 0 && i3 >= 0) {
    *xMin = std::min(std::min(i1, i2), i3);
    *xMax = std::max(std::max(i1, i2), i3);

    return;
  }

  //If the scan line intersects a horizontal line
  if (i1 == -2 && p1.y == y) {
    *xMin = std::min(p1.x, p2.x);
    *xMax = std::max(p1.x, p2.x);

    return;
  } else if (i2 == -2 && p1.y == y) {
    *xMin = std::min(p3.x, p2.x);
    *xMax = std::max(p3.x, p2.x);

    return;
  } else if (i3 == -3 && p3.y == y) {
    *xMin = std::min(p3.x, p1.x);
    *xMax = std::max(p3.x, p1.x);

    return;
  }

  //Intersects at a point
  if (i1 < 0 && i2 < 0) {
    *xMin = i3;
    *xMax = i3;

    return;
  } else if (i1 < 0 && i3 < 0) {
    *xMin = i2;
    *xMax = i2;

    return;
  } else if (i2 < 0 && i3 < 0) {
    *xMin = i1;
    *xMax = i1;

    return;
  }

  //Horizontal non intersecting line or no intersection
  if (i1 < 0) {
    *xMin = std::min(i3, i2);
    *xMax = std::max(i3, i2);

    return;
  } else if (i2 < 0) {
    *xMin = std::min(i3, i1);
    *xMax = std::max(i3, i1);

    return;
  } else if (i3 < 0) {
    *xMin = std::min(i1, i2);
    *xMax = std::max(i1, i2);

    return;
  }
}