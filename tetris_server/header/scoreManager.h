#pragma once
#include "scoreBoard.h"

typedef struct ScoreManager {
	ScoreBoard* scoreBoard;
	int nextLevelLine;
	int blockScore;
	int lineScore;
};

ScoreManager* scoreManagerCreate(ScoreBoard* scoreBoard);

void scoreManagerBlockClear(ScoreManager* scoreManager);

void scoreManagerLineClear(ScoreManager* scoreManager, int lineNum);

int computeComboScore(int score, int combo);

void levelUp(ScoreManager* scoreManager);

int computeNextLevelLine(int curLevel);

int computeBlockScore(int curLevel);

int computeLineScore(int curLevel);

int levelUpConditionCheck(ScoreManager* scoreManager);

void ScoreManagerTest();
