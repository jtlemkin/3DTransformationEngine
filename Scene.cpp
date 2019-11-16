//
// Created by James Lemkin on 11/2/19.
//

#include "Scene.h"

//Draws blue axes lines
void drawAxes() {
  rgb color = makeRGB(0, 0, 1);

  auto bottom_middle = Vertex(0, -1);
  auto top_middle = Vertex(0, 1);
  auto left_middle = Vertex(-1, 0);
  auto right_middle = Vertex(1, 0);

  drawLine(bottom_middle, top_middle, color);
  drawLine(left_middle, right_middle, color);
}

//Renders the scene
void Scene::render() {
  BoundingBox boundingBox(polyhedra);

  drawAxes();

  for (const auto& polyhedron: polyhedra) {
    polyhedron.render(boundingBox, screenSize, Z);
    polyhedron.render(boundingBox, screenSize, Y);
    polyhedron.render(boundingBox, screenSize, X);
  }
}

//Constructor
Scene::Scene(std::string& fname, size2 screenSize) {
  this->screenSize = screenSize;
  polyhedra = readScene(fname);
}

//Reads a set of vertices from file pointer
std::vector<Vertex> readVerticesFromFile(std::ifstream& f) {
  std::string line;

  getline(f, line);
  int num_vertices = std::stoi(line);
  std::vector<Vertex> vertices;

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

//Reads a set of edges from a file pointer
std::vector<Face> readFacesFromFile(std::ifstream &f, std::vector<Vertex>& vertices) {
  std::string line;

  getline(f, line);
  int num_faces = std::stoi(line);
  std::vector<Face> faces;

  faces.reserve(num_faces);

  for(int j = 0; j < num_faces; j++) {
    getline(f, line);

    auto v_indices = split(line, (char) 32);

    int p1 = stoi(v_indices.at(0));
    int p2 = stoi(v_indices.at(1));
    int p3 = stoi(v_indices.at(2));

    faces.emplace_back(p1, p2, p3, 1, vertices);

    vertices[p1 - 1].addFace(faces.back());
    vertices[p2 - 1].addFace(faces.back());
    vertices[p3 - 1].addFace(faces.back());
  }

  return faces;
}

void readColorsFromFile(std::ifstream& f, std::vector<Vertex>& vertices) {
  std::string line;

  float r, g, b;

  for (auto &vertice : vertices) {
    getline(f, line);

    auto vals = split(line, (char) 32);

    r = stof(vals[0]) / 255;
    g = stof(vals[1]) / 255;
    b = stof(vals[2]) / 255;

    vertice.color = makeRGB(r, g, b);
  }
}

void readSpecularitiesFromFile(std::ifstream &f, std::vector<Face>& faces) {
  std::string line;

  for (auto &face : faces) {
    getline(f, line);

    float spec = stof(line);

    face.specularity = spec;
  }
}

std::vector<Polyhedron> readPolyhedraFromFile(std::ifstream& f) {
  std::vector<Polyhedron> polyhedra;

  std::string line;

  getline(f, line);
  int num_polyhedra = std::stoi(line);

  polyhedra.reserve(num_polyhedra);

  //skip lines
  getline(f, line);

  for(int i = 0; i < num_polyhedra; i++) {
    std::vector<Vertex> vertices = readVerticesFromFile(f);

    readColorsFromFile(f, vertices);

    std::vector<Face> faces = readFacesFromFile(f, vertices);

    readSpecularitiesFromFile(f, faces);

    polyhedra.emplace_back(vertices, faces);

    //skip line
    getline(f, line);
  }

  return polyhedra;
}

//Reads in polyhedra from a file
std::vector<Polyhedron> Scene::readScene(std::string &fname) {
  std::string line;
  std::ifstream f;
  f.open(fname);

  std::vector<Polyhedron> polyhedra;

  if (f.is_open())
  {
    polyhedra = readPolyhedraFromFile(f);
  } else {
    std::cout << "FILE UNABLE TO OPEN\n";
  }

  f.close();

  return polyhedra;
}

//Writes polyhedra to a file
void Scene::writeScene(std::string &fname) {
  std::ofstream f(fname);

  if (f.is_open()) {
    f << polyhedra.size() << "\n\n";

    for (const auto& polyhedron : polyhedra) {
      f << polyhedron.vertices.size() << "\n";

      for (int i = 0; i < polyhedron.vertices.size(); i++) {
        f << polyhedron.vertices[i].x() << " " << polyhedron.vertices[i].y() << " " << polyhedron.vertices[i].z() << "\n";
      }

      f << polyhedron.faces.size() << "\n";

      for (int i = 0; i < polyhedron.faces.size(); i++) {
        f << polyhedron.faces[i].p1 << " " << polyhedron.faces[i].p2 << "\n";
      }

      f << "\n";
    }

    f.close();
  }
}

//Returns the number of polyhedra in a scene
int Scene::getNumPolyhedra() {
  return (int) polyhedra.size();
}
