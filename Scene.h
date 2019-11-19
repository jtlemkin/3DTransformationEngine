//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VIEWINGPIPELINE_H
#define HW2_VIEWINGPIPELINE_H

#include "Polyhedra/Polyhedron.h"
#include <fstream>
#include <string>
#include "Polyhedra/Vertex.h"
#include "Lighting/LightSource.h"
#include "Math/BoundingBox.h"
#include "Math/Vector2i.h"
#include <iostream>
#include <cmath>
#include "Util/Util.h"
#include "Lighting/RGB.h"

class Polyhedron;

class Scene {
 public:
  RGB ambientColor;
  Vector3f eyeLoc;
  RGB brightest;
  RGB darkest;

  void updateExtrema(RGB color);
  void lightVertices();

  BoundingBox computeBoundingBox();

  std::vector<LightSource> lights;

  Vector2i screenSize;

  std::vector<Polyhedron> polyhedra;

  Scene(std::string& fname, Vector2i screenSize, RGB ambientColor = RGB(0,0,1),
        Vector3f eyeLoc = Vector3f(1,1,1));

  void render();

  std::vector<Polyhedron> readScene(std::string &fname);
  void writeScene(std::string &fname);

  void addLightSource(LightSource& light);

  RGB normalize(RGB color);
};

#endif //HW2_VIEWINGPIPELINE_H
