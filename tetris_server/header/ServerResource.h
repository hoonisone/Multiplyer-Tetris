#pragma once

#include "error.h"
#include <vector>
#include <string>
using namespace std;

class ServerResource {
private:
	static ServerResource* serverResource;
	vector<string> loginUserNames;
public:
	static ServerResource* GetServerResource() {
		if (serverResource == NULL) {
			errorPrint("serveResource is not registerd yet!");
		}
		return serverResource;
	}
};