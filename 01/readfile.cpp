#include "readfile.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


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