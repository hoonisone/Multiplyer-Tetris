#pragma once
#include <vector>
#include <string>
#include "ServerInforDao.h"
#include "error.h"
class ServerInforManager {
private:
	vector<ServerInfor> data;
	ServerInforDao* dao;
public:
	ServerInforManager(ServerInforDao* dao) :dao(dao) {
		data = dao->getAllObjects();
	};

	bool chackNameExist(string name) {
		for (auto infor : data) {
			if (name == infor.getName()) {
				return true;
			}
		}
		return false;
	}

	void insert(ServerInfor serverInfor) {
		if (chackNameExist(serverInfor.getName())) {
			errorPrint("server name already exist");
		}
		data.push_back(serverInfor);
	}

	ServerInfor getObjectByName(string name) {
		for (auto infor : data) {
			if (name == infor.getName()) {
				return infor;
			}
		}
		errorPrint("not exist name");
	}

	vector<string> getAllServerName() {
		vector<string> names;
		for (auto infor : data) {
			names.push_back(infor.getName());
		}
		return names;
	}

};