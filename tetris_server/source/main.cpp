#pragma warning(disable:4996)
#define _HAS_STD_BYTE 0
#include <iostream>
#include "Bean.h"
#include <unordered_map>
using namespace std;
void responseHandler(char* request, char* response) {
	strcpy(response, request);
	return;
}

//Test();
//serverRun(5000, responseHandler);
/*SingleModeManger* singleModeManager = Bean::getSingleManager();
singleModeManager->run();
Consol::move(0, 100);*/


unordered_map<string, string(*)()> sceneInfor;
int main(int argc, char* argv[]) {
	Consol::changeScreenSize(WIDTH, HEIGHT);
	Consol::setCursorFlag(false);
	Bean::getDirector()->run("main menu");
}
