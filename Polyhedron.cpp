//
// Created by James Lemkin on 10/31/19.
//

#include "Polyhedron.h"

void drawTriangle(Vertex2f p1, Vertex2f p2, Vertex2f p3, pixel color) {
  glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);

    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);

    glVertex2f(p3.x, p3.y);
    glVertex2f(p1.x, p1.y);
  glEnd();
}

float normalize(float val, float min, float max) {
  if (max == min) {
    return 0;
  }

  return (val - min) / (max - min) * 2 - 1;
}

std::vector<Vertex3f> normalizeVertices(std::vector<Vertex3f> vertices, BoundingBox boundingBox) {
  std::vector<Vertex3f> normalizedVertices;

  for (const auto& vertex : vertices) {
    auto x = normalize(vertex.x, boundingBox.min, boundingBox.max);
    auto y = normalize(vertex.y, boundingBox.min, boundingBox.max);
    auto z = normalize(vertex.z, boundingBox.min, boundingBox.max);

    normalizedVertices.emplace_back(x, y, z);
  }

  return normalizedVertices;
}

std::vector<Vertex2f> flattenVertices(std::vector<Vertex3f> vertices, Dimension d) {
  std::vector<Vertex2f> flattenedVertices;

  for (const auto& vertex : vertices) {
    flattenedVertices.push_back(vertex.flatten(d));
  }

  return flattenedVertices;
}

std::vector<Vertex2i> pixelizeVertices(std::vector<Vertex2f> vertices, size2 screensize) {
  std::vector<Vertex2i> pixelVertices;

  for (const auto& vertex : vertices) {
    pixelVertices.push_back(vertex.pixelize(screensize));
  }

  return pixelVertices;
}

Polyhedron::Polyhedron(int numVertices, std::vector<Vertex3f> vertices) : numVertices(numVertices), vertices(vertices) {}

void Polyhedron::renderXY(BoundingBox boundingBox, size2 screensize) const {
  std::vector<Vertex3f> normalizedVertices = normalizeVertices(vertices, boundingBox);
  std::vector<Vertex2f> flattenedVertices = flattenVertices(normalizedVertices, Z);

  for (int i = 0; i < numVertices - 2; i++) {
    pixel color = makePixel(0,0,0);

    drawTriangle(flattenedVertices[i], flattenedVertices[i + 1], flattenedVertices[i + 2], color);
  }
}
void Polyhedron::renderXZ(BoundingBox boundingBox, size2 screensize) const {

}
void Polyhedron::renderYZ(BoundingBox boundingBox, size2 screensize) const {

}
