#pragma warning(disable:4996)
#define _HAS_STD_BYTE 0
#include <iostream>
#include "server.h"
using namespace std;
void responseHandler(char* request, char* response) {
	strcpy(response, request);
	return;
}

int main(int argc, char* argv[]) {
	serverRun(5000, responseHandler);
	//Consol::changeScreenSize(WIDTH, HEIGHT);
	//Consol::setCursorFlag(false);
	//Bean::getDirector()->run("main menu");
}
