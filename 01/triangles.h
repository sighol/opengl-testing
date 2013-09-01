#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <cstdlib>
#include <string>

#include "LoadShaders.h"

void initData();
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

struct VertexData {
		GLubyte *color;
		GLfloat *position;
};
typedef GLfloat* Vertex;
typedef GLubyte* Color;

VertexData* getVertices(int cols, int rows, int* size);


Vertex getVertex(int x, int y);
Color getColor();
