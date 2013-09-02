#pragma once

#include <GL/gl.h>
#include <cstdlib>
#include <iostream>

typedef GLfloat* Vertex;
typedef GLubyte* Color;

typedef struct {
		GLubyte *color;
		GLfloat *position;
} VertexData;


VertexData* getVertices(int cols, int rows, uint* size);
Vertex getVertex(int x, int y);
Color getColor();
void printVertices(VertexData* data, int size);
GLfloat func(int x, int y);
void printVertex(Vertex vertex);
void printVertexData(VertexData *v);