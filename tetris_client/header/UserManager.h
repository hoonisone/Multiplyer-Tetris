#pragma once
#include "UserDao.h"
#include <string>
#include <vector>

using namespace std;
/*
�׻� ��� ������ �ֽ� ������ userList�� ��� �ִ�.
�Ź� userDao�� ���� ���Ͽ� ����Ѵ�.
*/
class UserManager {
private:
	UserDao* userDao;
	vector<User> userList;
public:
	UserManager(UserDao* userDao) : userDao(userDao) {
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