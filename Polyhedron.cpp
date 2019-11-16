//
// Created by James Lemkin on 10/31/19.
//

#include "Polyhedron.h"

//Constructor
Polyhedron::Polyhedron(std::vector<Vertex> vertices, std::vector<Face> faces) {
  this->vertices = std::move(vertices);
  this->faces = std::move(faces);
}

//Normalizes a float to a value between 0 and 1
float normalize(float val, float min, float max) {
  if (max == min) {
    return 0;
  }

  return (val - min) / (max - min) * 2 - 1;
}

//Returns a vector of vertices that have been normalized within the bounding box
std::vector<Vertex> normalizeVertices(std::vector<Vertex> vertices, BoundingBox boundingBox) {
  std::vector<Vertex> normalizedVertices;

  for (const auto& vertex : vertices) {
    auto x = normalize(vertex.x(), boundingBox.min, boundingBox.max);
    auto y = normalize(vertex.y(), boundingBox.min, boundingBox.max);
    auto z = normalize(vertex.z(), boundingBox.min, boundingBox.max);

    normalizedVertices.emplace_back(x, y, z);
  }

  return normalizedVertices;
}

//Returns a vector of 2D vertices from 3D vertices for drawing
std::vector<Vertex> flattenVertices(std::vector<Vertex> vertices, Dimension d) {
  std::vector<Vertex> flattenedVertices = vertices;

  for (auto& vertex : flattenedVertices) {
    vertex.flatten(d);
  }

  return flattenedVertices;
}

//Set the gl viewport to a quarter of the screen
void setViewport(size2 screensize, Dimension toIgnore) {
  switch(toIgnore) {
    case X:
      glViewport(0, 0, screensize.width / 2, screensize.height / 2);
      break;
    case Y:
      glViewport(screensize.width / 2, screensize.width / 2, screensize.width / 2, screensize.height / 2);
      break;
    case Z:
      glViewport(0, screensize.width / 2, screensize.width / 2, screensize.height / 2);
  }
}

//Resets gl viewport to default
void resetViewport(size2 screensize) {
  glViewport(0, 0, screensize.width, screensize.height);
}

//Transforms vertices through viewing pipeline and then draws all edges to screen
void Polyhedron::render(BoundingBox boundingBox, size2 screensize, Dimension toIgnore) const {
  auto normalVertices = normalizeVertices(vertices, boundingBox);
  auto flatVertices = flattenVertices(normalVertices, toIgnore);

  setViewport(screensize, toIgnore);

  rgb color = makeRGB(0, 0, 0);
  for (int i = 0; i < faces.size(); i++) {
    /*
     * Edge.x refers to the index of the starting vertex of an edge and edge.y refers to the index of the ending
     * vertex of an edge. Indices start at 1 so we subtract all indices by 1.
    */

    auto face = faces[i];

    drawFace(flatVertices[face.p1 - 1], flatVertices[face.p2 - 1], flatVertices[face.p3 - 1], color, toIgnore);
  }

  resetViewport(screensize);
}

//Translates a polyhedron
void Polyhedron::translate(float x, float y, float z) {
  for(auto& vertex : vertices) {
    vertex.translate(makeVector3(x, y, z));
  }
}

//Rotates a polyhedron around an arbitrary axis
void Polyhedron::rotate(float angle, vector3 p1, vector3 p2) {
  for(auto& vertex : vertices) {
    vertex.rotate_around_axis(angle, p1, p2);
  }
}

//Computes bounds of polyhedron and returns the center point
vector3 Polyhedron::getCentroid() {
  float minX, minY, minZ, maxX, maxY, maxZ;

  maxX = std::numeric_limits<float>::min();
  maxY = std::numeric_limits<float>::min();
  maxZ = std::numeric_limits<float>::min();

  minX = std::numeric_limits<float>::max();
  minY = std::numeric_limits<float>::max();
  minZ = std::numeric_limits<float>::max();

  for(const auto& vertex : vertices) {
    minX = std::min(minX, vertex.x());
    minY = std::min(minY, vertex.y());
    minZ = std::min(minZ, vertex.z());

    maxX = std::max(maxX, vertex.x());
    maxY = std::max(maxY, vertex.y());
    maxZ = std::max(maxZ, vertex.z());
  }

  return makeVector3((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);
}

//Scales a polyhedron around its centroid
void Polyhedron::scale(float factor) {
  vector3 centroid = getCentroid();

  for(auto& vertex : vertices) {
    vertex.scale(factor, centroid);
  }
}

Face::Face(int p1, int p2, int p3, float specularity) : p1(p1), p2(p2), p3(p3), specularity(specularity) {}
