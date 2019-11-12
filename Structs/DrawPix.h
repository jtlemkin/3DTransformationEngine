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
#include <stdio.h>
#include <stdlib.h>
#include "Util.h"
#include "../Vertex.h"

void draw_pix(vector2 loc, pixel color);
void drawLine(Vertex p1, Vertex p2, pixel color);
