cmake_minimum_required(VERSION 3.8)
project(hw2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -framework GLUT -framework OpenGL")

set(SOURCE_FILES main.cpp Util.cpp Util.h PixelBuffer.cpp PixelBuffer.h DrawPix.cpp DrawPix.h)
add_executable(hw2 ${SOURCE_FILES})