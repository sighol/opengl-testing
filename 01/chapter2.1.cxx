#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

#include "readfile.h"

// Denne sørger for at vi slipper å inkludere <GL/gl.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Chapter 2"

using namespace std;

int CurrentWidth = 800,
	CurrentHeight = 600,
	WindowHandle = 0;

unsigned FrameCount = 0;

GLuint
	VertexShaderId,
	FragmentShaderId,
	ProgramId,
	VaoId,
	VboId,
	ColorBufferId;

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void printGlError(string title);

void printGlError(string title) {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		cerr << "Error: " << title << gluErrorString(error) << endl;
	} else {
		cout << "ingen error" << endl;
	}
}

// Fra Chapter 2
void Cleanup(void);
void CreateVBO(void);
void DestroyVBO(void);
void CreateShaders(void);
void DestroyShaders(void);



int main(int argc, char* argv[])
{
	Initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[])
{
	InitWindow(argc, argv);

	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(GlewInitResult)
		);
		exit(EXIT_FAILURE);
	}

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);


	// CreateShaders();
	// CreateVBO();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[])
{
	// Må være den første glut-funksjonen som blir kalt.
	glutInit(&argc, argv);

	// Selvforklarende
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Returner fra glutMainLoop når du trykker på X.
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	// Selvforklarende
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	/*
	Definerer hva slags opengl-context vi ønsker  GLUT_DEPTH skrur på bruken av
	**depth buffer**. Dybdebufferet inneholder  z-høyden til hver piksel som
	rendres til skjermen. Dette er viktig for å passe på at ting ikke overlapper
	hverandre når de ikke skal og at ting som er lenger vekk legges bak nærmere
	ting.

	GLUT_DOUBLE er et flagg som skrur på bruken av dobbelt-bufring, noe som
	reduserer bildeflirking (image flickering).

	GLUT_RGBA gjør det mulig å bruke vanlig red green blue alpha-verdier
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if(WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);

	// Denne kjører når opengl vanligvis ikke gjør noe.
	glutIdleFunc(IdleFunction);

	// glutTimerFunc(int msTilFunksjonenKalles, funksjon, argument til funksjonen);
	glutTimerFunc(0, TimerFunction, 0);

	glutCloseFunc(Cleanup);
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
	++FrameCount;
	// Setter alt til ClearColor og fjerner all piksel-dybde-data
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
	glutPostRedisplay();

}

void IdleFunction(void) {
	glutPostRedisplay();
}

void TimerFunction(int Value) {
	if (0 != Value) {
		char* TempString = (char*)
				malloc(512 + strlen(WINDOW_TITLE_PREFIX));

		sprintf(
			TempString,
			"%s: %d Frames Per Second @ %d x %d",
			WINDOW_TITLE_PREFIX,
			FrameCount * 4,
			CurrentWidth,
			CurrentHeight
		);

		glutSetWindowTitle(TempString);
		free(TempString);
	} else {
	}

	FrameCount = 0;
	glutTimerFunc(250, TimerFunction, 1);
}

void Cleanup(void) {
	DestroyShaders();
	DestroyVBO();
}

void CreateVBO(void) {
	GLfloat Vertices[] = {
		-0.8f, -0.8f, 0.0f, 1.0f,
		 0.0f,  0.8f, 0.0f, 1.0f,
		 0.8f, -0.8f, 0.0f, 1.0f
	};

	GLfloat Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	// verdien av glGetError() brukes ikke, men errorene nullstilles slik at de
	// kan hentes senere
	GLenum ErrorCheckValue = glGetError();

	// glGenVertexArrays(GLsizei n, GLuint *arrays). n beskriver antall vertex
	// arrays som skal genereres. Etter at de er generert settes en peker til
	// alle vertexene i arrays. I vårt tilfelle har vi bare en vertex, slik at
	// vi kan bruke en enkel uint til å holde på tallet vårt.
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	// void glGenBuffers(GLSizei n, GLuint* buffers); Denne genererer bufferene.
	// Funksjonen fungerer akkurat på samme måte som glGenVertexArrays med tanke
	// på argumenter.
	glGenBuffers(1, &VboId);
	// GL_ARRAY_BUFFER viser at dataene som skal settes inn inneholder vertex
	// attributter. glBindBuffer setter også dette bufferet som *current* slik
	// at følgende buffer-relaterte operasjoner.
	glBindBuffer(GL_ARRAY_BUFFER, VboId);

	// void glBufferData(
	//     GLenum target,
	//     GLsizeiptr size,
	//     GLvoid* data,
	//     GLenum usage
	// );
	//
	// usage  ble satt til GL_STATIC_DRAW som betyr at det ikke vil bli endret
	// (static).
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// Denne viser OpenGL hva slags typer data vi har puttet inn.
	// void glVertexAttribPointer(
	//     GLuint index,
	//     GLint size,
	//     GLenum type,
	//     GLboolean normalized,
	//     GLsizei stride,
	//     const GLvoid* pointer
	// );

	// Tilbyr nok metadata til at openGL vet hvordan den skal bruke rådataen.
	// Indexen samsvarer med location= som er beskrevet i shaderen. Med andre
	// ord: Vi sier nå at in_Position (i shaderen) settes til det bufferet vi
	// satt inn. size representerer her ikke størrelse i bytes men antall
	// komponenter. size = 4 siden vi har 4 komponenter: x, y, z, w. Hver
	// komponent er av type GL_FLOAT. Hvis normalized er satt til GL_TRUE vil en
	// int som sendes inn bli normalisert fra [0, 255] => [0.0, 1,0]. Dette er
	// altså en kjapp måte å konverterer fra int til float. (?)
	// Stride og pointer settes til 0 siden vi har sekvensielle data.
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// indexen som sender er den samme som i glVertexAttribPointer
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create a VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}

}

void DestroyVBO(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void CreateShaders(void)
{
	printGlError("createShaders");

	string strVertexShader = readlines("tut2-vertex-shader.glsl");
	string strFragmentShader = readlines("tut2-fragment-shader.glsl");

	const char* cVertexShader = strVertexShader.c_str();
	const char* cFragmentShader = strFragmentShader.c_str();

	GLenum ErrorCheckValue = glGetError();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	// void glShaderSource(
	//     GLuint shader,
	//     GLsizei count, Hvor mange strenger vi har. vi har 1.
	//     const GLchar** string, array med strenger
	//     const GLint * length. Vi kan sette denne til NULL hvis strengene
	//                           termineres med \0
	// );

	// Denne funksjonene kopierer shader-koden
	glShaderSource(VertexShaderId, 1, &cVertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &cFragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	// Dette blir nesten som et program som kjører på GPU.
	ProgramId = glCreateProgram();
		glAttachShader(ProgramId, VertexShaderId);
		glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);

	// Gjør programmet current. Dette programmet er aktivt helt til glUseProgram
	// blir kallt med et annet shaderprogram.
	glUseProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void DestroyShaders(void)
{
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}
