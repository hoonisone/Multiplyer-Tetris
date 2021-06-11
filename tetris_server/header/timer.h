#pragma once
#include <time.h>
#include <windows.h>
/*time.h ���̺귯�� ����*/

typedef struct Timer {
	clock_t accTime;

	void (*init)(Timer* timer);
	clock_t (*getTime)(Timer* timer);
	void (*del)(Timer* timer);
}Timer;


Timer * createTimer();



