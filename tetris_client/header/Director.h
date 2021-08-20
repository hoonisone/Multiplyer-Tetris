#pragma once
#include "Scene.h"
#include "Consol.h"
#include <vector>
#include <string>
#include <unordered_map>

class Director {
	unordered_map<string, Scene*(*)()> sceneInfor;	// sceneName과 scene object creator를 관리한다.
	string curSceneName = "";
public:
	Director() {};
	void enrollScene(string name, Scene* (*scene)()) {
		try{
			sceneInfor[name] = scene;
		}
		catch(...){
			errorPrint("scene enrollment error");
		}
		
	}
	void run(string startSceneName) {
		curSceneName = startSceneName;
		while (true) {
			Consol::clear();
			curSceneName = sceneInfor[curSceneName]()->action();
			
			if (curSceneName == "")
				break;
		}
		cout << "종료";
	}
};