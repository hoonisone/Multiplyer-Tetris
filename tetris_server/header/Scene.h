#pragma once
#pragma once
#include "Input.h"
#include "ColorPainter.h"
#include "Canvas.h"
#include <windows.h>
#include "ButtonManager.h"
#include "ColorPrinter.h"

class Scene {
private:
	virtual void erase() = 0;
public:
	virtual string start() = 0;	// ����� �����ϰ� ��� ������ text�� ����
};

