cmake_minimum_required(VERSION 3.10)

project(raytracing)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/camera/camera.h
    src/camera/camera.cpp
    src/utils/random.h
    src/utils/random.cpp
    src/utils/vec.h
    src/utils/vec.cpp
    src/utils/color.h
    src/utils/color.cpp
    src/utils/parse.h
    src/utils/parse.cpp
    src/utils/common_commands.h
    src/utils/object_commands.h
    src/utils/light_commands.h
    src/objects/intersection.h
    src/objects/ray.h
    src/objects/box.h
    src/objects/ellipsoid.h
    src/objects/object.h
    src/objects/light_source.h
    src/objects/plane.h
    src/scene/scene.h
    src/scene/scene.cpp
)
