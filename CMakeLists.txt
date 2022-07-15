cmake_minimum_required(VERSION 3.22)
project(render)

set(CMAKE_CXX_STANDARD 11)

# RUN
add_executable(render main.cpp defs.h defs.cpp geometry.cpp geometry.h)
# TEST
#add_executable(render test.cpp defs.h defs.cpp geometry.cpp geometry.h)
