#include <stdio.h>
#include <stdlib.h>
#include "my_math.h"

int my_add(int a, int b) {
	return a + b;
}

int my_div(int a, int b) {
	if (b == 0) {
		printf("0으로 나눌 수 없습니다.");
		exit(0);
	}
	return a / b;
}
