#pragma once

#include "Scene.h";
#include "error.h"
#include "Canvas.h"
class FunctionScene : public Scene {
private:
	Canvas* canvas;
	string(*function)();
public:
	FunctionScene(Canvas* canvas,  string(*function)()) :canvas(canvas), function(function) {
		if (function == NULL) {
			errorPrint("function paremeter is NULL");
		}
	};
	virtual string action() override {
		canvas->draw();
		return function();
	}

	~FunctionScene() {
		delete canvas;
	}
};