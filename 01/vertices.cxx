#include "triangles.h"

using namespace std;

typedef GLfloat* Vertex;
typedef GLubyte* Color;

VertexData* getVertices(int cols, int rows, int* size);
Vertex getVertex(int x, int y);
Color getColor();
void printVertices(VertexData* data, int size);
GLfloat func(int x, int y);

int main() {
	int rows = 2;
	int cols = 2;
	int size;
	VertexData* data = getVertices(cols, rows, &size);
	printVertices(data, size);
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

void printVertices(VertexData* data, int size) {
	cout << "printing: " << size <<  endl;
	for (int i = 0; i < size; i++) {
		VertexData *data = &data[i];
		cout << data->color << endl;
	}
	cout << "is done" << endl;
}