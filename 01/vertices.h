#pragma once
// #include <Windows.h>

#include <GL/gl.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

class Vertex {
public:Vertex(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z), w(1){}
	   Vertex(){};
	GLfloat x, y, z, w;
};

class Color {
	public:Color(GLfloat _x, GLfloat _y, GLfloat _z) : r(_x), g(_y), b(_z), a(1){}
		   Color(){};
	GLubyte r, g, b, a;
};

class VertexData {
	public:VertexData(Color c, Vertex v):color(c), position(v){};
		   VertexData(){};
		Color color;
		Vertex position;
};

class Dimension {
public:
	Dimension(GLfloat _x, GLfloat _y, GLfloat _w, GLfloat _h) :
			x(_x), y(_y), width(_w), height(_h){};
	GLfloat x, y, width, height;
};

class SurfData {
public:
	SurfData(GLfloat (*_func) (GLfloat, GLfloat), Dimension _d) :
			dimension(_d), func(_func) {};
	Dimension dimension;
	GLfloat (*func)(GLfloat, GLfloat);
	VertexData triangles;
	VertexData grid;
	GLfloat minZ;
	GLfloat maxZ;
};

std::vector<VertexData> getVertices(Dimension, int cols, int rows);
Vertex getVertex(GLfloat x, GLfloat y);
Color getColor();
GLfloat func(GLfloat x, GLfloat y);
void printVertices(const std::vector<VertexData> &data);

