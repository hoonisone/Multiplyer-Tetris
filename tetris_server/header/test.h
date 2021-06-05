#pragma once

#define TEST_NAME_SIZE 100
#define TEST_MAX_NUM 100

#define Test(name, function) _Test((char*)name, function)

void TestStart();
void _Test(char* name, int (*testFunction)());
void TestEnd();