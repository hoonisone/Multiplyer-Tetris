#pragma once

#define LISTENER_BUFFER_SIZE 100

typedef struct Listener {
	int x, y;	// �����ʰ� �׷����� ��ǥ
	char buffer[LISTENER_BUFFER_SIZE+1];
	char input; // ���� �ֱٿ� �Է� ���� ��
};

Listener* 

