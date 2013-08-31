project(redbook)
cmake_minimum_required(VERSION 2.8)

file(GLOB SRC_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cxx")
message(${SRC_LIST})
include_directories("../include")

add_definitions(
    --std=c++11 -Wall
)

add_library(RF_LIB "readfile.cpp")
add_executable(readfile "readfile-test.cpp")
target_link_libraries(readfile RF_LIB)

add_library(LS_LIB "../lib/LoadShaders.cpp")

foreach (src ${SRC_LIST})
	string(REPLACE ".cxx" "" name ${src})
	message("${src} -> ${name}")
	add_executable(${name} ${src})
	target_link_libraries(${name} GL GLU GLEW glfw glut RF_LIB LS_LIB)
endforeach(src ${SRC_LIST})
