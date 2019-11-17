//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VIEWINGPIPELINE_H
#define HW2_VIEWINGPIPELINE_H

#include "Polyhedron.h"
#include <fstream>
#include <string>
#include "Vertex.h"
#include "Color.h"
#include "LightSource.h"
#include <iostream>
#include <math.h>

class Scene {
 private:
  size2 screenSize;
  Color ambientColor;
  Vector3f eyeLoc;
  Color brightest;
  Color darkest;

  std::vector<LightSource> lights;

  void updateExtrema(Color color);

 public:
  std::vector<Polyhedron> polyhedra;

  Scene(std::string& fname, size2 screenSize, Color ambientColor = Color(0,0,0), Vector3f eyeLoc = Vector3f(0,0,0));

  void render();

  std::vector<Polyhedron> readScene(std::string &fname);
  void writeScene(std::string &fname);

  int getNumPolyhedra();

  Color computeColorOfVertex(Vertex& vertex);
};

#endif //HW2_VIEWINGPIPELINE_H
