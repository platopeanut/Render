cmake_minimum_required(VERSION 3.22)
project(RENDER)

set(CMAKE_CXX_STANDARD 11)


#add_executable(render PixelOrderRender.cpp graphics/transformation.cpp graphics/transformation.h graphics/common.cpp graphics/common.h graphics/materials.cpp graphics/materials.h graphics/utils.cpp graphics/utils.h graphics/lights.cpp graphics/lights.h graphics/surfaces.cpp graphics/surfaces.h display/win32.cpp display/win32.h)
add_executable(render ObjectOrderRender.cpp graphics/transformation.cpp graphics/transformation.h graphics/common.cpp graphics/common.h graphics/materials.cpp graphics/materials.h graphics/utils.cpp graphics/utils.h graphics/lights.cpp graphics/lights.h graphics/surfaces.cpp graphics/surfaces.h display/win32.cpp display/win32.h)

