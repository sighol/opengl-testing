#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>

#include "readfile.h"

typedef struct {
	GLenum type;
	std::string filename;
} ShaderInfo;

void init();
GLuint LoadShaders(GLsizei, ShaderInfo[]);
void printGlError(std::string);
uint CreateShader(std::string, GLenum);
void display();
void InitializeWindow(int argc, char** argv);