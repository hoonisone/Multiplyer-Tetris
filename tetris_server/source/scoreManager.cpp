//#include "scoreManager.h"
//#include "scoreBoard.h"
//#include "test.h"
//
//#include <stdlib.h>
//#include <stdio.h>
//#define DEFAULT_BLOCK_SCORE 1
//#define DEFAULT_LINE_SCORE 10
//
//static void scoreManagerBlockClear(ScoreManager* sm);
//static void scoreManagerLineClear(ScoreManager* sm, int lineNum);
//static int scoreManagerComputeComboScore(int score, int combo);
//static void scoreManagerLevelUp(ScoreManager* sm);
//static int scoreManagerComputeNextLevelLine(int curLevel);
//static int scoreManagerComputeBlockScore(int curLevel);
//static int scoreManagerComputeLineScore(int curLevel);
//static int scoreManagerLevelUpConditionCheck(ScoreManager* sm);
//
//static int scoreManagerFillInternalMethod(ScoreManager * sm) {
//	sm->blockClear = scoreManagerBlockClear;
//	sm->lineClear = scoreManagerLineClear;
//	sm->computeComboScore = scoreManagerComputeComboScore;
//	sm->levelUp = scoreManagerLevelUp;
//	sm->computeNextLevelLine = scoreManagerComputeNextLevelLine;
//	sm->computeBlockScore = scoreManagerComputeBlockScore;
//	sm->computeLineScore = scoreManagerComputeLineScore;
//	sm->levelUpConditionCheck = scoreManagerLevelUpConditionCheck;
//}
//
//ScoreManager* scoreManagerCreate(ScoreBoard* sb) {
//	ScoreManager* newObject = (ScoreManager*)malloc(sizeof(ScoreManager));
//	newObject->scoreBoard = sb;
//	newObject->nextLevelLine = scoreManagerComputeNextLevelLine(newObject->scoreBoard->level);
//	int curLevel = newObject->scoreBoard->level;
//	newObject->blockScore = scoreManagerComputeBlockScore(curLevel);
//	newObject->lineScore = scoreManagerComputeLineScore(curLevel);
//	return newObject;
//}
//
//void scoreManagerBlockClear(ScoreManager* sm) {
//	scoreBoardAddBlock(sm->scoreBoard, 1);
//	scoreBoardAddScore(sm->scoreBoard, sm->blockScore);
//	scoreBoardInitCombo(sm->scoreBoard);
//	if (!sm->scoreBoard->comboCheck) {
//		scoreBoardInitCombo(sm->scoreBoard);
//	}
//	scoreBoardComboCheckOff(sm->scoreBoard);
//}
//
//void scoreManagerLineClear(ScoreManager* sm, int lineNum) {
//	scoreBoardAddLine(sm->scoreBoard, lineNum);
//	scoreBoardAddCombo(sm->scoreBoard, lineNum);
//	scoreBoardComboCheckOn(sm->scoreBoard);
//	int addScore = scoreManagerComputeComboScore(sm->lineScore, sm->scoreBoard->combo);
//	scoreBoardAddScore(sm->scoreBoard, addScore);
//	if (scoreManagerLevelUpConditionCheck(sm)) {
//		scoreManagerLevelUp(sm);
//	}
//}
//int scoreManagerComputeComboScore(int score, int combo) {
//	return score * combo;
//}
//
//void scoreManagerLevelUp(ScoreManager* sm) {
//	scoreBoardAddLevel(sm->scoreBoard, 1);
//	int curLevel = sm->scoreBoard->level;
//	sm->nextLevelLine = scoreManagerComputeNextLevelLine(curLevel);
//	sm->blockScore = scoreManagerComputeBlockScore(curLevel);
//	sm->lineScore = scoreManagerComputeLineScore(curLevel);
//}
//
//int scoreManagerComputeNextLevelLine(int curLevel) {
//	if (curLevel <= 5)
//		return (curLevel) * 5;
//	else if(curLevel<=10){
//		return 30 + (curLevel-5) * 10;
//	}
//	else {
//		return 80 + (curLevel - 10) * 20;
//	}
//}
//
//int scoreManagerComputeBlockScore(int curLevel) {
//	return DEFAULT_BLOCK_SCORE*curLevel;
//}
//
//int scoreManagerComputeLineScore(int curLevel) {
//	return DEFAULT_LINE_SCORE * curLevel * 10;
//}
//int scoreManagerLevelUpConditionCheck(ScoreManager* sm) {
//	int curLine = sm->scoreBoard->line;
//	int nextLevelLine = sm->nextLevelLine;
//	if (curLine >= nextLevelLine ){
//		return 1;
//	}
//	return 0;
//}