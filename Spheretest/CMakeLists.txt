project(redbook)
cmake_minimum_required(VERSION 2.8)

add_definitions(
    --std=c++11 -Wall
)

add_library(RF_LIB "OpenGL.cpp")

add_executable(main "main.cpp")
target_link_libraries(main GL GLU GLEW glut RF_LIB)
