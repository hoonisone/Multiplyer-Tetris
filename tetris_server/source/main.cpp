#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "error.h"
#include "list.h"
#include "user.h"
#include "utill.h"
#include "string+.h"
#include "file.h"
#include "userManager.h"
#include "tetrisScreen.h"

#include <conio.h>

void responseHandler(char* request, char* response) {
	strcpy(response, request);
	return;
}

void Test() {
	ListTestAll();
}

int main(int argc, char* argv[]) {
	//serverRun(5000, responseHandler);

	Screen* screen = screenCreateScreen();
	int (*arr)[4] = blockGetShape(screen->curBlock);
	printf("x = %d\n", screen->curBlockX);
	printf("y = %d\n", screen->curBlockY);
	printf("shape = %d\n", screen->curBlock->shape);
	printf("color = %d\n", screen->curBlock->color);
	printf("angle = %d\n", screen->curBlock->angle);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d", arr[i][j]);
		}
		printf("\n");
	}
}