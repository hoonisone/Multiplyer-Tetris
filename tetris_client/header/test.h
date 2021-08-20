#pragma once

#define TEST_NAME_SIZE 100
#define TEST_MAX_NUM 100

#define test(name, function) _test((char*)name, function)

void testStart();
void _test(char* name, int (*testFunction)());
void testEnd();