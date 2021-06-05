#pragma once

#define LISTENER_BUFFER_SIZE 100

typedef struct Listener {
	int x, y;	// 리스너가 그려지는 좌표
	char buffer[LISTENER_BUFFER_SIZE+1];
	char input; // 가장 최근에 입력 받은 값
};

Listener* 

