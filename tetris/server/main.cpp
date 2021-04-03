#include <stdio.h>
#include "serverSocket.h"
#include "error.h"
#include "list.h"

int compare(Data a, Data b) {
	return a <= b;
}

//DWORD WINAPI ThreadFunc1(void* data) {
//	static int cnt = 0;
//	while (1) {
//		int id = GetCurrentThreadId();
//		printf("id=%d, ThreadFunc1:%d \n", id, cnt++);
//		Sleep(2000);
//	}
//}

int main(int argc, char* argv[]) {
	List* list = listCreate();
	for (int i = 0; i < listGetSize(list); i++) {
		printf("%d", listGetElement(list, i));
	}
	for (int i = 0; i < 10; i++) {
		listPushBackElement(list, i+1);
	}
	listPopElement(list, 8);
	listPopElement(list, 4);
	listPopElement(list, 3);
	listSort(list, compare);
	listPushBackList(list, list);
	for (int i = 0; i < listGetSize(list); i++) {
		printf("%d\n", listGetElement(list, i));
	}

	//HANDLE thread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
	//HANDLE thread2 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);

	//while (1) {
	//	Sleep(10000);
	//}

	//int port = 5000;
	//char buffer[BUFFER_SIZE];
	//ServerSocket* sc = serverSocketCreate(port);
	//serverSocketConnect(sc);
	//Sleep(10000);
	//serverSocketSend(sc, (char*)"hello");
	//int len = serverSocketReceive(sc, buffer);
	//printf("Massage(%d): %s\n", len, buffer);
	//serverSocketTerminate(sc);
}