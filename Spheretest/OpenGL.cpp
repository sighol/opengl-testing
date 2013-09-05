#include "OpenGL.h"

string readlines(string filepath) {
	ifstream file;
	file.open(filepath);
	stringstream ss;
	string line;
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			ss << line << endl;
		}
	}
	file.close();
	return ss.str();
}

void OpenGL::start()
{
	glutMainLoop();
}
void OpenGL::startDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGL::endDraw()
{
	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
}
void OpenGL::init()
{
	char *myargv [1];
	int myargc=1;
	myargv [0]= _strdup ("OpenGL");
	glutInit(&myargc, myargv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);

	glutInitWindowSize(1280, 720);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	auto WindowHandle = glutCreateWindow("OpenGL");
	glutFullScreen();

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
	
	glEnable(GL_DEPTH_TEST);
	programId = glCreateProgram();
}

void OpenGL::CompileProgram() {
	glLinkProgram(programId);
	
	GLint status;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	
   if(status == false){
		int infologLength =  0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infologLength);
		GLchar* buffer = new char[infologLength];
		GLsizei charsWritten = 0;
		std::cout << "Error: " << std::endl;
		glGetProgramInfoLog(programId, infologLength, &charsWritten, buffer);
		std::cout << buffer << std::endl;
   }

	glUseProgram(programId);
}
void OpenGL::setUniform(GLchar* name, float value)
{
	if ( uniforms.find(name) == uniforms.end() )
		uniforms[name] = glGetUniformLocation(programId, name);
	glUniform1f(uniforms[name], value);
}

void OpenGL::AddShader(string filename, GLenum shaderType) {
	string filepath = "shaders/" + filename;
	string strShader = readlines(filepath);
	const char* cShader = strShader.c_str();

	GLuint shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &cShader, NULL);
	glCompileShader(shaderId);
	printShaderError(shaderId, filename);
	glAttachShader(programId, shaderId);
}

void OpenGL::printShaderError(GLuint shaderId, string filename) {
	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Compilation error in shader %s: %s\n", filename.c_str(), strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
}

int OpenGL::addVertexBuffer(GLuint type, std::vector<Vertex> vertices)
{
	// Create and bind VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create and binf a BufferObject for vertex data
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Copy data into bufferobject
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		&vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(Attribute::Position);
	glVertexAttribPointer(Attribute::Position, 4, GL_FLOAT,
		GL_FALSE, 0, 0);

	VertexBufferData vbd;
	vbd.type = type;
	vbd.VAO = VAO;
	vbd.vertices = vertices.size();
	vertexBuffers[VAO] = vbd;

	return VAO;
}
void OpenGL::drawVertexBuffer(int num)
{
	VertexBufferData vbd = vertexBuffers[num];
	glBindVertexArray(vbd.VAO);
	glDrawArrays(vbd.type, 0, vbd.vertices);
}

void OpenGL::error(string title) {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		cerr << "Error-" << title << ": " << gluErrorString(err) << endl;
	}
}