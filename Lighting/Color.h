//
// Created by James Lemkin on 11/16/19.
//

#ifndef HW2_COLOR_H
#define HW2_COLOR_H

class Color {
 public:
  int r, g, b;

  Color(int r, int g, int b);

  Color mult(float n) const;
  Color add(Color c2) const;
};

#endif //HW2_COLOR_H
