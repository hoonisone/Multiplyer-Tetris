#include "scoreManager.h"
#include "scoreBoard.h"
#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#define DEFAULT_BLOCK_SCORE 1
#define DEFAULT_LINE_SCORE 10

static int LevelUpTest();

ScoreManager* scoreManagerCreate(ScoreBoard* scoreBoard) {
	ScoreManager* newObject = (ScoreManager*)malloc(sizeof(ScoreManager));
	newObject->scoreBoard = scoreBoard;
	newObject->nextLevelLine = computeNextLevelLine(newObject->scoreBoard->level);
	int curLevel = newObject->scoreBoard->level;
	newObject->blockScore = computeBlockScore(curLevel);
	newObject->lineScore = computeLineScore(curLevel);
	return newObject;
}

void scoreManagerBlockClear(ScoreManager* scoreManager) {
	scoreBoardAddBlock(scoreManager->scoreBoard, 1);
	scoreBoardAddScore(scoreManager->scoreBoard, scoreManager->blockScore);
	scoreBoardInitCombo(scoreManager->scoreBoard);
	if (!scoreManager->scoreBoard->comboCheck) {
		scoreBoardInitCombo(scoreManager->scoreBoard);
	}
	scoreBoardComboCheckOff(scoreManager->scoreBoard);
}

void scoreManagerLineClear(ScoreManager* scoreManager, int lineNum) {
	scoreBoardAddLine(scoreManager->scoreBoard, lineNum);
	scoreBoardAddCombo(scoreManager->scoreBoard, lineNum);
	scoreBoardComboCheckOn(scoreManager->scoreBoard);
	int addScore = computeComboScore(scoreManager->lineScore, scoreManager->scoreBoard->combo);
	scoreBoardAddScore(scoreManager->scoreBoard, addScore);
	if (levelUpConditionCheck(scoreManager)) {
		levelUp(scoreManager);
	}
}
int computeComboScore(int score, int combo) {
	return score * combo;
}

void levelUp(ScoreManager* scoreManager) {
	scoreBoardAddLevel(scoreManager->scoreBoard, 1);
	int curLevel = scoreManager->scoreBoard->level;
	scoreManager->nextLevelLine = computeNextLevelLine(curLevel);
	scoreManager->blockScore = computeBlockScore(curLevel);
	scoreManager->lineScore = computeLineScore(curLevel);
}

int computeNextLevelLine(int curLevel) {
	if (curLevel <= 5)
		return (curLevel) * 5;
	else if(curLevel<=10){
		return 30 + (curLevel-5) * 10;
	}
	else {
		return 80 + (curLevel - 10) * 20;
	}
}

int computeBlockScore(int curLevel) {
	return DEFAULT_BLOCK_SCORE*curLevel;
}

int computeLineScore(int curLevel) {
	return DEFAULT_LINE_SCORE * curLevel * 10;
}
int levelUpConditionCheck(ScoreManager* scoreManager) {
	int curLine = scoreManager->scoreBoard->line;
	int nextLevelLine = scoreManager->nextLevelLine;
	if (curLine >= nextLevelLine ){
		return 1;
	}
	return 0;
}

void ScoreManagerTest() {
	TestStart();
	Test("LevelUpTest", LevelUpTest);
	TestEnd();
}

int LevelUpTest() {
	ScoreBoard* sb= scoreBoardCreate();
	ScoreManager* sm = scoreManagerCreate(sb);
	int nextLevelLine = computeNextLevelLine(sm->scoreBoard->level);
	for (int i = 0; i < nextLevelLine; i++) {
		scoreManagerLineClear(sm, 1);
	}
	printf("%d\n", sm->scoreBoard->level);
	if (sm->scoreBoard->level == 2) {
		return 1;
	}
	return 0;
}
