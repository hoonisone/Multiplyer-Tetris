#pragma once
#include <stdlib.h> // rand() �Լ� ���� ���̺귯��
#define RANDOM getRandom()

typedef struct Random {
	int (*getValue)();
};

Random* getRandom();
