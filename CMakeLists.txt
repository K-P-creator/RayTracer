cmake_minimum_required(VERSION 3.16)

project("RayTracer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/Main.cpp src/Sphere.cpp src/Scene.cpp src/Plane.cpp)