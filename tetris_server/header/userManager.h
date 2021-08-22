#pragma once
#include "UserDao.h"
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
	UserDao* userDao;
	map<string, int> userMap;	// userList�� idx�� �̸��� ���������� -> ���� Ž���� ����
	vector<User> userList;
	void updateFile() {
		userDao->setAllUsers(userList);
	}
public:
	UserManager(UserDao* userDao) : userDao(userDao) {
		userList = userDao->getAllUsers();
		for (int i = 0; i < userList.size(); i++) {
			User& user = userList[i];
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
	bool objectExistCheck(User user) {
		return nameExistCheck(user.getName());
	}
	void createUser(User user){
		if (!objectExistCheck(user)) {
			userList.push_back(user);
			userMap[user.getName()] = userList.size() - 1;
		}
	}
	void update(User user) {
		if (objectExistCheck(user)) {
			userList[userMap[user.getName()]] = user;
			updateFile();
		}
	}

};