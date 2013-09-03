#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <cstdlib>
#include <string>

#include "LoadShaders.h"
#include "vertices.h"

void initData();
void initStaticData();
void initDynamicData();
void initShaders();
void printGlError(std::string);
uint CreateShader(std::string, GLenum);
void display();
void idle();
void mouse(int button, int state, int x, int y);
void motion(int, int);
void InitWindow(int argc, char** argv);
void error(std::string);
void printShaderError(GLuint, std::string filename);

#define BUFFER_OFFSET(x)  ((const void*) (x))