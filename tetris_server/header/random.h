#pragma once
#include <stdlib.h> // rand() 함수 포함 라이브러리
#define RANDOM getRandom()

typedef struct Random {
	int (*getValue)();
};

Random* getRandom();
