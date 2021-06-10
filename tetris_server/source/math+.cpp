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