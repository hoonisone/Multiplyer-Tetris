#pragma once
#include "SingleUserDao.h"
#include <string>
#include <vector>

using namespace std;
/*
항상 모든 유저의 최신 정보를 userList에 담고 있다.
매번 userDao를 통해 파일에 기록한다.
*/
class SingleUserManager {
private:
	SingleUserDao* userDao;
	vector<SingleUser> userList;
public:
	SingleUserManager(SingleUserDao* userDao) : userDao(userDao) {
		userList = userDao->getAllObjects();
	}
	vector<string> getAllUserNames() {
		vector<string> names;
		for (int i = 0; i < userList.size(); i++) {
			names.push_back(userList[i].getName());
		}
		return names;
	}
};