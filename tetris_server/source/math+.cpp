#include "math+.h"
#include "test.h"

static int TestGreater();
static int TestSmaller();

int greater(int a, int b) {
	return (a > b) ? a : b;
}

int smaller(int a, int b) {
	return (a < b) ? a : b;
}

int TestGreater(){
	int a = 10;
	int b = 20;
	if (greater(a, b) == b)
		return 1;
	else
		return 0;
}

int TestSmaller() {
	int a = 10;
	int b = 20;
	if (smaller(a, b) == a)
		return 1;
	else
		return 0;
}

void TestMathPlus() {
	TestStart();
	Test("greater", TestGreater);
	Test("smaller", TestSmaller);
	TestEnd();
}
