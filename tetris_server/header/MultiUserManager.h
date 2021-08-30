#pragma once
#include "MultiUserDao.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;
/*
�׻� ��� ������ �ֽ� ������ userList�� ��� �ִ�.
�Ź� userDao�� ���� ���Ͽ� ����Ѵ�.
*/
class UserManager {
private:
	MultiUserDao* userDao;
	map<string, int> userMap;	// userList�� idx�� �̸��� ���������� -> ���� Ž���� ����
	vector<MultiUser> userList;
	void updateFile() {
		userDao->setAllUsers(userList);
	}
public:
	UserManager(MultiUserDao* userDao) : userDao(userDao) {
		userList = userDao->getAllUsers();
		for (int i = 0; i < userList.size(); i++) {
			MultiUser& user = userList[i];
			userMap[user.getName()] = i;	// �̸��� �ε����� ���� ���´�.
		}
	}
	vector<string> getAllUserNames() const{
		vector<string> names;
		for (int i = 0; i < userList.size(); i++) {
			names.push_back(userList[i].getName());
		}
		return names;
	}
	bool nameExistCheck(string name) const {
		return userMap.find(name) == userMap.end();
	}
	bool objectExistCheck(MultiUser user) {
		return nameExistCheck(user.getName());
	}
	void insertUser(MultiUser user){
		if (!objectExistCheck(user)) {
			userList.push_back(user);
			userMap[user.getName()] = userList.size() - 1;
		}
	}
	void update(MultiUser user) {
		if (objectExistCheck(user)) {
			userList[userMap[user.getName()]] = user;
			updateFile();
		}
	}

};