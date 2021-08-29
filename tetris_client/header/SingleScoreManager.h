#pragma once
#include <algorithm>
#include <vector>
#include "singleScoreDao.h"
#include "singleScore.h"

using namespace std;

class SingleScoreManager {
public:
	SingleScoreDao* dao;
	vector<SingleScore> data;
public:
	SingleScoreManager(SingleScoreDao* dao) : dao(dao) {
		data = dao->getAllObjects();
		
	};
	
	void insert(SingleScore object) {
		int insertIdx = lower_bound(data.begin(), data.end(), object) - data.begin();	// ������ 1�� ���� ��쿡 ���� ���Ѽ��� ���Ѵ�.
		data.insert(data.begin()+insertIdx, object);
		dao->setAllObjects(data);
	}
	void printAllObject() {

		for (int i = 0; i < data.size(); i++) {
			cout << data[i].getName() << endl;
		}
	}
};