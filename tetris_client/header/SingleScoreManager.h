#pragma once
#include <algorithm>
#include <vector>
#include "singleScoreDao.h"
#include "singleScore.h"

using namespace std;
class Test {
public:
	int a;
	Test(int a) : a(a) {  };

	bool operator<(const Test& b) {
		return a > b.a;
	}
};

class SingleScoreManager {
public:
	SingleScoreDao* dao;
	vector<SingleScore> data;
public:
	SingleScoreManager(SingleScoreDao* dao) : dao(dao) {
		data = dao->getAllObjects();
		
	};
	
	void insert(SingleScore object) {
		int insertIdx = lower_bound(data.begin(), data.end(), object) - data.begin();	// 점수가 1점 낮은 경우에 대해 상한선을 구한다.
		data.insert(data.begin()+insertIdx, object);
	}
	void printAllObject() {

		for (int i = 0; i < data.size(); i++) {
			cout << data[i].getName() << endl;
		}
	}
};