//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VIEWINGPIPELINE_H
#define HW2_VIEWINGPIPELINE_H

#include "Polyhedra/Polyhedron.h"
#include <fstream>
#include <string>
#include "Polyhedra/Vertex.h"
#include "Lighting/Color.h"
#include "Lighting/LightSource.h"
#include "Math/BoundingBox.h"
#include "Math/Vector2i.h"
#include <iostream>
#include <math.h>
#include "Util/Util.h"
#include "Lighting/RGB.h"

class Polyhedron;

class Scene {
 private:
  Color ambientColor;
  Vector3f eyeLoc;
  Color brightest;
  Color darkest;

  std::vector<LightSource> lights;

  void updateExtrema(Color color);
  void lightVertices();

  BoundingBox computeBoundingBox();

 public:
  Vector2i screenSize;

  std::vector<Polyhedron> polyhedra;

  Scene(std::string& fname, Vector2i screenSize, Color ambientColor = Color(255,255,255), Vector3f eyeLoc = Vector3f(1,1,1));

  void render();

  std::vector<Polyhedron> readScene(std::string &fname);
  void writeScene(std::string &fname);

  int getNumPolyhedra();

  void addLightSource(LightSource& light);

  RGB normalize(Color color);
};

#endif //HW2_VIEWINGPIPELINE_H
