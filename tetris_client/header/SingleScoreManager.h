#pragma once

#include "singleScoreDao.h"
#include <vector>

using namespace std;
class SingleScoreManager {
private:
	SingleScoreDao* dao;
	vector<SingleScore> data;
public:
	SingleScoreManager(SingleScoreDao* dao) : dao(dao) {
		data = dao->getAllObjects();
	};
	
	void insert(SingleScore object) {

	}


};