#include "math+.h"
#include "test.h"

static int GreaterTest();
static int SmallerTest();

int greater(int a, int b) {
	return (a > b) ? a : b;
}

int smaller(int a, int b) {
	return (a < b) ? a : b;
}

int GreaterTest(){
	int a = 10;
	int b = 20;
	if (greater(a, b) == b)
		return 1;
	else
		return 0;
}

int SmallerTest() {
	int a = 10;
	int b = 20;
	if (smaller(a, b) == a)
		return 1;
	else
		return 0;
}

void MathPlusTest() {
	TestStart();
	Test("greater", GreaterTest);
	Test("smaller", SmallerTest);
	TestEnd();
}