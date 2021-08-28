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

	virtual vector<T> getAllObjects() = 0;
	virtual void setAllObjects(vector<T> objects) = 0;

	~Dao() {
		delete fm;
	}
};