#pragma warning(disable:4996)
#pragma comment(lib, "rpcrt4.lib")

#define _HAS_STD_BYTE 0
#include <iostream>
#include "Bean.h"
using namespace std;
void responseHandler(char* request, char* response) {
	strcpy(response, request);
	return;
}

int main(int argc, char* argv[]) {
	UserManager* um = Bean::getUserManager();
	Server* server = Bean::getServer(5000);
	server->enroll("connect", [&](string ip, int port, string data) -> string {
		vector<string> userNames = um->getAllUserNames();
		string s;
		for (int i = 0; i < userNames.size(); i++) {
			s += userNames[i] + "/";
		}
		s.pop_back();
		return s;
		});
	server->enroll("default", [&](string ip, int port, string data) -> string {
		vector<string> userNames = um->getAllUserNames();
		string s;
		for (int i = 0; i < userNames.size(); i++) {
			s += userNames[i] + "/";
		}
		s.pop_back();
		return s;
	});
	server->run();
	//Consol::changeScreenSize(WIDTH, HEIGHT);
	//Consol::setCursorFlag(false);
	//Bean::getDirector()->run("main menu");
}
