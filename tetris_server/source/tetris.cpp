#include <stdio.h>
#include <conio.h>
#include "graphic.h"
#include "tetris.h"
#include "mainScreen.h"
#include "subScreen.h"
#include <stdlib.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE ' '
#define HOLD 'z'
#define ITEM 'x'

static TetrisFunction* createTetrisFunction();
static char getKey();
static void tetrisMainHandler(Tetris* tetris);
static void tetrisMoveRightHandler(Tetris* tetris);
static void tetrisMoveLeftHandler(Tetris* tetris);
static void tetrisMoveDownHandler(Tetris* tetris);
static void tetrisMoveFloorHandler(Tetris* tetris);
static void tetrisHoldKeyHandler(Tetris* tetris);
static void tetrisItemKeyHandler(Tetris* tetris);
static void tetrisTurnRightHandler(Tetris* tetris);
static void tetrisTurnLeftHandler(Tetris* tetris);


Tetris * createTetris() {
	Tetris* tetris = (Tetris*)malloc(sizeof(Tetris));
	tetris->mainScreen = MAIN_SCREEN->create(0, 0, 12, 22);
	tetris->subScreen = SUB_SCREEN->create(11, 0, 6, 22, BLOCK->createRandomBlock());
	return tetris;
}
TetrisFunction* getTetrisFunction() {
	TetrisFunction* tf = NULL;
	if (tf == NULL) {
		tf = (TetrisFunction*)malloc(sizeof(TetrisFunction));
		tf->create = createTetris;
		tf->mainHandler = tetrisMainHandler;
	}
	return tf;
}

char getKey() {
	char key = _getch();
	if (key == -32) {
		key = _getch();
		switch (key) {
		case LEFT:
			return LEFT;
		case RIGHT:
			return RIGHT;
		case UP:
			return UP;
		case DOWN:
			return DOWN;
		}
	}else {
		switch (key) {
		case SPACE:
			return SPACE;
		case HOLD:
			return HOLD;
		case ITEM:
			return ITEM;
		}
	}
	return NULL;
}
void tetrisMainHandler(Tetris* tetris) {
	MainScreen* mainScreen = tetris->mainScreen;
	while (1) {
		char c = getKey();
		switch (c) {
		case UP:
			tetrisTurnRightHandler(tetris);
			break;
		case DOWN:
			tetrisMoveDownHandler(tetris);
			break;
		case RIGHT:
			tetrisMoveRightHandler(tetris);
			break;
		case LEFT:
			tetrisMoveLeftHandler(tetris);
			break;
		case SPACE:
			tetrisMoveFloorHandler(tetris);
			break;
		case HOLD:
			tetrisHoldKeyHandler(tetris);
			break;
		}
	}
}

void tetrisMoveRightHandler(Tetris* tetris) {
	MAIN_SCREEN->moveRight(tetris->mainScreen);
}

void tetrisMoveLeftHandler(Tetris* tetris) {
	MAIN_SCREEN->moveLeft(tetris->mainScreen);
}

void tetrisMoveDownHandler(Tetris* tetris) {
	MAIN_SCREEN->moveDown(tetris->mainScreen);
}

void tetrisMoveFloorHandler(Tetris* tetris) {
	Block* block = SUB_SCREEN->changeNextBlock(tetris->subScreen, BLOCK->createRandomBlock());
	MAIN_SCREEN->pullDown(tetris->mainScreen, block);
}

void tetrisHoldKeyHandler(Tetris* tetris) {

}

void tetrisItemKeyHandler(Tetris* tetris) {

}

void tetrisTurnRightHandler(Tetris* tetris) {
	MAIN_SCREEN->turnRight(tetris->mainScreen);
}

void tetrisTurnLeftHandler(Tetris* tetris) {
	MAIN_SCREEN->turnLeft(tetris->mainScreen);
}