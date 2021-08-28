#pragma once

#include "Scene.h";
#include "error.h"
class FunctionScene : public Scene {
private:
	string(*function)();
public:
	FunctionScene(string(*function)()) :function(function) {
		if (function == NULL) {
			errorPrint("function paremeter is NULL");
		}
	};
	virtual string action() override {
		return function();
	}

	~FunctionScene() {

	}
};