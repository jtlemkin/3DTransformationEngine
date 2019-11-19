//
// Created by James Lemkin on 11/17/19.
//

#include <iostream>
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

void getIntensityRange(int y, Vector2i p1, Vector2i p2, Vector2i p3, RGB c1, RGB c2, RGB c3, RGB* cMin,
                       RGB* cMax) {
  int i1 = computeIntersection(y, p1, p2);
  int i2 = computeIntersection(y, p2, p3);
  int i3 = computeIntersection(y, p3, p1);


}

RGB computeGouraudRange(RGB *cMin, RGB *cMax, RGB c1, RGB c2, Vector2i p1, Vector2i p2) {
  if (cMin->r == -1) {
    *cMin = c1;
    *cMax = c2;
  } else {
    cMin->r += (c2.r - c1.r) / (p1.y - p2.y);
    cMin->g += (c2.g - c1.g) / (p1.y - p2.y);
    cMin->b += (c2.b - c1.b) / (p1.y - p2.y);
  }
}

RGB computeHorizontalGouraudRange(RGB *cMin, RGB *cMax, RGB c1, RGB c2, Vector2i p1, Vector2i p2) {
  if (p1.x < p2.x) {
    *cMin = c1;
    *cMax = c2;
  } else {
    *cMin = c2;
    *cMax = c1;
  }
}

void computeIntersectionLocationsAndColors(int y, Vector2i p1, Vector2i p2, Vector2i p3, RGB c1, RGB c2, RGB c3,
                                           int *xMin, int *xMax, RGB *cMin, RGB *cMax) {

  int i1 = computeIntersection(y, p1, p2);
  int i2 = computeIntersection(y, p2, p3);
  int i3 = computeIntersection(y, p3, p1);

  //No special cases
  if (i1 >= 0 && i2 >= 0 && i3 >= 0) {
    if (i1 <= i2 && i1 <= i3) {
      computeGouraudRange(cMin, cMax, c1, c2, p1, p2);
    } else if (i2 <= i1 && i2 <= i3) {
      computeGouraudRange(cMin, cMax, c2, c3, p2, p3);
    } else if (i3 <= i1 && i3 <= i2){
      computeGouraudRange(cMin, cMax, c3, c1, p3, p1);
    } else {
      std::cout << "Critical error with gouraud color\n";
    }

    *xMin = std::min(std::min(i1, i2), i3);
    *xMax = std::max(std::max(i1, i2), i3);

    return;
  }

  //If the scan line intersects a horizontal line
  if (i1 == -2 && p1.y == y) {
    *xMin = std::min(p1.x, p2.x);
    *xMax = std::max(p1.x, p2.x);

    computeHorizontalGouraudRange(cMin, cMax, c1, c2, p1, p2);

    return;
  } else if (i2 == -2 && p1.y == y) {
    *xMin = std::min(p3.x, p2.x);
    *xMax = std::max(p3.x, p2.x);

    computeHorizontalGouraudRange(cMin, cMax, c2, c3, p2, p3);

    return;
  } else if (i3 == -3 && p3.y == y) {
    *xMin = std::min(p3.x, p1.x);
    *xMax = std::max(p3.x, p1.x);

    computeHorizontalGouraudRange(cMin, cMax, c3, c1, p3, p1);

    return;
  }

  //Intersects at a point
  if (i1 < 0 && i2 < 0) {
    *xMin = i3;
    *xMax = i3;

    *cMin = c1;
    *cMax = c1;

    return;
  } else if (i1 < 0 && i3 < 0) {
    *xMin = i2;
    *xMax = i2;

    *cMin = c2;
    *cMax = c2;

    return;
  } else if (i2 < 0 && i3 < 0) {
    *xMin = i1;
    *xMax = i1;

    *cMin = c3;
    *cMax = c3;

    return;
  }

  //Horizontal non intersecting line or no intersection
  if (i1 < 0) {
    *xMin = std::min(i3, i2);
    *xMax = std::max(i3, i2);

    computeGouraudRange(cMin, cMax, c2, c3, p2, p3);

    return;
  } else if (i2 < 0) {
    *xMin = std::min(i3, i1);
    *xMax = std::max(i3, i1);

    computeGouraudRange(cMin, cMax, c1, c3, p1, p3);

    return;
  } else if (i3 < 0) {
    *xMin = std::min(i1, i2);
    *xMax = std::max(i1, i2);

    computeGouraudRange(cMin, cMax, c1, c2, p1, p2);

    return;
  }
}

//Normalizes a float to a value between 0 and 1
float normalize(float val, float min, float max) {
  if (max == min) {
    return 0;
  }

  return (val - min) / (max - min) * 2 - 1;
}