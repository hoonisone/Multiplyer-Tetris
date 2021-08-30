#pragma once
#include "SingleUserDao.h"
#include <string>
#include <vector>

using namespace std;
/*
�׻� ��� ������ �ֽ� ������ userList�� ��� �ִ�.
�Ź� userDao�� ���� ���Ͽ� ����Ѵ�.
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