cmake_minimum_required(VERSION 3.8)
project(hw2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp Util/glDrawing.cpp Util/glDrawing.h Polyhedra/Polyhedron.cpp Polyhedra/Polyhedron.h Polyhedra/Vertex.cpp Polyhedra/Vertex.h Scene.cpp Scene.h Math/BoundingBox.cpp Math/BoundingBox.h Math/Matrix4x4.cpp Math/Matrix4x4.h Math/Dimension.h Math/Vector3f.cpp Math/Vector3f.h Lighting/Color.cpp Lighting/Color.h Lighting/LightSource.cpp Lighting/LightSource.h Polyhedra/Triangle.cpp Polyhedra/Triangle.h Math/Vector2i.cpp Math/Vector2i.h Util/Util.cpp Util/Util.h Lighting/RGB.cpp Lighting/RGB.h Math/Vector2f.cpp Math/Vector2f.h)
add_executable(hw2 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries(hw2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})