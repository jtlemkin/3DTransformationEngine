//
// Created by James Lemkin on 10/27/19.
//

#pragma once

#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//other includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "../Math/Dimension.h"

void draw_pix(int x, int y, int z, float r, float g, float b, Dimension toIgnore);
void draw_pix(float x, float y, float r, float g, float b);
//void drawLine(Vertex p1, Vertex p2, rgb color);
//void drawFace(Vertex p1, Vertex p2, Vertex p3, rgb color, Dimension toIgnore);

//Set the gl viewport to a quarter of the screen
void setViewport(int width, int height, Dimension toIgnore);

//Resets gl viewport to default
void resetViewport(int width, int height);
