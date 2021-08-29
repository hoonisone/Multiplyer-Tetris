#pragma once

#include "Dao.h"
#include "ServerInfor.h"
#include "string+.h"
class ServerInforDao : public Dao<ServerInfor>{
private:
	ServerInfor parse(string serverInforString) override {
		vector<string> tokens = split(serverInforString, "/");
		string name = tokens[0];
		string ip = tokens[1];
		string port = tokens[2];
		return ServerInfor(name, ip, port);
	}
	string toString(ServerInfor serverInfor) override {
		char arr[100];
		string name = serverInfor.getName();
		string ip= serverInfor.getIp();
		string port= serverInfor.getPort();
		sprintf(arr, "%s/%s/%s", name.c_str(), ip.c_str(), port.c_str());
		return string(arr);
	}
public:
	ServerInforDao(FileManager* fm) :Dao(fm) {};

};