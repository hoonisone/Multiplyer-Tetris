#include "mainBlock.h"
#include "error.h"

static MainBlockFunction* mainBlockFunctionCreate();
static MainBlocK* mainBlockCreate(BlockBoard* blockBoard, Block* firstBlock);
static Block* mainBlockChangeMainBlock(MainBlocK* mainBlockManager, Block* block);
static void mainBlockInitShadowBlock(MainBlocK* mainBlockManager);
static void mainBlockUpdateShawdowBlock(MainBlocK* mainBlockManager);
static void mainBlockUpdateShawdowBlockPosition(MainBlocK* mainBlockManager);
static void mainBlockMoveUp(MainBlocK* mainBlockManager);
static void mainBlockMoveDown(MainBlocK* mainBlockManager);
static void mainBlockMoveRight(MainBlocK* mainBlockManager);
static void mainBlockMoveLeft(MainBlocK* mainBlockManager);
static int mainBlockMove(MainBlocK* mainBlockManager, void(*move)(Block* block), void(*back)(Block* block));
static void mainBlockDrawMainBlock(MainBlocK* mainBlockManager);
static void mainBlockEraseMainBlock(MainBlocK* mainBlockManager);
static void mainBlockDrawShadowBlock(MainBlocK* mainBlockManager);
static void mainBlockEraseShadowBlock(MainBlocK* mainBlockManager);

static MainBlockFunction* getMainBlockFunction() {
	static MainBlockFunction* mainBlockManagerFunction = mainBlockFunctionCreate();
	return mainBlockManagerFunction;
}
static MainBlockFunction* mainBlockFunctionCreate() {
	MainBlockFunction* object = (MainBlockFunction*)malloc(sizeof(MainBlockFunction));
	object->create = mainBlockCreate;
	object->changeMainBlock = mainBlockChangeMainBlock;
	object->moveUp = mainBlockMoveUp;
	object->moveDown = mainBlockMoveDown;
	object->moveRight = mainBlockMoveRight;
	object->moveLeft = mainBlockMoveLeft;
	return object;
}
static MainBlocK* mainBlockCreate(BlockBoard* blockBoard, Block* firstBlock) {
	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	if (firstBlock == NULL) {
		errorPrint("firstBlock is NULL");
	}
	MainBlocK* object = (MainBlocK*)malloc(sizeof(MainBlocK));
	if (object == NULL) {
		errorPrint("memory allocation failed ");
	}
	object->blockBoard = blockBoard;
	mainBlockChangeMainBlock(object, firstBlock);
	mainBlockInitShadowBlock(object);
	return object;
}

static Block* mainBlockChangeMainBlock(MainBlocK* mainBlockManager, Block* block) {	// change main block into block and return origin main block
	if (mainBlockManager == NULL) {
		errorPrint("mainBlockManager is NULL");
	}
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	Block* originBlock = mainBlockManager->mainBlock;
	mainBlockManager->mainBlock = block;
	mainBlockUpdateShawdowBlock(mainBlockManager);
	return originBlock;
}
static void mainBlockInitShadowBlock(MainBlocK* mainBlockManager) {	// 한 번만 수행
	Block* shadowBlock = BLOCK->create(0, 0, 0, 0);
	mainBlockUpdateShawdowBlock(mainBlockManager);
}
static void mainBlockUpdateShawdowBlock(MainBlocK* mainBlockManager) {
	Block* shadowBlock = mainBlockManager->shadowBlock;
	Block* mainBlock = mainBlockManager->mainBlock;
	memcpy(shadowBlock, mainBlock, sizeof(Block));
	BLOCK->setLetter(shadowBlock, (char*)"□");
	mainBlockUpdateShawdowBlockPosition(mainBlockManager);
}
static void mainBlockUpdateShawdowBlockPosition(MainBlocK* mainBlockManager) {
	BlockBoard* blockBoard = mainBlockManager->blockBoard;
	Block* mainBlock = mainBlockManager->mainBlock;
	Block* shadowBlock = mainBlockManager->shadowBlock;
	int originY = mainBlock->y;
	while (BLOCK_BOARD->blockPositionPermitCheck(blockBoard, mainBlock)) {	// mainBlock을 끝까지 내린다.
		BLOCK->moveDown(mainBlock);
	}
	BLOCK->moveUp(mainBlock);
	shadowBlock->y = mainBlock->y;
	shadowBlock->x = mainBlock->x;
	mainBlock->y = originY;
}

static void mainBlockMoveUp(MainBlocK* mainBlockManager) {
	mainBlockMove(mainBlockManager, BLOCK->moveUp, BLOCK->moveDown);
}
static void mainBlockMoveDown(MainBlocK* mainBlockManager) {
	mainBlockMove(mainBlockManager, BLOCK->moveDown, BLOCK->moveUp);
}
static void mainBlockMoveRight(MainBlocK* mainBlockManager) {
	int success = mainBlockMove(mainBlockManager, BLOCK->moveRight, BLOCK->moveLeft);
	if (success) {// 좌우로 움질일 때만 shadowBlock갱신
		mainBlockUpdateShawdowBlockPosition(mainBlockManager);	
	}
}
static void mainBlockMoveLeft(MainBlocK* mainBlockManager) {
	int success = mainBlockMove(mainBlockManager, BLOCK->moveLeft, BLOCK->moveRight);
	if (success) {// 좌우로 움질일 때만 shadowBlock갱신
		mainBlockUpdateShawdowBlockPosition(mainBlockManager);	
	}
}

// mainBlock에 대해 move를 수행하고 범위를 벗어나면 back를 수행한다.
// 이동 성공 여부 반환
static int mainBlockMove(MainBlocK* mainBlockManager, void (*move)(Block* block), void (*back)(Block* block)) {
	int flag = 1;
	if (mainBlockManager == NULL) {
		errorPrint("mainBlockManager is NULL");
	}
	BlockBoard* blockBoard = mainBlockManager->blockBoard;
	Block* mainBlock = mainBlockManager->mainBlock;
	BLOCK->del(mainBlock);
	move(mainBlock);
	if (!BLOCK_BOARD->blockPositionPermitCheck(blockBoard, mainBlock)) {
		back(mainBlock);
		flag = 0;
	}
	BLOCK->drawBlock(mainBlock);
	return flag;
}

static void mainBlockDrawMainBlock(MainBlocK* mainBlockManager) {
	BLOCK->drawBlock(mainBlockManager->mainBlock);
}
static void mainBlockEraseMainBlock(MainBlocK* mainBlockManager) {
	BLOCK->del(mainBlockManager->mainBlock);
}
static void mainBlockDrawShadowBlock(MainBlocK* mainBlockManager) {
	BLOCK->drawBlock(mainBlockManager->shadowBlock);
}
static void mainBlockEraseShadowBlock(MainBlocK* mainBlockManager) {
	BLOCK->del(mainBlockManager->shadowBlock);
}
