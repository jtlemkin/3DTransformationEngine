//
// Created by James Lemkin on 10/27/19.
//

#include "glDrawing.h"

//Draws a single "pixel" given the current grid size
//don't change anything in this for project 1
void draw_pix(vector2 loc, rgb color){
  glBegin(GL_POINTS);
  glColor3f(color.r, color.g, color.b);
  glVertex3f(loc.x + 0.5, loc.y + 0.5, 0);
  glEnd();
}

void drawLine(Vertex p1, Vertex p2, rgb color) {
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINES);
  glVertex2f(p1.x(), p1.y());
  glVertex2f(p2.x(), p2.y());
  glEnd();
}