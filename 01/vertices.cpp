#include "vertices.h"

using namespace std;


vector<VertexData> getVertices(int cols, int rows) {
	srand(time(NULL));
	int m = max(cols, rows);
	vector<VertexData> vec;
	int row_center = rows/2;
	int col_center = cols/2;
	for (int y = 0; y < rows-1; y++) {
		for (int x = 0; x < cols-1; x++) {
			Vertex sw = getVertex(m, x-row_center, y-col_center);
			Vertex se = getVertex(m, x+1-row_center, y-col_center);
			Vertex ne = getVertex(m, x+1-row_center, y+1-col_center);
			Vertex nw = getVertex(m, x-row_center, y+1-col_center);
			Vertex square[] = {sw, se, ne, sw, ne, nw};
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

Vertex getVertex(int m, int x, int y) {
	Vertex v;
	int d = m/2;
	v.x = float(x)/d;
	v.y = float(y)/d;
	v.z = func(x, y)/(d*d);
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
	return x*y;
}

void printVertices(const vector<VertexData> &data) {
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