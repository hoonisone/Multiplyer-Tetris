#pragma once

#include <string>
using namespace std;

class ServerInfor {
private:
	string name;
	string ip;
	string port;
public:

	ServerInfor(string name, string ip, string port) :name(name), ip(ip), port(port) {};
	string getName() {
		return name;
	}
	string getIp() {
		return ip;
	}
	string getPort() {
		return port;
	}
};