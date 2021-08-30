#pragma once
#include <string>

using namespace std;

class SingleUser {
private:
	string name;	// id
	int win, draw, lose;	// multi
	int maxScore;	// single
public:
	SingleUser(string name, int win, int draw, int lose, int maxScore) :name(name), win(win), draw(draw), lose(lose), maxScore(maxScore) {};
	string getName() {
		return name;
	}
	int getWin() {
		return win;
	}
	int getDraw() {
		return draw;
	}
	int getLose() {
		return lose;
	}
	int getMaxScore() {
		return maxScore;
	}
};
