#pragma once
#include "Server.h"
#include "MultiUserManager.h"
class Bean {
private:
	static UserDao* getUserDao() {
		return new UserDao(getFileManager());
	}
	static FileManager* getFileManager() {
		return new FileManager("user.txt");
	}
public:
	static UserManager* getUserManager() {
		return new UserManager(getUserDao());
	}
	static Server* getServer(int port) {
		return new Server(port);
	}
};