//
// Created by James Lemkin on 11/2/19.
//

#ifndef HW2_VIEWINGPIPELINE_H
#define HW2_VIEWINGPIPELINE_H

#include "Polyhedron.h"
#include <fstream>
#include <string>
#include "Vertex2f.h"

class Scene {
 private:
  size2 screenSize;

 public:
  std::vector<Polyhedron> polyhedra;

  explicit Scene(std::string& fname, size2 screenSize);

  void render();

  std::vector<Polyhedron> readPolyhedra(std::string &fname);
  void writePolyhedron(std::string& fname);

  int getNumPolyhedra();
};

#endif //HW2_VIEWINGPIPELINE_H
