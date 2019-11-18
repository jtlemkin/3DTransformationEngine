//
// Created by James Lemkin on 11/16/19.
//

#ifndef HW2_LIGHTSOURCE_H
#define HW2_LIGHTSOURCE_H

#include "../Math/Vector3f.h"
#include "Color.h"

class LightSource {
 public:
  float intensity;
  float k;

  Vector3f loc;
  Color color;

  LightSource(float lightSourceIntensity, float k, const Vector3f &loc, const Color &lightColor);
};

#endif //HW2_LIGHTSOURCE_H
