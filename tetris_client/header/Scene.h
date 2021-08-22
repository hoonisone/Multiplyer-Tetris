#pragma once
#include "KeyInput.h"
#include "ColorPainter.h"
#include "Canvas.h"
#include <windows.h>
#include "UIManager.h"
#include "ColorPrinter.h"

/*
- Director ��ü�� ���� �����ȴ�.
*/
class Scene {
private:
public:
	virtual string action() = 0;	// ��� �ϳ��� �����ϰ� �ݵ�� ���� ����� �̸��� ��ȯ�ؾ� �Ѵ�. ������ ���Ḧ ���Ѵ�.
};

