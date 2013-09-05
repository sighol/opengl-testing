#include "vertices.h"

#include <cmath>
#include <cfloat>

using namespace std;


vector<VertexData> getVertices(Dimension dim, int cols, int rows, float* minZ, float* maxZ) {
	*minZ = FLT_MAX;
	*maxZ = FLT_MIN;
	srand(time(NULL));
	vector<VertexData> vec;
	GLfloat xStep = dim.width / cols;
	GLfloat yStep = dim.width / rows;
	for (int j = 0; j < rows-1; j++) {
		for (int i = 0; i < cols-1; i++) {
			GLfloat x =	i * xStep + dim.x;
			GLfloat y = j * yStep + dim.y;
			Vertex sw = getVertex(x, y);
			Vertex se = getVertex(x+xStep, y);
			Vertex ne = getVertex(x+xStep, y+yStep);
			Vertex nw = getVertex(x, y+yStep);
			Vertex square[] = {sw, se, ne, sw, ne, nw};
			for (int i = 0; i < 6; i++) {
				if (square[i].z > *maxZ) {
					*maxZ = square[i].z;
				}
				if (square[i].z < *minZ) {
					*minZ = square[i].z;
				}
				VertexData data;
				data.position = square[i];
				data.color = getColor();
				vec.push_back(data);
			}
		}
	}
	return vec;
}

Vertex getVertex(GLfloat x, GLfloat y) {
	Vertex v;
	v.x = float(x);
	v.y = float(y);
	v.z = func(x, y);
	v.w = 1.0;
	return v;
}

Color getColor() {
	Color c;
	c.r = rand() % 255;
	c.g = rand() % 255;
	c.b = rand() % 255;
	c.a = rand() % 255;
	return c;
}

GLfloat func(GLfloat x, GLfloat y) {
	return x*x - y*y;
}

void printVertices(const vector<VertexData> &data) {
	for (GLuint i = 0; i < data.size(); ++i) {
		GLfloat x = data[i].position.x;
		GLfloat y = data[i].position.y;
		GLfloat z = data[i].position.z;
		printf("%.2f , %.2f , %.2f\n", x, y, z);

		if (i % 3 == 2) {
			cout << endl;
		}
	}
}