//#include <stdio.h>
//#include <stdlib.h>
//#include "scoreBoard.h"
//#include "graphic.h"
//
//ScoreBoard* scoreBoardCreate() {
//	ScoreBoard* newObject = (ScoreBoard*)malloc(sizeof(ScoreBoard));
//	newObject->level = 1;
//	newObject->score = 0;
//	newObject->line = 0;
//	newObject->combo = 0;
//	newObject->comboCheck = 0;
//	return newObject;
//}
//
//void scoreBoardAddScore(ScoreBoard * scoreBoard, int score) {
//	scoreBoard->score += score;
//}
//
//void scoreBoardSubScore(ScoreBoard* scoreBoard, int score) {
//	scoreBoard->score -= score;
//	if (scoreBoard->score < 0)
//		scoreBoard->score = 0;
//}
//
//void scoreBoardAddLevel(ScoreBoard* scoreBoard, int level) {
//	scoreBoard->level += level;
//}
//
//void scoreBoardSubLevel(ScoreBoard* scoreBoard, int level) {
//	scoreBoard->level -= level;
//	if (scoreBoard->level < 1)
//		scoreBoard->level = 1;
//}
//
//void scoreBoardAddBlock(ScoreBoard* scoreBoard, int block) {
//	scoreBoard->block += block;
//}
//
//void scoreBoardSubBlock(ScoreBoard* scoreBoard, int block) {
//	scoreBoard->block -= block;
//	if (scoreBoard->block < 0)
//		scoreBoard->block = 0;
//}
//
//void scoreBoardAddLine(ScoreBoard* scoreBoard, int line) {
//	scoreBoard->line += line;
//}
//
//void scoreBoardSubLine(ScoreBoard* scoreBoard, int line) {
//	scoreBoard->line -= line;
//	if (scoreBoard->line < 0)
//		scoreBoard->line = 0;
//}
//
//void scoreBoardInitCombo(ScoreBoard* scoreBoard) {
//	scoreBoard->combo = 0;
//}
//
//void scoreBoardAddCombo(ScoreBoard* scoreBoard, int combo) {
//	scoreBoard->combo += combo;
//}
//
//void scoreBoardSubCombo(ScoreBoard* scoreBoard, int combo) {
//	scoreBoard->combo -= combo;
//	if (scoreBoard->combo < 0)
//		scoreBoard->combo = 0;
//}
//
//void scoreBoardComboCheckOn(ScoreBoard* scoreBoard) {
//	scoreBoard->comboCheck = 1;
//}
//
//void scoreBoardComboCheckOff(ScoreBoard* scoreBoard) {
//	scoreBoard->comboCheck = 0;
//}
//
//void scoreBoardDraw(ScoreBoard* scoreBoard, int X, int Y) {
//
//}