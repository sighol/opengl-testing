#include "OpenGL.h"

std::vector<Vertex> createSphere(float rad, int rings, int sectors);
void display();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

int xBase = 0, yBase = 0;
int pastDx = 0, pastDy = 0;
int dx = 0, dy = 0;

OpenGL ogl;
int triangle;

int main()
{
	ogl.init();

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	ogl.AddShader("triangles.vert", GL_VERTEX_SHADER);
	ogl.AddShader("triangles.frag", GL_FRAGMENT_SHADER);
	ogl.AddShader("triangles.geom", GL_GEOMETRY_SHADER);
	ogl.CompileProgram();
	
	auto triangles = createSphere(0.7, 100, 100);
	triangle = ogl.addVertexBuffer(GL_TRIANGLES, triangles);

	ogl.start();
}

void display()
{
	static float time = 0;
	time += 0.01f;

	ogl.startDraw();
	ogl.setUniform("time", time);
	ogl.drawVertexBuffer(triangle);
	ogl.endDraw();
}

void mouse(int button, int state, int x, int y)
{
	glutExit();
}

void motion(int x, int y)
{
}

std::vector<Vertex> createSphere(float rad, int rings, int sectors)
{
	std::vector<Vertex> vertices;

	float pi = 3.1415;
	float deltaTheta = pi/(rings-1);
	float deltaPhi = 2*pi/sectors;
	for(int ring = 0; ring <= rings; ring++){ //move to a new z - offset 
		float theta = ring*deltaTheta;
		for(int point = 0; point <= sectors; point++){ // draw a ring
			float phi = (point+1)*deltaPhi;
			float x = sin(theta) * cos(phi);
			float y = sin(theta) * sin(phi);
			float z = cos(theta);
			vertices.push_back(Vertex(z*rad, x*rad, y*rad));
		}
	}

	std::vector<Vertex> triangles;
	for(int r = 0; r < rings; r++)
		for(int s = 0; s < sectors; s++) {
                triangles.push_back(vertices[r * sectors + s]);
                triangles.push_back(vertices[r * sectors + (s+1)]);
                triangles.push_back(vertices[(r+1) * sectors + (s+1)]);
				
                triangles.push_back(vertices[r * sectors + s]);
                triangles.push_back(vertices[(r+1) * sectors + (s+1)]);
                triangles.push_back(vertices[(r+1) * sectors + s]);
        }

	return triangles;
}
