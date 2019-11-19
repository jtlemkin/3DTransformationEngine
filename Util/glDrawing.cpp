//
// Created by James Lemkin on 10/27/19.
//

#include "glDrawing.h"

//Draws a single "pixel" given the current grid size
//don't change anything in this for project 1
/*void draw_pix(int x, int y, int z, float r, float g, float b, Dimension toIgnore){
  glBegin(GL_POINTS);
  glColor3f(r, g, b);

  switch (toIgnore) {
    case Z:
      glVertex3f(x + 0.5, y + 0.5, 0);
    case Y:
      glVertex3f(x + 0.5, z + 0.5, 0);
    case X:
      glVertex3f(y + 0.5, z + 0.5, 0);
  }

  glEnd();
}*/

void draw_pix(float x, float y, float r, float g, float b){
  glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex3f(x, y, 0);
  glEnd();
}

//Set the gl viewport to a quarter of the screen
void setViewport(int width, int height, Dimension toIgnore) {
  switch(toIgnore) {
    case X:
      glViewport(0, 0, width / 2, height / 2);
      break;
    case Y:
      glViewport(width / 2, width / 2, width / 2, height / 2);
      break;
    case Z:
      glViewport(0, width / 2, width / 2, height / 2);
  }
}

//Resets gl viewport to default
void resetViewport(int width, int height) {
  glViewport(0, 0, width, height);
}

/*void drawLine(Vertex p1, Vertex p2, rgb color) {
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINES);
  glVertex2f(p1.x(), p1.y());
  glVertex2f(p2.x(), p2.y());
  glEnd();
}

void drawFace(Vertex p1, Vertex p2, Vertex p3, rgb color) {
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINE_LOOP);
  glVertex2f(p1.x(), p1.y());
  glVertex2f(p2.x(), p2.y());
  glVertex2f(p3.x(), p3.y());
  glEnd();
}*/
