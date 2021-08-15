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
string modeSelectHandler();
string singleModeGametHandler();
string singleModeMenuHandler();
string gameExitHandler();

unordered_map<string, string(*)()> sceneInfor;
int main(int argc, char* argv[]) {
	Consol::changeScreenSize(WIDTH, HEIGHT);
	Consol::setCursorFlag(false);
	//sceneInfor["main menu scene"] = modeSelectHandler;
	//sceneInfor["single mode menu scene"] = singleModeMenuHandler;
	//sceneInfor["single mode game scene"] = singleModeGametHandler;
	//sceneInfor["game exit scene"] = gameExitHandler;
	//string sceneName = "main menu scene";
	//while (true) {
	//	sceneName = sceneInfor[sceneName]();
	//}
	
}

string singleModeGametHandler() {
	Consol::clear();
	Bean::getSingleModeGameManager()->run();
	//return "single score scene";
	return "main menu scene";
}
string modeSelectHandler() {
	Consol::clear();
	const vector<string> key = { "Single Mode", "Multi Mode", "Developer", "Exit"};
	const vector<string> value= { "single mode menu scene", "multi mode menu scene", "developer scene", "game exit scene"};
	string mode = Bean::getModeSelectScene()->start();
	for (int i = 0; i < key.size(); i++) {
		if (mode == key[i])
			return value[i];
	}
	return "";
}
string singleModeMenuHandler() {
	Consol::clear();
	const vector<string> key = { "Start", "Rank", "Back"};
	const vector<string> value = { "single mode game scene", "single mode rank scene", "main menu scene"};
	string mode = Bean::getSingleModeMeneSelectScene()->start();
	for (int i = 0; i < key.size(); i++) {
		if (mode == key[i])
			return value[i];
	}
	return "";
}
string gameExitHandler() {
	exit(-1);
}