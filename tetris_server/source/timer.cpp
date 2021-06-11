#include "timer.h"
#include <stdlib.h>
#include "list.h"
#include <stdio.h>

// internal method
static void timerInit(Timer* timer);
static clock_t timerGetTime(Timer* timer);
static void timerDelete(Timer* timer);
static void timerFillInternalMethod(Timer* timer);

Timer* createTimer()
{
	Timer* timer = (Timer*)malloc(sizeof(Timer));
	timerFillInternalMethod(timer);
	timerInit(timer);
	return timer;
}

void timerFillInternalMethod(Timer* timer)
{
	timer->init = timerInit;
	timer->getTime = timerGetTime;
	timer->del = timerDelete;
}

void timerInit(Timer* timer)
{
	timer->accTime = 0;
}

clock_t timerGetTime(Timer* timer)
{
	return clock() - timer->accTime;
}

void timerDelete(Timer* timer) {
	free(timer);
}