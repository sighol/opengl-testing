#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "readfile.h"
#include <string>


typedef struct {
	GLenum type;
	std::string filename;
	GLuint shaderId;
} ShaderInfo;


GLuint LoadShaders(GLsizei, ShaderInfo[]);
GLuint CreateShader(std::string filename, GLenum shaderType);
void printShaderError(GLuint shaderId, std::string filename);
