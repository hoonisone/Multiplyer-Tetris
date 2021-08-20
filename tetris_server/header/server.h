#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock.h>

typedef struct ClientSocket {
	SOCKET socket;
	SOCKADDR_IN address;
	int addressSize;
} ClientSocket;

void serverRun(int port, void (*control)(char* request, char* response));

DWORD WINAPI serverConnectHandler(void* data);
DWORD WINAPI serverCommunicateHandler(void* data);