#pragma once

#include <GL/gl.h>
#include <cstdlib>
#include <iostream>
#include <vector>

struct Vertex {
	GLfloat x, y, z, w;
};

struct Color {
	GLubyte r, g, b, a;
};

struct VertexData {
		Color color;
		Vertex position;
};

std::vector<VertexData> getVertices(int cols, int rows);
Vertex getVertex(int x, int y);
Color getColor();
// void printVertices(VertexData* data, int size);
GLfloat func(int x, int y);
// void printVertex(Vertex vertex);
// void printVertexData(std::);