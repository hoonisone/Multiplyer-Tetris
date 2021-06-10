#pragma once
#include "math+.h"
#include "mathPlusTest.h"
#include "test.h"
static int smallerTest();
static int greaterTest();

int greaterTest() {
	int a = 10;
	int b = 20;
	if (greater(a, b) == b)
		return 1;
	else
		return 0;
}

int smallerTest() {
	int a = 10;
	int b = 20;
	if (smaller(a, b) == a)
		return 1;
	else
		return 0;
}

void mathPlusTest() {
	testStart();
	test("greater", greaterTest);
	test("smaller", smallerTest);
	testEnd();
}