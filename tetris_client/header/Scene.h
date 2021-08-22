#pragma once
#include "KeyInput.h"
#include "ColorPainter.h"
#include "Canvas.h"
#include <windows.h>
#include "UIManager.h"
#include "ColorPrinter.h"

/*
- Director 객체에 의해 관리된다.
*/
class Scene {
private:
public:
	virtual string action() = 0;	// 장면 하나를 수행하고 반드시 다음 장면의 이름을 반환해야 한다. 공백은 종료를 뜻한다.
};

