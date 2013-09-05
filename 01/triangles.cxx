#include "triangles.h"

using namespace std;


enum vertexArrayIDs {Triangles, numVertexArrays};
enum bufferIDs {ArrayBuffer, numBuffers};

struct LayoutState {
	GLint position = 0;
	GLint color = 1;
};

LayoutState layout;

GLuint vertexArrays[numVertexArrays];
GLuint Buffers[numBuffers];

GLuint vertexCount;

ShaderInfo *shaders;

GLint vRotationX, vRotationY, vIsGrid;

int main(int argc, char **argv)
{
	InitWindow(argc, argv);

	initShaders();
	initDynamicData();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

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

	GLint WindowHandle = glutCreateWindow(argv[0]);

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

void initDynamicData() {
	glGenVertexArrays(numVertexArrays, vertexArrays);
	glBindVertexArray(vertexArrays[Triangles]);

	Dimension dim(-1, -1, 2, 2);
	vector<VertexData> vertices = getVertices(dim, 10, 10);

	vertexCount = vertices.size() * sizeof(VertexData);
	cout << vertices.size() << endl;

	glGenBuffers(numBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(layout.color, 4, GL_UNSIGNED_BYTE, GL_TRUE,
						  sizeof(VertexData), 0);
	error("layout.colorattribpointer");

	glVertexAttribPointer(layout.position, 4, GL_FLOAT, GL_FALSE,
						  sizeof(VertexData),
						  (GLvoid*)sizeof(Color));
	glEnableVertexAttribArray(layout.color);
	glEnableVertexAttribArray(layout.position);
	error("last");
}

void initShaders() {
	ShaderInfo s[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"}
	};
	shaders = s;

	GLuint program = LoadShaders(2, shaders);
	glUseProgram(program);

	vRotationX = glGetUniformLocation(program, "vRotationX");
	glUniform1i(vRotationX, 0);

	vRotationY = glGetUniformLocation(program, "vRotationY");
	glUniform1i(vRotationY, 0);

	vIsGrid = glGetUniformLocation(program, "vIsGrid");
	glUniform1i(vIsGrid, 0);

	error("uniformloc");
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

	glBindVertexArray(vertexArrays[Triangles]);

	glUniform1i(vIsGrid, 0);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glUniform1i(vIsGrid, 1);
	glDrawArrays(GL_LINES, 0, vertexCount);

	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
}

int xBase = 0, yBase = 0;
int pastDx = 0, pastDy = 0;
int dx = 0, dy = 0;
void mouse(int button, int state, int x, int y) {
	if (state == 0) {
		xBase = x;
		yBase = y;
	} else {
		pastDx = dx + pastDx;
		pastDy = dy + pastDy;
	}
}

void motion(int x, int y) {
	dx = (x - xBase);
	float rotationX = (dx + pastDx)/4;
	glUniform1i(vRotationX, rotationX);

	dy = (y - yBase);
	float rotationY = (dy + pastDy)/4;
	glUniform1i(vRotationY, rotationY);
}
