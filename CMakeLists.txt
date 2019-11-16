cmake_minimum_required(VERSION 3.8)
project(hw2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp Structs/Util.cpp Structs/Util.h Structs/glDrawing.cpp Structs/glDrawing.h Polyhedron.cpp Polyhedron.h Vertex.cpp Vertex.h Scene.cpp Scene.h BoundingBox.cpp BoundingBox.h Matrix4x4.cpp Matrix4x4.h Dimension.h Vector3f.cpp Vector3f.h)
add_executable(hw2 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries(hw2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})