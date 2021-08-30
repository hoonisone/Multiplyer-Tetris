#pragma once
#include <string>
#include "SingleUser.h"
#include "FileManager.h"
#include "string+.h"
#include "Dao.h"

using namespace std;

class SingleUserDao :public Dao<SingleUser> {
private:
	SingleUser parse(string userInforString)override {
		vector<string> tokens = split(userInforString, "/");
		string name = tokens[0];
		int win = stoi(tokens[1]);
		int draw = stoi(tokens[2]);
		int lose = stoi(tokens[3]);
		int maxScore = stoi(tokens[4]);
		return SingleUser(name, win, draw, lose, maxScore);
	}
	string toString(SingleUser user) override {
		char arr[100];
		string name = user.getName();
		int win = user.getWin();
		int draw = user.getDraw();
		int lose = user.getLose();
		int maxScore = user.getMaxScore();
		sprintf(arr, "%s/%d/%d/%d/%d", name.c_str(), win, draw, lose, maxScore);
		return string(arr);
	}
public:
	SingleUserDao(FileManager* fm) : Dao(fm) {}

	//vector<User> getAllObjects() override {
	//	vector<User> userList;
	//	vector<string> lines = fm->readLines();
	//	for (int i = 0; i < lines.size(); i++) {
	//		userList.push_back(parse(lines[i]));
	//	}
	//	return userList;
	//}
	//void setAllObjects(vector<User> userList) override {
	//	vector<string> lines;
	//	for (int i = 0; i < userList.size(); i++) {
	//		lines.push_back(toString(userList[i]));
	//	}
	//	fm->writeLines(lines);
	//}
	~SingleUserDao() {
		delete fm;
	}
};