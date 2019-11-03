//
// Created by James Lemkin on 11/2/19.
//

#include <iostream>
#include "Scene.h"

void Scene::render() {
  BoundingBox boundingBox(polyhedra);

  for (const auto& polyhedron: polyhedra) {
    polyhedron.render(boundingBox, screenSize, Z);
    polyhedron.render(boundingBox, screenSize, Y);
    polyhedron.render(boundingBox, screenSize, X);
  }
}

Scene::Scene(std::string& fname, size2 screenSize) {
  this->screenSize = screenSize;
  polyhedra = readPolyhedron(fname);
}

std::vector<Vertex3f> readVerticesFromFile(std::ifstream& f) {
  std::string line;

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

  return vertices;
}

std::vector<vector2> readEdgesFromFile(std::ifstream& f) {
  std::string line;

  getline(f, line);
  int num_edges = std::stoi(line);
  std::vector<vector2> edges;

  edges.reserve(num_edges);

  for(int j = 0; j < num_edges; j++) {
    getline(f, line);

    auto v_indices = split(line, (char) 32);

    int x = stoi(v_indices.at(0));
    int y = stoi(v_indices.at(1));

    edges.push_back(makeVector2(x, y));
  }

  return edges;
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

    //skip lines
    getline(f, line);

    for(int i = 0; i < num_polyhedra; i++) {
      int num_vertices = 0;
      auto vertices = readVerticesFromFile(f);

      int num_edges = 0;
      auto edges = readEdgesFromFile(f);

      polyhedra.emplace_back((int) vertices.size(), vertices, (int) edges.size(), edges);

      //skip line
      getline(f, line);
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
    f << polyhedra.size() << "\n\n";

    for (const auto& polyhedron : polyhedra) {
      f << polyhedron.numVertices << "\n";

      for (int i = 0; i < polyhedron.numVertices; i++) {
        f << polyhedron.vertices[i].x << " " << polyhedron.vertices[i].y << polyhedron.vertices[i].z << "\n";
      }

      for (int i = 0; i < polyhedron.numEdges; i++) {
        f << polyhedron.edges[i].x << " " << polyhedron.edges[i].y << "\n";
      }

      f << "\n";
    }

    f.close();
  }
}