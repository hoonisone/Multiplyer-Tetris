#pragma once
#pragma warning(disable:4996)
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FileManager {
private:
	string fileName;
public:
	FileManager(string fileName) : fileName(fileName) {}

	vector<string> readLines() {
		ifstream openFile(fileName.data());
		vector<string> lines;
		string line;

		if (openFile.is_open()) {
			while (getline(openFile, line)) {
				lines.push_back(line);

			}

		}

		return lines;
	}

	void writeLines(vector<string> lines) {
		ofstream openFile(fileName.data());
		if (openFile.is_open()) {
			for (int i = 0; i < lines.size(); i++) {
				openFile << lines[i] << "\n";
			}
		}
	}
};


