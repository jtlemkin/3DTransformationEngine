//
// Created by James Lemkin on 10/27/19.
//

#include "DrawPix.h"

//Draws a single "pixel" given the current grid size
//don't change anything in this for project 1
void draw_pix(vector2 loc, pixel color){
  glBegin(GL_POINTS);
  glColor3f(color.r, color.g, color.b);
  glVertex3f(loc.x + 0.5, loc.y + 0.5, 0);
  glEnd();
}