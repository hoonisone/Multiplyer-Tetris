#pragma once
#pragma once
#include <conio.h>

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_SPACE ' '

class Input {
public:
	static char getKey() {	// �Է��� �ִ� ��� �� �ϳ��� ����
		char c;
		if (_kbhit()) {
			c = _getch();
			if (c == -32)	return _getch();
			else			return c;
		}
		return NULL;
	}
};