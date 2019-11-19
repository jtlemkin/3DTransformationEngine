//
// Created by James Lemkin on 11/17/19.
//

#ifndef HW2_RGB_H
#define HW2_RGB_H

class RGB {
 public:
  float r, g, b;

  RGB(float r, float g, float b);

  RGB mult(float n);
  RGB add(RGB rgb2);
};

#endif //HW2_RGB_H
