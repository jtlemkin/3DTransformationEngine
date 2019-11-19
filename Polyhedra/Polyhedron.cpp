//
// Created by James Lemkin on 10/31/19.
//

#include "Polyhedron.h"

//Constructor
Polyhedron::Polyhedron() {}

//Transforms vertices through viewing pipeline and then draws all edges to screen
void Polyhedron::render(Scene& scene, BoundingBox& boundingBox, Dimension toIgnore) const {
  setViewport(scene.screenSize.x, scene.screenSize.y, toIgnore);

  for (int i = 0; i < triangles.size(); i++) {
    renderTriangle(i, scene, toIgnore);
  }

  resetViewport(scene.screenSize.x, scene.screenSize.y);
}

void Polyhedron::renderTriangle(int triangleID, Scene& scene, Dimension toIgnore) const {
  Triangle t = triangles[triangleID];

  auto v1 = vertices[t.v1ID];
  auto v2 = vertices[t.v2ID];
  auto v3 = vertices[t.v3ID];

  Vector2i p1 = v1.flatten(toIgnore).getDeviceCoords(scene.screenSize.x, scene.screenSize.y);
  Vector2i p2 = v2.flatten(toIgnore).getDeviceCoords(scene.screenSize.x, scene.screenSize.y);
  Vector2i p3 = v3.flatten(toIgnore).getDeviceCoords(scene.screenSize.x, scene.screenSize.y);

  int yMin = std::min(std::min(p1.y, p2.y), p3.y);
  int yMax = std::max(std::max(p1.y, p2.y), p3.y);

  for (int y = yMin; y <= yMax; y++) {
    int xStart, xEnd;
    RGB cStart(-1,-1,-1);
    RGB cEnd(-1,-1,-1);

    computeIntersectionLocationsAndColors(y, p1, p2, p3, v1.color, v2.color, v3.color, &xStart, &xEnd, &cStart, &cEnd);

    float dx = xEnd - xStart;

    for(int x = xStart; x <= xEnd; x++) {
      auto startRGB = scene.normalize(cStart);
      auto endRGB = scene.normalize(cEnd);

      RGB displayRGB = dx == 0 ? startRGB :
                       startRGB.mult((float) (xEnd - x) / dx).add(endRGB.mult(((float) (x - xStart) / dx)));

      auto raster = Vector2i(x, y).toNDC(scene.screenSize.x, scene.screenSize.y);

      draw_pix(raster.x, raster.y, displayRGB.r, displayRGB.g, displayRGB.b);
    }
  }
}

Vector3f Polyhedron::getVertexNormal(int vertexID) {
  Vector3f sumOfNormals(0,0,0);

  for (const auto& triangleID : vertices[vertexID].triangleIDs) {
    sumOfNormals = sumOfNormals.add(getFaceNormal(triangleID));
  }

  auto numTriangles = vertices[vertexID].triangleIDs.size();

  Vector3f avgOfNormals = sumOfNormals.divideBy(numTriangles);

  return avgOfNormals.normalize();
}

Vector3f Polyhedron::getFaceNormal(int triangleID) {
  Triangle tri = triangles[triangleID];
  Vertex v1 = vertices[tri.v1ID];
  Vertex v2 = vertices[tri.v2ID];
  Vertex v3 = vertices[tri.v3ID];

  Vector3f a = Vector3f(v2.x() - v1.x(), v2.y() - v1.y(), v2.z() - v1.z());
  Vector3f b = Vector3f(v3.x() - v1.x(), v3.y() - v1.y(), v3.z() - v1.z());

  float x = (a.y * b.z) - (a.z - b.y);
  float y = (a.z - b.x) - (a.x * b.z);
  float z = (a.x * b.y) - (a.y - b.x);

  return Vector3f(x, y, z);
}

int Polyhedron::getVertexSpecularity(int vertexID) {
  int specularity = 0;

  Vertex v = vertices[vertexID];

  for (const auto& triangleID : v.triangleIDs) {
    specularity += triangles[triangleID].specularity;
  }

  if (v.triangleIDs.size() == 0) {
    return 0;
  }

  return specularity / (int) v.triangleIDs.size();
}

RGB Polyhedron::getVertexColor(int vertexID, Vector3f &eyeLoc, LightSource light, RGB ambientColor) {
  Vertex v = vertices[vertexID];

  float distanceBetweenPointAndEye = eyeLoc.minus(Vector3f(v.x(), v.y(), v.z())).magnitude();
  float intensityAtV = light.intensity / (distanceBetweenPointAndEye + light.k);

  Vector3f vertexNormal = getVertexNormal(vertexID).normalize();
  Vector3f lightVector = Vector3f(light.loc.x - v.x(), light.loc.y - v.y(), light.loc.z - v.z()).normalize();
  Vector3f reflectionVector = vertexNormal.multiply(2 * vertexNormal.dot(lightVector)).minus(lightVector).normalize();
  Vector3f viewVector = eyeLoc.minus(Vector3f(v.x(), v.y(), v.z())).normalize();

  float lightDotNormal = lightVector.dot(vertexNormal);
  float reflectionDotView = reflectionVector.dot(viewVector);

  RGB diffuseColor = lightDotNormal <= 0 ? RGB(0,0,0) : v.diffuseColor.mult(lightDotNormal);

  RGB specularColor = lightDotNormal <= 0 || reflectionDotView <= 0 ?
                      RGB(0,0,0) : light.color.mult((float) pow(reflectionDotView, getVertexSpecularity(vertexID)));

  RGB finalColor = ambientColor.add(diffuseColor.add(specularColor).mult(intensityAtV));

  return finalColor;
}

//Translates a polyhedron
/*void Polyhedron::translate(float x, float y, float z) {
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
}*/