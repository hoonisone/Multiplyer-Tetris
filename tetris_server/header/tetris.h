#pragma once
#include "mainScreen.h"
#include "scoreBoard.h"

#define TETRIS getTetrisFunction()

typedef struct Tetris {
	MainScreen* mainScreen;
	SubScreen* subScreen;

}Tetris;

typedef struct TetrisFunction {
	Tetris* (*create)();
	void (*mainHandler)(Tetris* tetris);
};

TetrisFunction* getTetrisFunction();