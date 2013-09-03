#include "vertices.h"

using namespace std;


vector<VertexData> getVertices(int cols, int rows) {
	srand(time(NULL));
	vector<VertexData> vec;
	for (int y = 0; y < rows-1; y++) {
		for (int x = 0; x < cols-1; x++) {
			Vertex sw = getVertex(x, y);
			Vertex se = getVertex(x+1, y);
			Vertex ne = getVertex(x+1, y+1);
			Vertex nw = getVertex(x, y+1);
			Vertex square[] = {se, sw, nw, se, nw, ne};
			for (int i = 0; i < 6; i++) {
				VertexData data;
				data.position = square[i];
				data.color = getColor();
				vec.push_back(data);
			}

		}
	}
	return vec;
}

Vertex getVertex(int x, int y) {
	Vertex v;
	int d = 2;
	v.x = float(x)/d;
	v.y = float(y)/d;
	v.z = func(x, y)/d;
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

GLfloat func(int x, int y) {
	return 0.0;
}

// Color getColor() {
// 	GLubyte *color = new GLubyte[4];
// 	for (int i = 0; i < 4; i++) {
// 		color[i] = rand() % 255;
// 	}
// 	return color;
// }

// void printVertices(VertexData* vertices, int size) {
// 	for (int i = 0; i < size; i++) {
// 		VertexData *data = &vertices[i];
// 		printVertexData(data);
// 	}
// }

// void printVertex(Vertex v) {
// 	for (int i = 0; i < 3; i++) {
// 		cout << v[i] << ", ";
// 	}
// 	cout << endl;
// }

void printVertexData(const vector<VertexData> &data) {
	for (uint i = 0; i < data.size(); ++i) {
		GLfloat x = data[i].position.x;
		GLfloat y = data[i].position.y;
		GLfloat z = data[i].position.z;
		printf("%.2f , %.2f , %.2f\n", x, y, z);

		if (i % 3 == 2) {
			cout << endl;
		}
	}
}