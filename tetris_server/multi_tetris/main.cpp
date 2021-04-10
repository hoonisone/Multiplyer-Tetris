#include <stdio.h>
#include "serverSocket.h"
#include "error.h"
#include "list.h"

int compare(Data a, Data b) {
	return a <= b;
}

int main(int argc, char* argv[]) {
	List* listOdd = listCreate();
	List* listEven = listCreate();

	//for (int i = 0; i < listGetSize(listOdd); i++) {
	//	printf("%d", listGetElement(listOdd, i));
	//}

	for (int i = 0; i < 100; i++) {
		listPushBackElement(listOdd, i+1);
	}
	for (int i = listGetSize(listOdd)-1; i >= 0; i--) {
		int value = listGetElement(listOdd, i);
		if (value % 2 == 0) {
			listPopElement(listOdd, i);
			listPushBackElement(listEven, value);
		}
	}
	for (int i = 0; i < listGetSize(listOdd); i++) {
		printf("%d\n", listGetElement(listOdd, i));
	}
	//listPopElement(list, 8);
	//listPopElement(list, 4);
	//listPopElement(list, 3);
	//listSort(list, compare);
	//listPushBackList(list, list);
	//for (int i = 0; i < listGetSize(list); i++) {
	//	printf("%d\n", listGetElement(list, i));
	//}


	//int port = 5000;
	//char buffer[BUFFER_SIZE];
	//ServerSocket* sc = serverSocketCreate(port);
	//serverSocketConnect(sc);
	//serverSocketSend(sc, (char*)"hello");
	//int len = serverSocketReceive(sc, buffer);
	//printf("Massage(%d): %s\n", len, buffer);
	//serverSocketTerminate(sc);
}