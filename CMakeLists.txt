cmake_minimum_required(VERSION 3.8)
project(hw2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -framework GLUT -framework OpenGL")

set(SOURCE_FILES main.cpp Structs/Util.cpp Structs/Util.h Structs/PixelBuffer.cpp Structs/PixelBuffer.h Structs/DrawPix.cpp Structs/DrawPix.h Polyhedron.cpp Polyhedron.h Vertex2f.cpp Vertex2f.h Scene.cpp Scene.h BoundingBox.cpp BoundingBox.h)
add_executable(hw2 ${SOURCE_FILES})