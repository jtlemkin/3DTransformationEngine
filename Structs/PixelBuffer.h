//
// Created by James Lemkin on 10/27/19.
//

#pragma once

#include <stdio.h>
#include "Util.h"
#include "DrawPix.h"

struct pixelBuffer {
  size2 grid_size;
  int pix_size;
  pixel* buffer;
};

void fillBuffer(pixelBuffer& pb, pixel color);

pixelBuffer makePixelBuffer(size2 gridSize, int pix_size);

void recordPixel(vector2 loc, pixel color, pixelBuffer& pb);

pixel getPixelAt(vector2 loc, pixelBuffer& pb);

void displayBuffer(pixelBuffer& pb);
