#include "vertices.h"

using namespace std;


VertexData* getVertices(int cols, int rows, uint* size) {
	*size = (cols-1) * (rows-1)*6;
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
				vertices[n].color = getColor();
				vertices[n].position = square[i];
				n++;
			}

		}
	}
	return vertices;
}

Vertex getVertex(int x, int y) {
	GLfloat* vertex = new GLfloat[3];
	vertex[0] = float(x);
	vertex[1] = float(y);
	vertex[2] = func(x, y);
	return vertex;
}

GLfloat func(int x, int y) {
	return x + y;
}

Color getColor() {
	GLubyte *color = new GLubyte[4];
	for (int i = 0; i < 4; i++) {
		color[i] = rand() % 255;
	}
	return color;
}

void printVertices(VertexData* vertices, int size) {
	for (int i = 0; i < size; i++) {
		VertexData *data = &vertices[i];
		printVertexData(data);
	}
}

void printVertex(Vertex v) {
	for (int i = 0; i < 3; i++) {
		cout << v[i] << ", ";
	}
	cout << endl;
}

void printVertexData(VertexData *vd) {
	cout << vd << " - ";
	cout << "Pos: ";
	for (int i = 0; i < 3; i++) {
		cout << vd->position[i] << ", ";
	}
	cout << "Color: ";
	for (int i = 0; i < 4; i++) {
		cout << (int)vd->color[i] << ", ";
	}
	cout << endl;
}