#pragma once
#include <string>

using namespace std;

class MultiUser {
private:
	string name;	// id
	string password;
	int win, draw, lose;	// multi
	int maxScore;	// single
public:
	MultiUser(string name, string password) :MultiUser(name, password, 0, 0, 0, 0) {};
	MultiUser(string name, string password, int win, int draw, int lose, int maxScore) :name(name), password(password), win(win), draw(draw), lose(lose), maxScore(maxScore) {};
	string getName() const {
		return name;
	}
	string getPassword() {
		return password;
	}
	int getWin() const {
		return win;
	}
	int getDraw() const {
		return draw;
	}
	int getLose() const {
		return lose;
	}
	int getMaxScore() const {
		return maxScore;
	}
	int addWin() {
		win++;
	}
	int addDraw() {
		draw++;
	}
	int addLose() {
		lose++;
	}
	int setMaxScore(int maxScore) {
		this->maxScore = maxScore;
	}
};
