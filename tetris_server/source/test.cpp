#include <stdio.h>
#include <windows.h>

#include "test.h"
#include "string.h"
#include "error.h"

static int success;
static int fail;
static int total;
char failFunctionNames[TEST_MAX_NUM][TEST_NAME_SIZE];

void testStart() {
	success = 0;
	fail = 0;
	total = 0;
	printf("Test Start!!!\n");
	printf("-----------------------------------------\n");
}

void _test(char* name, int (*testFunction)()) {
	total++;
	printf("* Test(%d)\n", total);
	printf("\t- Name   : %s\n", name);
	printf("\t- Result : ");
	if (testFunction()) {
		success++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("SUCCESS!!!\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else {
		fail++;
		strcpy_s(failFunctionNames[fail], name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("FAIL\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	printf("\n");
	printf("-----------------------------------------\n");
}

void testEnd() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	printf("Total   ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf(":% d\n", total);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("Success ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf(": %d\n", success);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("Fail    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf(": %d\n", fail);

	
	if (fail > 0) {
		printf("Fail Function List:\n");
		for (int i = 0; i < fail; i++) {
			printf("\t* %s\n", failFunctionNames[i]);
		}
	}
	printf("-----------------------------------------\n");
}