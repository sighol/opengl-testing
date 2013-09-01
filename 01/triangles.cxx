#include "triangles.h"

using namespace std;


enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0, vColor=1};

GLuint VaoId;

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

ShaderInfo *shaders;

GLint vScaleId;
GLint vRotationX, vRotationY;

const GLuint NumVertices = 18;

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

void printVertex(VertexData* vertices, int size);

void initData() {
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	int size;
	VertexData *vertices = getVertices(10, 10, &size);
	int VertexDataSize = 4 *sizeof(GLubyte) + 3*sizeof(GLfloat);

	int totalSize = VertexDataSize * size;
	printVertex(vertices, size);

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, totalSize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE,
						  VertexDataSize, 0);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE,
						  VertexDataSize,
						  BUFFER_OFFSET(4*sizeof(GLubyte)));
	glEnableVertexAttribArray(vColor);
	glEnableVertexAttribArray(vPosition);
}

void printVertex(VertexData* vertices, int size) {
	int typeSize = 4 * sizeof(GLubyte) + 3*sizeof(GLfloat);
	cerr << typeSize << " og " << sizeof(vertices) << endl;
	for (int i = 0; i < size; i++) {
		cout << vertices[i] << endl;
	}

	exit(0);
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

	vRotationX = glGetUniformLocation(program, "vRotationX");
	glUniform1i(vRotationX, 0);

	vRotationY = glGetUniformLocation(program, "vRotationY");
	glUniform1i(vRotationY, 0);

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

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

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
		printf("xbase: %d, yBase:%d\n", x, y);
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
	printf("x: %d, y: %d\n", dx, dy);
}

GLfloat func(int x, int y) {
	return x + y;
}

typedef GLfloat* Vertex;
typedef GLubyte* Color;

Vertex getVertex(int x, int y) {
	GLfloat* vertex = new GLfloat[3];
	vertex[0] = float(x);
	vertex[1] = float(y);
	vertex[2] = func(x, y);
	return vertex;
}

Color getColor() {
	GLubyte *color = new GLubyte[4];
	for (int i = 0; i < 4; i++) {
		color[i] = rand() % 255;
	}
	return color;
}

VertexData* getVertices(int cols, int rows, int* size) {
	*size = (cols-1) * (rows-1) * 6;
	VertexData *vertices = new VertexData[*size];
	int n = 0;
	for (int y = 0; y < rows-1; y++) {
		for (int x = 0; x < cols-1; x++) {
			Vertex sw = getVertex(x, y);
			Vertex se = getVertex(x+1, y);
			Vertex ne = getVertex(x+1, y+1);
			Vertex nw = getVertex(x, y+1);
			Vertex square[] = {se, sw, nw, se, nw, ne};
			for (int i = 0; i < 6; i++) {
				VertexData *data = new VertexData;
				data->position = square[i];
				data->color = getColor();
				vertices[n + i] = *data;
			}
			n += 6;
		}
	}
	return vertices;
}

