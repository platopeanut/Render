cmake_minimum_required(VERSION 3.22)
project(render)

set(CMAKE_CXX_STANDARD 11)

# RUN
add_executable(render main.cpp display/defs.h display/defs.cpp graphics/common.cpp graphics/common.h graphics/materials.cpp graphics/materials.h graphics/utils.cpp graphics/utils.h graphics/lights.cpp graphics/lights.h graphics/surfaces.cpp graphics/surfaces.h)
# TEST
#add_executable(render test.cpp defs.h defs.cpp geometry.cpp geometry.h)
