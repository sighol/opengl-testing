#pragma once

#ifdef _WIN32
	#include <Windows.h>
	#include <string>
	#define STRDUP _strdup
#elif __gnu_linux__
	#define STRDUP strdup
	#include <string.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

enum Attribute
{
	Position,
	Color
};

class Vertex {
public:
	Vertex(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z), w(1){}
	Vertex(){};
	GLfloat x, y, z, w;
};

struct VertexBufferData
{
	int vertices;
	GLuint type;
	GLuint VAO;
};

class OpenGL
{
	std::map<int, VertexBufferData> vertexBuffers;
	GLuint programId;
	std::map<GLchar*, int> uniforms;

public:
	void start();
	void startDraw();
	void endDraw();
	void init();
	void CompileProgram();
	void AddShader(string filename, GLenum shaderType);
	void printShaderError(GLuint shaderId, string filename);
	void error(string title);
	void setUniform(GLchar*, float);

	int addVertexBuffer(GLuint type, std::vector<Vertex> vertices);
	void drawVertexBuffer(int num);
};

