//
// Created by James Lemkin on 11/2/19.
//

#include "Scene.h"

//Draws blue axes lines
/*void drawAxes() {
  Color color(0, 0, 255);

  auto bottom_middle = Vertex(0, -1);
  auto top_middle = Vertex(0, 1);
  auto left_middle = Vertex(-1, 0);
  auto right_middle = Vertex(1, 0);

  drawLine(bottom_middle, top_middle, color);
  drawLine(left_middle, right_middle, color);
}*/

//Renders the scene
void Scene::render() {
  BoundingBox boundingBox = computeBoundingBox();

  //drawAxes();

  lightVertices();

  for (const auto& polyhedron: polyhedra) {
    polyhedron.render(*this, boundingBox, Z);
    polyhedron.render(*this, boundingBox, Y);
    polyhedron.render(*this, boundingBox, X);
  }
}

//Constructor
Scene::Scene(std::string& fname, Vector2i screenSize, RGB ambientColor, Vector3f eyeLoc)
    : ambientColor(ambientColor), eyeLoc(eyeLoc), darkest(RGB(2, 2, 2)),
      brightest(RGB(0, 0, 0)), screenSize(screenSize) {

  polyhedra = readScene(fname);
}

//Reads a set of vertices from file pointer
void readVerticesFromFile(std::ifstream& f, Polyhedron& polyhedron) {
  std::string line;

  getline(f, line);
  int num_vertices = std::stoi(line);

  polyhedron.vertices.reserve(num_vertices);

  for(int j = 0; j < num_vertices; j++) {
    getline(f, line);

    auto points = split(line, (char) 32);

    float x = stof(points.at(0));
    float y = stof(points.at(1));
    float z = stof(points.at(2));

    polyhedron.vertices.emplace_back(j, x, y, z);
  }
}

//Reads a set of edges from a file pointer
void readFacesFromFile(std::ifstream &f, Polyhedron& polyhedron) {
  std::string line;

  getline(f, line);
  int num_faces = std::stoi(line);

  polyhedron.triangles.reserve(num_faces);

  for(int j = 0; j < num_faces; j++) {
    getline(f, line);

    auto v_indices = split(line, (char) 32);

    int v1ID = stoi(v_indices.at(0)) - 1;
    int v2ID = stoi(v_indices.at(1)) - 1;
    int v3ID = stoi(v_indices.at(2)) - 1;

    polyhedron.triangles.emplace_back(j, v1ID, v2ID, v3ID, 1);

    polyhedron.vertices[v1ID].addTriangle(j);
    polyhedron.vertices[v2ID].addTriangle(j);
    polyhedron.vertices[v3ID].addTriangle(j);
  }
}

void readColorsFromFile(std::ifstream& f, Polyhedron& polyhedron) {
  std::string line;

  float r, g, b;

  for (auto &vertice : polyhedron.vertices) {
    getline(f, line);

    auto vals = split(line, (char) 32);

    r = stof(vals[0]) / 255;
    g = stof(vals[1]) / 255;
    b = stof(vals[2]) / 255;

    vertice.diffuseColor = RGB(r, g, b);
  }
}

void readSpecularitiesFromFile(std::ifstream &f, Polyhedron& polyhedron) {
  std::string line;

  for (auto &face : polyhedron.triangles) {
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
    polyhedra.emplace_back();

    readVerticesFromFile(f, polyhedra.back());

    readColorsFromFile(f, polyhedra.back());

    readFacesFromFile(f, polyhedra.back());

    readSpecularitiesFromFile(f, polyhedra.back());

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
/*void Scene::writeScene(std::string &fname) {
  std::ofstream f(fname);

  if (f.is_open()) {
    f << polyhedra.size() << "\n\n";

    for (const auto& polyhedron : polyhedra) {
      f << polyhedron.vertices.size() << "\n";

      for (int i = 0; i < polyhedron.vertices.size(); i++) {
        f << polyhedron.vertices[i].x() << " " << polyhedron.vertices[i].y() << " " << polyhedron.vertices[i].z() << "\n";
      }

      f << polyhedron.triangles.size() << "\n";

      for (int i = 0; i < polyhedron.triangles.size(); i++) {
        f << polyhedron.triangles[i].p1 << " " << polyhedron.triangles[i].p2 << "\n";
      }

      f << "\n";
    }

    f.close();
  }
}*/

void Scene::updateExtrema(RGB color) {
  brightest.r = std::max(brightest.r, color.r);
  brightest.g = std::max(brightest.g, color.g);
  brightest.b = std::max(brightest.b, color.b);

  darkest.r = std::min(darkest.r, color.r);
  darkest.g = std::min(darkest.g, color.g);
  darkest.b = std::min(darkest.b, color.b);
}

void Scene::addLightSource(LightSource& light) {
  lights.push_back(light);
}

void Scene::lightVertices() {
  for (auto& polyedron : polyhedra) {
    for (int i = 0; i < polyedron.vertices.size(); i++) {
      Vertex& v = polyedron.vertices[i];

      v.color = polyedron.getVertexColor(i, eyeLoc, lights[0], ambientColor);

      updateExtrema(v.color);
    }
  }
}

BoundingBox Scene::computeBoundingBox() {
  BoundingBox bb;

  for (const auto& polyhedron : polyhedra) {
    for (const auto &vertex : polyhedron.vertices) {
      bb.addPoint(Vector3f(vertex.x(), vertex.y(), vertex.z()));
    }
  }

  return bb;
}

RGB Scene::normalize(RGB color) {
  float highestIntensity = std::max(std::max(brightest.r, brightest.g), brightest.b);
  float lowestIntensity = std::min(std::min(darkest.r, darkest.g), darkest.b);

  float intensityRange = highestIntensity - lowestIntensity;

  if (intensityRange == 0) {
    return color;
  }

  float r = color.r / intensityRange;
  float g = color.g / intensityRange;
  float b = color.b / intensityRange;

  return RGB(r, g, b);
}

