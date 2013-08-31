#include "triangles.h"

using namespace std;


enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VaoId;

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

int WindowHandle;

int main(int argc, char **argv)
{
	InitWindow(argc, argv);

	initShaders();
	initData();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();
}

void InitWindow(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
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
	printGlError("before glewInit");
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();
	if (GLEW_OK != glewInitResult) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		cerr << glewGetErrorString(glewInitResult) << endl;
		exit(EXIT_FAILURE);
	}

	glutDisplayFunc(display);
}

void initData() {
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][4] = {
		{ -0.90f, -0.90f, 0.0f, 1.0f}, // Triangle 1
		{  0.85f, -0.90f, 0.0f, 1.0f},
		{ -0.90f,  0.85f, 0.0f, 1.0f},
		{  0.90f, -0.85f, 0.0f, 1.0f}, // Triangle 2
		{  0.90f,  0.90f, 0.0f, 1.0f},
		{ -0.85f,  0.90f, 0.0f, 1.0f}
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
				 vertices, GL_STATIC_DRAW);
}

void initShaders() {
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"}
	};

	GLuint program = LoadShaders(2, shaders);
	glUseProgram(program);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT,
						  GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}

void printGlError(string title) {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		cerr << "Error: " << title << ": " << gluErrorString(error) << endl;
	} else {
		cout << title <<": ingen error" << endl;
	}
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

uint CreateShader(string filename, GLenum shaderType) {
	string filepath = "shaders/" + filename;
	string strShader = readlines(filepath);
	const char* cShader = strShader.c_str();

	GLuint shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &cShader, NULL);
	glCompileShader(shaderId);
	return shaderId;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glFlush();
	printGlError("display");
}
