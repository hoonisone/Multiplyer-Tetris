//#pragma once
//#include "scoreBoard.h"
//
//typedef struct ScoreManager {
//	ScoreBoard* scoreBoard;
//	int nextLevelLine;
//	int blockScore;
//	int lineScore;
//
//	// internal method
//	void (*blockClear)(ScoreManager* sm);
//	void (*lineClear)(ScoreManager* sm, int lineNum);
//	int (*computeComboScore)(int score, int combo);
//	void (*levelUp)(ScoreManager* sm);
//	int (*computeNextLevelLine)(int curLevel);
//	int(*computeBlockScore)(int curLevel);
//	int (*computeLineScore)(int curLevel);
//	int (*levelUpConditionCheck)(ScoreManager* sm);
//};
//
//ScoreManager* scoreManagerCreate(ScoreBoard* sb);