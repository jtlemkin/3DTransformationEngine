//
// Created by James Lemkin on 11/2/19.
//

#include <iostream>
#include "Scene.h"

void Scene::render() {
  BoundingBox boundingBox(polyhedra);

  for (const auto& polyhedron: polyhedra) {
    polyhedron.renderXY(boundingBox, screenSize);
  }
}

Scene::Scene(std::string& fname, size2 screenSize) {
  this->screenSize = screenSize;
  polyhedra = readPolyhedron(fname);
}

std::vector<Polyhedron> Scene::readPolyhedron(std::string& fname) {
  std::string line;
  std::ifstream f;
  f.open(fname);

  std::vector<Polyhedron> polyhedra;

  if (f.is_open())
  {
    getline(f, line);
    int num_polyhedra = std::stoi(line);

    polyhedra.reserve(num_polyhedra);

    for(int i = 0; i < num_polyhedra; i++) {
      getline(f, line);
      int num_vertices = std::stoi(line);
      std::vector<Vertex3f> vertices;

      vertices.reserve(num_vertices);

      for(int j = 0; j < num_vertices; j++) {
        getline(f, line);

        auto points = split(line, (char) 32);

        float x = stof(points.at(0));
        float y = stof(points.at(1));
        float z = stof(points.at(2));

        vertices.emplace_back(x, y, z);
      }

      polyhedra.emplace_back(num_vertices, vertices);
    }
  } else {
    std::cout << "FILE UNABLE TO OPEN\n";
  }

  f.close();

  return polyhedra;
}

void Scene::writePolyhedron(std::string& fname) {
  std::ofstream f(fname);

  if (f.is_open()) {
    f << polyhedra.size() << "\n";

    for (const auto& polyhedron : polyhedra) {
      f << polyhedron.numVertices << "\n";

      for (int i = 0; i < polyhedron.numVertices; i++) {
        f << polyhedron.vertices[i].x << " " << polyhedron.vertices[i].y << polyhedron.vertices[i].z << "\n";
      }
    }

    f.close();
  }
}