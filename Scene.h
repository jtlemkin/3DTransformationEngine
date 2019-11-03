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
  std::vector<Polyhedron> polyhedra;
  size2 screenSize;

 public:
  explicit Scene(std::string& fname, size2 screenSize);

  void render();

  std::vector<Polyhedron> readPolyhedron(std::string& fname);
  void writePolyhedron(std::string& fname);
};

#endif //HW2_VIEWINGPIPELINE_H
