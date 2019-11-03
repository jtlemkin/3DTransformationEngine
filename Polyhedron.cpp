//
// Created by James Lemkin on 10/31/19.
//

#include "Polyhedron.h"

void drawLine(Vertex2f p1, Vertex2f p2, pixel color) {
  glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
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

void Polyhedron::render(BoundingBox boundingBox, size2 screensize, Dimension toIgnore) const {
  std::vector<Vertex3f> normalizedVertices = normalizeVertices(vertices, boundingBox);
  std::vector<Vertex2f> flattenedVertices = flattenVertices(normalizedVertices, toIgnore);

  pixel color = makePixel(0,0,0);
  for (int i = 0; i < numEdges; i++) {
    /*
     * Edge.x refers to the index of the starting vertex of an edge and edge.y refers to the index of the ending
     * vertex of an edge. Indices start at 1 so we subtract all indices by 1.
    */

    drawLine(flattenedVertices[edges[i].x - 1], flattenedVertices[edges[i].y - 1], color);
  }
}

Polyhedron::Polyhedron(int numVertices,
                       std::vector<Vertex3f> vertices,
                       int numEdges,
                       std::vector<vector2> edges)
    : numVertices(numVertices), numEdges(numEdges) {
  this->vertices = std::move(vertices);
  this->edges = std::move(edges);
}
