project(redbook)
cmake_minimum_required(VERSION 2.8)

file(GLOB EXEC_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cxx")
file(GLOB SRC_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

add_definitions(
    --std=c++11 -Wall
)

add_library(RF_LIB ${SRC_LIST})

foreach (src ${EXEC_LIST})
	string(REPLACE ".cxx" "" name ${src})
	message("${src} -> ${name}")
	add_executable(${name} ${src})
	target_link_libraries(${name} GL GLU GLEW glut RF_LIB)
endforeach(src ${EXEC_LIST})
