#include <iostream>
#include <string>

using namespace std;

#include "vgl.h"
#include "readfile.h"

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VaoId;

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

int WindowHandle;



typedef struct {
	GLenum type;
	string filename;
} ShaderInfo;

GLuint LoadShaders(GLsizei size, ShaderInfo infos[]);
void printGlError();

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

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
				 vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"}
	};

	glGetError();
	GLuint program = LoadShaders(2, shaders);
	glUseProgram(program);
	printGlError();
	glVertexAttribPointer(vPosition, 2, GL_FLOAT,
						  GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void printGlError() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		cerr << "Could not create the shaders: " << gluErrorString(error) << endl;
	} else {
		cout << "ingen error" << endl;
	}
}


uint CreateShader(string filename, GLenum shaderType) {
	string filepath = "shaders/" + filename;
	string strShader = readlines(filepath);
	cout << strShader << endl;
	const char* cShader = strShader.c_str();

	GLuint shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &cShader, NULL);
	glCompileShader(shaderId);
	return shaderId;
}

uint LoadShaders(GLsizei size, ShaderInfo info[]) {
	GLuint programId = glCreateProgram();
	for (GLsizei i = 0; i < size; i++) {
		ShaderInfo* val = &info[i];
		GLuint shaderId = CreateShader(val->filename, val->type);
		glAttachShader(programId, shaderId);
	}
	glLinkProgram(programId);
	return programId;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	glutInitWindowSize(512, 512);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(argv[0]);

	if (WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();
	if (GLEW_OK != glewInitResult) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		cerr << glewGetErrorString(glewInitResult) << endl;
		exit(EXIT_FAILURE);
	}

	init();

	glutDisplayFunc(display);

	glutMainLoop();
}