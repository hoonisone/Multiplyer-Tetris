#pragma once

#include <string>

using namespace std;

class SingleScore {
private:
	string name;
	string date;
	long long score;

public:
	SingleScore(string name, string date, int score) : name(name), date(date), score(score) {};
	string getName() {
		return name;
	}
	string getDate() {
		return date;
	}
	long long getScore() {
		return score;
	}
	bool operator<(const SingleScore& target) { // �켱���� ���� �۴� -> ������ ���� -> ������ ����.
		return score > target.score;
	}
};