#pragma once
#include <stdlib.h> // rand() 함수 포함 라이브러리
#define RANDOM getRandom()

class Random {
public:
	static int randomInt() {
		static bool initFlag = false;
		if (!initFlag) {
			srand(time(NULL));
			initFlag = true;
		}
		return rand();
	}
};