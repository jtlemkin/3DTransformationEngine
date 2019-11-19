//
// Created by James Lemkin on 11/16/19.
//

#ifndef HW2_LIGHTSOURCE_H
#define HW2_LIGHTSOURCE_H

#include "../Math/Vector3f.h"
#include "RGB.h"

class LightSource {
 public:
  float intensity;
  float k;

  Vector3f loc;
  RGB color;

  LightSource(float lightSourceIntensity, float k, const Vector3f &loc, const RGB &lightColor);
};

#endif //HW2_LIGHTSOURCE_H
