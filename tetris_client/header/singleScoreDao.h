#pragma once
#include "FileManager.h"
#include "singleScore.h"
#include "string+.h"
#include "Dao.h"

class SingleScoreDao : public Dao<SingleScore> {
private:
	FileManager* fm;
	SingleScore parse(string userInforString) override {
		vector<string> tokens = split(userInforString, "/");
		string name = tokens[0];
		string date = tokens[1];
		int score = stoi(tokens[2]);
		return SingleScore(name, date, score);
	}
	string toString(SingleScore object) override {
		char arr[100];
		string name = object.getName();
		string date = object.getDate();
		int score = object.getScore();
		sprintf(arr, "%s/%s/%d", name.c_str(), date.c_str(), score);
		return string(arr);
	}
public:
	SingleScoreDao(FileManager* fm) :Dao(fm) {};

	vector<SingleScore> getAllObjects() override {
		vector<string> lines = fm->readLines();
		vector<SingleScore> singleScores;
		for (int i = 0; i < lines.size(); i++) {
			singleScores.push_back(parse(lines[i]));
		}
		return singleScores;
	}

	void setAllObjects(vector<SingleScore> objects) override {
		vector<string> lines;
		for (int i = 0; i < objects.size(); i++) {
			lines.push_back(toString(objects[i]));
		}
		fm->writeLines(lines);
	}

	~SingleScoreDao() {
		delete fm;
	}

};