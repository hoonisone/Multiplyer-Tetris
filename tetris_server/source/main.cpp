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
#include "math+.h"
#include <wchar.h>

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
	graphicChangeLetter((char*)"*");
	drawLineRectangle(0, 0, 12, 3);
	drawLineRectangle(0, 2, 12, 5);
	graphicChangeLetter((char*)"¶≤");
	drawPoint(0, 2);
	graphicChangeLetter((char*)"¶¥");
	drawPoint(11, 2);

	graphicMoveCursor(1, 1);
	printf("   %10s\n\n", "«—∏Ì»∆");
	graphicMoveCursor(1, 3);
	printf("  WIN: %7d\n", 100);
	graphicMoveCursor(1, 4);
	printf(" DRAW: %7d\n", 100);
	graphicMoveCursor(1, 5);
	printf(" LOSE: %7d\n", 100);
	Screen* screen = screenCreateScreen();
	curBlockMoveDown(screen);
	curBlockMoveDown(screen);
	curBlockMoveDown(screen);
	curBlockMoveDown(screen);
	curBlockMoveDown(screen);
	pressCurBlock(screen);
	screenSetCurBlock(screen);
	screenSetCurBlock(screen);
	for(int i=0 ; i<10 ; i++)
		curBlockMoveDown(screen);
	drawScreen(screen, 0 , 7);
	
	
	//wchar_t wc1 = L'\u2764';
	//graphicMoveCursor(30, 20);
	//wprintf(L"%c\n", wc1);
	while (1);


}

