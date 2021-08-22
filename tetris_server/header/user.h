#pragma once
#include <string>

using namespace std;

class User {
private:
	string name;	// id
	int win, draw, lose;	// multi
	int maxScore;	// single
public:
	User(string name) :User(name, 0, 0, 0, 0) {};
	User(string name, int win, int draw, int lose, int maxScore) :name(name), win(win), draw(draw), lose(lose), maxScore(maxScore) {};
	string getName() const {
		return name;
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
