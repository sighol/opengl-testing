#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "loadshaders.h"
#include "vertices.h"

void initDynamicData();
void initShaders();
void printGlError(std::string);
void display();
void mouse(int button, int state, int x, int y);
void motion(int, int);
void InitWindow(int argc, char** argv);
void error(std::string);
void initUniforms(GLuint program);

#define BUFFER_OFFSET(x)  ((const void*) (x))
