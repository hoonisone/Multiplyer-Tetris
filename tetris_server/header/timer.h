#pragma once
#include <time.h>
#include <windows.h>

class Timer {
private:
	int accTime;
public:
	Timer() {
		init();
	}
	void init(){
		accTime = clock();
	}
	clock_t getAccTime(){
		return clock() - accTime;
	}
	~Timer(){

	}
};