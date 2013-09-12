#include "loadshaders.h"

using namespace std;


GLuint LoadShaders(GLsizei size, ShaderInfo info[]) {
	GLuint programId = glCreateProgram();
	for (GLsizei i = 0; i < size; i++) {
		ShaderInfo* val = &info[i];
		val->shaderId = CreateShader(val->filename, val->type);
		glAttachShader(programId, val->shaderId);
	}
	glLinkProgram(programId);
	return programId;
}

GLuint CreateShader(string filename, GLenum shaderType) {
	string filepath = "shaders/" + filename;
	string strShader = readlines(filepath);
	const char* cShader = strShader.c_str();

	GLuint shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &cShader, NULL);
	glCompileShader(shaderId);
	printShaderError(shaderId, filename);
	return shaderId;
}


void printShaderError(GLuint shaderId, string filename) {
	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
	    GLint infoLogLength;
	    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	    GLchar* strInfoLog = new GLchar[infoLogLength + 1];
	    glGetShaderInfoLog(shaderId, infoLogLength, NULL, strInfoLog);

	    fprintf(stderr, "Compilation error in shader %s: %s\n", filename.c_str(), strInfoLog);
	    delete[] strInfoLog;
	    exit(EXIT_FAILURE);
	}
}
