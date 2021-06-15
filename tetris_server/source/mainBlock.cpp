#include "mainBlock.h"
#include "error.h"

static MainBlockFunction* mainBlockFunctionCreate();
static MainBlock* mainBlockCreate(BlockBoard* blockBoard, Block* firstBlock);
static Block* mainBlockChangeMainBlock(MainBlock* mainBlockManager, Block* block);
static void mainBlockInitShadowBlock(MainBlock* mainBlockManager);
static void mainBlockUpdateShawdowBlock(MainBlock* mainBlockManager);
static void mainBlockUpdateShawdowBlockPosition(MainBlock* mainBlockManager);
static int mainBlockMoveUp(MainBlock* mainBlockManager);
static int mainBlockMoveDown(MainBlock* mainBlockManager);
static int mainBlockMoveRight(MainBlock* mainBlockManager);
static int mainBlockMoveLeft(MainBlock* mainBlockManager);
static void mainBlockMoveToOrigin(MainBlock* mainBlockManager);
static int mainBlockMoveOneSpace(MainBlock* mainBlockManager, void(*move)(Block* block), void(*back)(Block* block));
static void mainBlockDrawMainBlock(MainBlock* mainBlockManager);
static void mainBlockEraseMainBlock(MainBlock* mainBlockManager);
static void mainBlockDrawShadowBlock(MainBlock* mainBlockManager);
static void mainBlockEraseShadowBlock(MainBlock* mainBlockManager);

MainBlockFunction* getMainBlockFunction() {
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
static MainBlock* mainBlockCreate(BlockBoard* blockBoard, Block* firstBlock) {

	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	if (firstBlock == NULL) {
		errorPrint("firstBlock is NULL");
	}
	MainBlock* object = (MainBlock*)malloc(sizeof(MainBlock));
	memset(object, 0, sizeof(MainBlock));
	if (object == NULL) {
		errorPrint("memory allocation failed ");
	}

	object->blockBoard = blockBoard;

	mainBlockInitShadowBlock(object);
	mainBlockChangeMainBlock(object, firstBlock);
	mainBlockDrawMainBlock(object);

	mainBlockDrawShadowBlock(object);
	return object;
}

static Block* mainBlockChangeMainBlock(MainBlock* mainBlockManager, Block* block) {	// change main block into block and return origin main block
	if (mainBlockManager == NULL) {
		errorPrint("mainBlockManager is NULL");
	}
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	Block* originBlock = mainBlockManager->mainBlock;

	if(!originBlock == NULL)
		mainBlockEraseMainBlock(mainBlockManager);
	mainBlockManager->mainBlock = block;

	mainBlockMoveToOrigin(mainBlockManager);
	mainBlockDrawMainBlock(mainBlockManager);
	mainBlockUpdateShawdowBlock(mainBlockManager);
	return originBlock;
}
static void mainBlockInitShadowBlock(MainBlock* mainBlockManager) {	// 한 번만 수행
	Block* shadowBlock = BLOCK->create(0, 0, 0, 0, 0);
	GRAPHIC->changeColor(WHITE);
	mainBlockManager->shadowBlock = shadowBlock;
}
static void mainBlockUpdateShawdowBlock(MainBlock* mainBlockManager) {
	Block* shadowBlock = mainBlockManager->shadowBlock;
	Block* mainBlock = mainBlockManager->mainBlock;
	memcpy(shadowBlock, mainBlock, sizeof(Block));
	BLOCK->setLetter(shadowBlock, (char*)"□");
	mainBlockUpdateShawdowBlockPosition(mainBlockManager);
}
static void mainBlockUpdateShawdowBlockPosition(MainBlock* mainBlockManager) {
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

static int mainBlockMoveUp(MainBlock* mainBlockManager) {
	return mainBlockMoveOneSpace(mainBlockManager, BLOCK->moveUp, BLOCK->moveDown);
}
static int mainBlockMoveDown(MainBlock* mainBlockManager) {
	return mainBlockMoveOneSpace(mainBlockManager, BLOCK->moveDown, BLOCK->moveUp);
}
static int mainBlockMoveRight(MainBlock* mainBlockManager) {
	int success = mainBlockMoveOneSpace(mainBlockManager, BLOCK->moveRight, BLOCK->moveLeft);
	if (success) {// 좌우로 움질일 때만 shadowBlock갱신
		mainBlockEraseShadowBlock(mainBlockManager);
		mainBlockUpdateShawdowBlockPosition(mainBlockManager);
		mainBlockDrawShadowBlock(mainBlockManager);
	}
	return success;
}
static int mainBlockMoveLeft(MainBlock* mainBlockManager) {
	int success = mainBlockMoveOneSpace(mainBlockManager, BLOCK->moveLeft, BLOCK->moveRight);
	if (success) {// 좌우로 움질일 때만 shadowBlock갱신
		mainBlockEraseShadowBlock(mainBlockManager);
		mainBlockUpdateShawdowBlockPosition(mainBlockManager);	
		mainBlockDrawShadowBlock(mainBlockManager);
	}
	return success;
}
static void mainBlockMoveToOrigin(MainBlock* mainBlockManager) {
	BlockBoard* blockBoard = mainBlockManager->blockBoard;
	Block* mainBlock = mainBlockManager->mainBlock;
	int destX = blockBoard->x + blockBoard->width/2 - BLOCK_WIDTH/2;
	int destY = blockBoard->y;
	BLOCK->moveTo(mainBlock, destX, destY);
}
// mainBlock에 대해 move를 수행하고 범위를 벗어나면 back를 수행한다.
// 이동 성공 여부 반환
static int mainBlockMoveOneSpace(MainBlock* mainBlockManager, void (*move)(Block* block), void (*back)(Block* block)) {
	int flag = 1;
	if (mainBlockManager == NULL) {
		errorPrint("mainBlockManager is NULL");
	}
	BlockBoard* blockBoard = mainBlockManager->blockBoard;
	Block* mainBlock = mainBlockManager->mainBlock;
	mainBlockEraseMainBlock(mainBlockManager);
	move(mainBlock);
	if (!BLOCK_BOARD->blockPositionPermitCheck(blockBoard, mainBlock)) {
		back(mainBlock);
		flag = 0;
	}
	mainBlockDrawMainBlock(mainBlockManager);
	return flag;
}

static void mainBlockDrawMainBlock(MainBlock* mainBlockManager) {
	BLOCK->drawBlock(mainBlockManager->mainBlock);
}
static void mainBlockEraseMainBlock(MainBlock* mainBlockManager) {
	
	BLOCK->erase(mainBlockManager->mainBlock);
}
static void mainBlockDrawShadowBlock(MainBlock* mainBlockManager) {
	BLOCK->drawBlock(mainBlockManager->shadowBlock);
}
static void mainBlockEraseShadowBlock(MainBlock* mainBlockManager) {
	BLOCK->erase(mainBlockManager->shadowBlock);
}
