#include <iostream>

using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs {Triangles=0, NumVAOs=1};
enum Buffer_IDs {ArrayBuffer=0, NumBuffers=1};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init()
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
		{ -0.90, -0.90}, // Triangle 1
		{  0.85, -0.90},
		{ -0.90,  0.85},
		{  0.90, -0.85}, // Triangle 2
		{  0.90,  0.90},
		{ -0.85,  0.90}
	};
}

int main(int argc, char const *argv[])
{

}