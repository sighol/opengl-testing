#pragma once
#include <Windows.h>

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

std::vector<VertexData> getVertices(int cols, int rows);
Vertex getVertex(int m,int x, int y);
Color getColor();
GLfloat func(int x, int y);
void printVertices(const std::vector<VertexData> &data);
