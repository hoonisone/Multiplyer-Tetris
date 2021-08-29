#pragma once
#include "FileManager.h"

template <typename T>
class Dao {
protected:
	FileManager* fm;
	virtual T parse(string text) = 0;
	virtual string toString(T object) = 0;
public:
	Dao(FileManager* fm) : fm(fm) {};

	vector<T> getAllObjects()  {
		vector<string> lines = fm->readLines();

		vector<T> singleScores;

		for (int i = 0; i < lines.size(); i++) {
			singleScores.push_back(parse(lines[i]));
		}
		return singleScores;
	}

	void setAllObjects(vector<T> objects)  {
		vector<string> lines;
		for (int i = 0; i < objects.size(); i++) {
			lines.push_back(toString(objects[i]));
		}
		fm->writeLines(lines);
	}

	~Dao() {
		delete fm;
	}
};