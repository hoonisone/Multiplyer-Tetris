#pragma once
#include <stdlib.h> // rand() �Լ� ���� ���̺귯��
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