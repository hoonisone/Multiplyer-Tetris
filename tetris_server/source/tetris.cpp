//#include <stdio.h>
//#include <conio.h>
//#include "graphic.h"
//#include "tetris.h"
//#include <stdlib.h>
//#define UP 72
//#define DOWN 80
//#define LEFT 75
//#define RIGHT 77
//#define SPACE ' '
//#define HOLD 'z'
//#define ITEM 'x'
//
//static TetrisFunction* createTetrisFunction();
//static void tetrisFunctionFillInternalMethod(TetrisFunction* tf);
//static char getKey();
//static void tetrisMainHandler(Tetris* tetris);
//static void tetrisMoveRightHandler(Tetris* tetris);
//static void tetrisMoveLeftHandler(Tetris* tetris);
//static void tetrisMoveDownHandler(Tetris* tetris);
//static void tetrisMoveFloorHandler(Tetris* tetris);
//static void tetrisHoldKeyHandler(Tetris* tetris);
//static void tetrisItemKeyHandler(Tetris* tetris);
//static void tetrisTurnRightHandler(Tetris* tetris);
//static void tetrisTurnLeftHandler(Tetris* tetris);
//
//TetrisFunction* _tetrisFunction = NULL;
//
//Tetris * createTetris() {
//	Tetris* tetris = (Tetris*)malloc(sizeof(Tetris));
//	tetris->screen = createScreen();
//	return tetris;
//}
//TetrisFunction* getTetrisFunction() {
//	if (_tetrisFunction == NULL) {
//		_tetrisFunction = createTetrisFunction();
//	}
//	return _tetrisFunction;
//}
//TetrisFunction* createTetrisFunction() {
//	TetrisFunction* tf = (TetrisFunction*)malloc(sizeof(TetrisFunction));
//	tetrisFunctionFillInternalMethod(tf);
//	return tf;
//}
//void tetrisFunctionFillInternalMethod(TetrisFunction* tf) {
//	tf->mainHandler = tetrisMainHandler;
//	tf->moveRightHandler = tetrisMoveRightHandler;
//	tf->moveLeftHandler = tetrisMoveLeftHandler;
//	tf->moveDownHandler = tetrisMoveDownHandler;
//	tf->moveFloorHandler = tetrisMoveFloorHandler;
//	tf->holdKeyHandler = tetrisHoldKeyHandler;
//	tf->itemKeyHandler = tetrisItemKeyHandler;
//	tf->turnRightHandler = tetrisTurnRightHandler;
//	tf->turnLeftHandler = tetrisTurnLeftHandler;
//}
//
//char getKey() {
//	char key = _getch();
//	if (key == -32) {
//		key = _getch();
//		switch (key) {
//		case LEFT:
//			return LEFT;
//		case RIGHT:
//			return RIGHT;
//		case UP:
//			return UP;
//		case DOWN:
//			return DOWN;
//		}
//	}else {
//		switch (key) {
//		case SPACE:
//			return SPACE;
//		case HOLD:
//			return HOLD;
//		case ITEM:
//			return ITEM;
//		}
//	}
//	return NULL;
//}
//void tetrisMainHandler(Tetris* tetris) {
//	Screen* screen = tetris->screen;
//
//	while (1) {
//		SCREEN->drawFullScreen(screen, 0, 0);
//		char c = getKey();
//		switch (c) {
//		case UP:
//			tetrisTurnRightHandler(tetris);
//			break;
//		case DOWN:
//			tetrisMoveDownHandler(tetris);
//			break;
//		case RIGHT:
//			tetrisMoveRightHandler(tetris);
//			break;
//		case LEFT:
//			tetrisMoveLeftHandler(tetris);
//			break;
//		case SPACE:
//			tetrisMoveFloorHandler(tetris);
//			break;
//		case HOLD:
//			tetrisHoldKeyHandler(tetris);
//			break;
//		}
//	}
//}
//
//void tetrisMoveRightHandler(Tetris* tetris) {
//	//SCREEN->eraseCurBlock(tetris->screen);
//	SCREEN->curBlockMoveRight(tetris->screen);
//}
//
//void tetrisMoveLeftHandler(Tetris* tetris) {
//
//}
//
//void tetrisMoveDownHandler(Tetris* tetris) {
//
//}
//
//void tetrisMoveFloorHandler(Tetris* tetris) {
//
//}
//
//void tetrisHoldKeyHandler(Tetris* tetris) {
//
//}
//
//void tetrisItemKeyHandler(Tetris* tetris) {
//
//}
//
//void tetrisTurnRightHandler(Tetris* tetris) {
//
//}
//
//void tetrisTurnLeftHandler(Tetris* tetris) {
//
//}