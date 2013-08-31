#include "triangles.h"

using namespace std;


enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VaoId;

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

ShaderInfo *shaders;
GLint vScaleId;

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
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();
	if (GLEW_OK != glewInitResult) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		cerr << glewGetErrorString(glewInitResult) << endl;
		exit(EXIT_FAILURE);
	}

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
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
	glVertexAttribPointer(vPosition, 4, GL_FLOAT,
						  GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}

void initShaders() {
	ShaderInfo s[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"}
	};
	shaders = s;

	GLuint program = LoadShaders(2, shaders);
	glUseProgram(program);
	vScaleId = glGetUniformLocation(program, "vScale");
	glUniform1f(vScaleId, 2.0);


	error("uniformloc");
	cout << "uniform-index: " << vScaleId << endl;
}

void error(string title) {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		cerr << "Error-" << title << ": " << gluErrorString(err) << endl;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
}


void mouse(int button, int state, int x, int y) {

}

void motion(int x, int y) {;
		float scale = x/512.0;
		glUniform1f(vScaleId, scale);
}