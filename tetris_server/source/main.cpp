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
	drawScreen(screen, 10 , 10);


}