#pragma once
#pragma once
#include <conio.h>

enum Key {KEY_NULL=-1,  KEY_LEFT=75,KEY_RIGHT = 77, KEY_UP = 72, KEY_DOWN = 80, KEY_SPACE = ' '};

class Input {
public:
	static Key getKey() {	// 입력이 있는 경우 값 하나를 리턴
		Key c;
		if (_kbhit()) {
			c = (Key)_getch();
			if (c == -32)	return (Key)_getch();
			else			return c;
		}
		return (Key)-1;
	}
};