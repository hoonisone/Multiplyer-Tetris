#include <stdlib.h>
#include "random.h"
#include "timer.h"
#include "error.h"

static Random* randomCreate();
static int randomGetValue();

Random* getRandom() {
	static Random* random = randomCreate();
	return random;
}
static Random* randomCreate() {
	Random* random = (Random*)malloc(sizeof(Random));
	if (random == NULL) {
		errorPrint("memory allocation failed");
	}
	random->getValue = randomGetValue;
	srand(time(NULL));
	return random;
}

static int randomGetValue() {
	return rand();
}