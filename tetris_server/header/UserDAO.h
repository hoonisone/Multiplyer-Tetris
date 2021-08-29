#pragma once
#include <string>
#include "User.h"
#include "FileManager.h"
#include "string+.h"

using namespace std;

class UserDao {
private:
	FileManager* userFileManager;
	User parse(string userInforString) {
		vector<string> tokens = split(userInforString, "/");
		string name = tokens[0];
		string password = tokens[1];
		int win = stoi(tokens[2]);
		int draw = stoi(tokens[3]);
		int lose = stoi(tokens[4]);
		int maxScore = stoi(tokens[5]);
		return User(name, password, win, draw, lose, maxScore);
	}
	string toString(User user) {
		char arr[100];
		string name = user.getName();
		string password = user.getPassword();
		int win = user.getWin();
		int draw = user.getDraw();
		int lose = user.getLose();
		int maxScore = user.getMaxScore();
		sprintf(arr, "%s/%s/%d/%d/%d/%d", name.c_str(), password.c_str(), win, draw, lose, maxScore);
		return string(arr);
	}
public:
	UserDao(FileManager* userFileManager) : userFileManager(userFileManager) {}

	vector<User> getAllUsers() {
		vector<User> userList;
		vector<string> lines = userFileManager->readLines();
		for (int i = 0; i < lines.size(); i++) {
			userList.push_back(parse(lines[i]));
		}
		return userList;
	}
	void setAllUsers(vector<User> userList) {
		vector<string> lines;
		for (int i = 0; i < userList.size(); i++) {
			lines.push_back(toString(userList[i]));
		}
		userFileManager->writeLines(lines);
	}
	~UserDao() {
		delete userFileManager;
	}
};