//
// Created by James Lemkin on 11/16/19.
//

#include "LightSource.h"
LightSource::LightSource(float lightSourceIntensity, float k, const Vector3f &loc, const Color &lightColor)
    : intensity(lightSourceIntensity), k(k), loc(loc), color(lightColor) {}
