//
// Created by James Lemkin on 11/17/19.
//

#ifndef HW2_UTIL_H
#define HW2_UTIL_H

#include <string>
#include <sstream>
#include <vector>

#include "../Math/Vector2i.h"
#include "../Lighting/Color.h"

std::vector<std::string> split(const std::string& s, char delimiter);
int computeIntersection(int y, Vector2i p1, Vector2i p2);
void computeIntersectionLocationsAndColors(int y, Vector2i p1, Vector2i p2, Vector2i p3, Color c1, Color c2, Color c3,
                                           int *xMin, int *xMax, Color *cMin, Color *cMax);
float normalize(float val, float min, float max);

#endif //HW2_UTIL_H
