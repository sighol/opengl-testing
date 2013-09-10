#include "triangles.h"

using namespace std;


enum vertexArrayIDs {Triangles, numVertexArrays};
enum bufferIDs {ArrayBuffer, numBuffers};

struct LayoutState {
	LayoutState():position(0), color(1){}
	GLint position;
	GLint color;
};

struct UniformState {
	GLint xRotation, yRotation, isGrid, zoom, maxZ, minZ;
};

UniformState uniforms;

LayoutState layout;

GLuint vertexArrays[numVertexArrays];
GLuint buffers[numBuffers];

GLuint vertexSize, vertexByteSize;

GLint frameCount = 0;

struct View {
	View():rows(10),cols(10),dim(Dimension(-1, -1, 2, 2)),width(600),height(400){}
	GLint rows;
	GLint cols;
	Dimension dim;
	GLint width;
	GLint height;
	float minZ;
	float maxZ;
};

View view;

void initGL();
void initGlut(int argc, char **argv);
void initCallbacks();
void timer(int);
void resize(int, int);


int main(int argc, char **argv){
	initGlut(argc, argv);
	initShaders();
	initDynamicData();
	initGL();
	initCallbacks();
	glutMainLoop();
}

void initCallbacks() {
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(resize);
}

void initGL() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void initGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	glutInitWindowSize(view.width, view.height);
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
}

void initDynamicData() {
	glGenVertexArrays(numVertexArrays, vertexArrays);
	glBindVertexArray(vertexArrays[Triangles]);

	vector<VertexData> vertices = getVertices(view.dim, view.cols, view.rows, &view.minZ, &view.maxZ);

	cout << "min: " << view.minZ << ", max: " << view.maxZ << endl;

	glUniform1f(uniforms.maxZ, view.maxZ);
	glUniform1f(uniforms.minZ, view.minZ);

	vertexSize = vertices.size();
	vertexByteSize = vertexSize * sizeof(VertexData);
	cout << vertices.size() << endl;

	glGenBuffers(numBuffers, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, vertexByteSize, &vertices[0], GL_STATIC_DRAW);
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
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"}
	};

	GLuint program = LoadShaders(2, shaders);
	glUseProgram(program);

	initUniforms(program);
}

void initUniforms(GLuint program) {
	uniforms.xRotation = glGetUniformLocation(program, "vRotationX");
	uniforms.yRotation = glGetUniformLocation(program, "vRotationY");
	uniforms.isGrid = glGetUniformLocation(program, "vIsGrid");
	uniforms.maxZ = glGetUniformLocation(program, "vMaxZ");
	uniforms.minZ = glGetUniformLocation(program, "vMinZ");

	glUniform1i(uniforms.xRotation, 0);
	glUniform1i(uniforms.yRotation, 0);
	glUniform1i(uniforms.isGrid, 0);
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
	frameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vertexArrays[Triangles]);

	glUniform1i(uniforms.isGrid, 0);
	glDrawArrays(GL_TRIANGLES, 0, vertexSize);
	glUniform1i(uniforms.isGrid, 1);

	glDrawArrays(GL_LINES, 0, vertexSize);

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
	glUniform1i(uniforms.xRotation, rotationX);

	dy = (y - yBase);
	float rotationY = (dy + pastDy)/4;
	glUniform1i(uniforms.yRotation, rotationY);
}

void resize(int width, int height) {
	view.width = width;
	view.height = height;
	glViewport(0, 0, width, height);
}

void timer(int Value) {
	if (0 != Value) {
		char *tempString = (char*)
				malloc(512 * sizeof(char));

		std::stringstream ss;
		ss << "Surf: " << frameCount * 4 << "FPS: @ " << view.width << " x " << view.height;

		glutSetWindowTitle(ss.str().c_str());
		free(tempString);
	}
	frameCount = 0;
	glutTimerFunc(250, timer, 1);
}