#pragma once

#include <GL/gl.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

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
Vertex getVertex(int m,int x, int y);
Color getColor();
GLfloat func(int x, int y);
void printVertices(const std::vector<VertexData> &data);