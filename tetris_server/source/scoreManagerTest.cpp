#include "scoreManagerTest.h"
#include "test.h"
#include <stdio.h>

static int LevelUpTest();

void ScoreManagerTest() {
	testStart();
	test("LevelUpTest", LevelUpTest);
	testEnd();
}

int LevelUpTest() {
	ScoreBoard* sb = scoreBoardCreate();
	ScoreManager* sm = scoreManagerCreate(sb);
	int nextLevelLine = sm->computeNextLevelLine(sm->scoreBoard->level);
	for (int i = 0; i < nextLevelLine; i++) {
		sm->lineClear(sm, 1);
	}
	printf("%d\n", sm->scoreBoard->level);
	if (sm->scoreBoard->level == 2) {
		return 1;
	}
	return 0;
}
