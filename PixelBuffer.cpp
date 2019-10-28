//
// Created by James Lemkin on 10/27/19.
//

#include "PixelBuffer.h"

pixelBuffer makePixelBuffer(size2 gridSize, int pix_size) {
  pixelBuffer pb;
  pb.grid_size = gridSize;
  pb.pix_size = pix_size;

  pb.buffer = new pixel[gridSize.width * gridSize.height];

  fillBuffer(pb, makePixel(1, 1, 0));

  return pb;
}

int getNumPixels(const pixelBuffer& pb) {
  return pb.grid_size.width * pb.grid_size.height;
}

void fillBuffer(pixelBuffer& pb, pixel color) {
  for(int i = 0; i < getNumPixels(pb); i++) {
    pb.buffer[i] = color;
  }
}

void recordPixel(vector2 loc, pixel color, pixelBuffer& pb) {
  if (loc.x >= 0 && loc.x < pb.grid_size.width && loc.y >= 0 && loc.y < pb.grid_size.height) {
    pb.buffer[loc.x + loc.y * pb.grid_size.width] = color;
  }
}

void displayBuffer(pixelBuffer& pb) {
  for(int i = 0; i < getNumPixels(pb); i++) {
    vector2 loc;
    loc.x = i % pb.grid_size.width;
    loc.y = i / pb.grid_size.width;

    draw_pix(loc, pb.buffer[i]);
  }
}

pixel getPixelAt(vector2 loc, pixelBuffer& pb) {
  return pb.buffer[loc.x + loc.y * pb.grid_size.width];
}