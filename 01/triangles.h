#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <cstdlib>
#include <string>

#include "readfile.h"

typedef struct {
	GLenum type;
	std::string filename;
} ShaderInfo;

void initData();
void initShaders();
GLuint LoadShaders(GLsizei, ShaderInfo[]);
void printGlError(std::string);
uint CreateShader(std::string, GLenum);
void display();
void InitWindow(int argc, char** argv);
void error(std::string);
void printShaderError(GLuint, std::string filename);