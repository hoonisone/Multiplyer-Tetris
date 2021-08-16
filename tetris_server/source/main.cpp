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
	UserDAO* dao = Bean::getUserDAO();
	vector<User> userList;
	//userList.push_back(User("hoonisone", 1, 2, 3, 100));
	//userList.push_back(User("hoon", 11, 12, 13, 200));
	//userList.push_back(User("isone", 21, 22, 23, 300));
	//dao->setAllUsers(userList);
	userList = dao->getAllUsers();
	cout << userList.size();
	for (int i = 0; i < userList.size(); i++) {
		cout << userList[i].getName() << endl;
	}
	/*ScannerButton* button = Bean::getScannerButton(5, 5, 10, 3);
	button->draw();
	while (true) {
		char c = Input::getKey();
		if(c != -1){
			if (c == 8)
				button->backspace();
			else
				button->enter(c);
		}
	}*/
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