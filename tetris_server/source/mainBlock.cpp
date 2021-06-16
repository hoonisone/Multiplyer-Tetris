#include "mainBlock.h"
#include "error.h"


static MainBlock* mainBlockCreate(BlockBoard* blockBoard, Block* firstBlock);
static Block* mainBlockChangeBlock(MainBlock* mainBlock, Block* block);
static void mainBlockInitShadowBlock(MainBlock* mainBlock);
static void mainBlockUpdateShawdowBlock(MainBlock* mainBlock);
static void mainBlockUpdateShawdowBlockPosition(MainBlock* mainBlock);
static int mainBlockMoveUp(MainBlock* mainBlock);
static int mainBlockMoveDown(MainBlock* mainBlock);
static int mainBlockMoveRight(MainBlock* mainBlock);
static int mainBlockMoveLeft(MainBlock* mainBlock);
static void mainBlockPullDown(MainBlock* mainBlock);
static void mainBlockMoveToOrigin(MainBlock* mainBlock);
static int mainBlockTurnRight(MainBlock* mainBlock);
static int mainBlockTurnLeft(MainBlock* mainBlock);
static int mainBlockMoveOneSpace(MainBlock* mainBlock, void(*move)(Block* block), void(*back)(Block* block));
static void mainBlockDrawMainBlock(MainBlock* mainBlock);
static void mainBlockEraseMainBlock(MainBlock* mainBlock);
static void mainBlockDrawShadowBlock(MainBlock* mainBlock);
static void mainBlockEraseShadowBlock(MainBlock* mainBlock);

MainBlockFunction* mainBlockFunctionCreate() {
	static MainBlockFunction* object = NULL;
	if (object == NULL) {
		object = (MainBlockFunction*)malloc(sizeof(MainBlockFunction));
		object->create = mainBlockCreate;
		object->changeBlock = mainBlockChangeBlock;
		object->moveDown = mainBlockMoveDown;
		object->moveRight = mainBlockMoveRight;
		object->moveLeft = mainBlockMoveLeft;
		object->turnRight = mainBlockTurnRight;
		object->turnLeft = mainBlockTurnLeft;
		object->pullDown = mainBlockPullDown;
	}
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


	object->bodyBlock = firstBlock;
	mainBlockMoveToOrigin(object);
	mainBlockInitShadowBlock(object);
	mainBlockUpdateShawdowBlock(object);
	mainBlockDrawMainBlock(object);
	mainBlockDrawShadowBlock(object);
	return object;
}

static Block* mainBlockChangeBlock(MainBlock* mainBlock, Block* block) {	// change main block into block and return origin main block
	if (mainBlock == NULL) {
		errorPrint("mainBlockManager is NULL");
	}
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	Block* originBlock = mainBlock->bodyBlock;
	mainBlockEraseMainBlock(mainBlock);
	mainBlockEraseShadowBlock(mainBlock);
	mainBlock->bodyBlock = block;
	mainBlockMoveToOrigin(mainBlock);
	mainBlockUpdateShawdowBlock(mainBlock);
	mainBlockDrawMainBlock(mainBlock);
	mainBlockDrawShadowBlock(mainBlock);
	return originBlock;
}
static void mainBlockInitShadowBlock(MainBlock* mainBlock) {	// �� ���� ����
	Block* shadowBlock = BLOCK->create(0, 0, 0, 0, 0);
	GRAPHIC->changeColor(WHITE);
	mainBlock->shadowBlock = shadowBlock;
}
static void mainBlockUpdateShawdowBlock(MainBlock* mainBlock) {
	Block* shadowBlock = mainBlock->shadowBlock;
	Block* bodyBlock = mainBlock->bodyBlock;
	memcpy(shadowBlock, bodyBlock, sizeof(Block));
	BLOCK->setLetter(shadowBlock, (char*)"��");
	mainBlockUpdateShawdowBlockPosition(mainBlock);
}
static void mainBlockUpdateShawdowBlockPosition(MainBlock* mainBlock) {
	BlockBoard* blockBoard = mainBlock->blockBoard;
	Block* bodyBlock = mainBlock->bodyBlock;
	Block* shadowBlock = mainBlock->shadowBlock;
	int originY = bodyBlock->y;
	while (BLOCK_BOARD->blockPositionPermitCheck(blockBoard, bodyBlock)) {	// mainBlock�� ������ ������.
		BLOCK->moveDown(bodyBlock);
	}
	BLOCK->moveUp(bodyBlock);
	shadowBlock->y = bodyBlock->y;
	shadowBlock->x = bodyBlock->x;
	bodyBlock->y = originY;
}

static int mainBlockMoveUp(MainBlock* mainBlock) {
	return mainBlockMoveOneSpace(mainBlock, BLOCK->moveUp, BLOCK->moveDown);
}
static int mainBlockMoveDown(MainBlock* mainBlock) {
	return mainBlockMoveOneSpace(mainBlock, BLOCK->moveDown, BLOCK->moveUp);
}
static int mainBlockMoveRight(MainBlock* mainBlock) {
	int success = mainBlockMoveOneSpace(mainBlock, BLOCK->moveRight, BLOCK->moveLeft);
	if (success) {
		mainBlockEraseShadowBlock(mainBlock);
		mainBlockUpdateShawdowBlockPosition(mainBlock);
		mainBlockDrawShadowBlock(mainBlock);
	}
	return success;
}
static int mainBlockMoveLeft(MainBlock* mainBlock) {
	int success = mainBlockMoveOneSpace(mainBlock, BLOCK->moveLeft, BLOCK->moveRight);
	if (success) {
		mainBlockEraseShadowBlock(mainBlock);
		mainBlockUpdateShawdowBlockPosition(mainBlock);	
		mainBlockDrawShadowBlock(mainBlock);
	}
	return success;
}
static void mainBlockPullDown(MainBlock* mainBlock) {
	int destY = mainBlock->shadowBlock->y;
	while(mainBlock->bodyBlock->y < destY){
		mainBlockMoveDown(mainBlock);
		_sleep(10);
	}
}
static void mainBlockMoveToOrigin(MainBlock* mainBlock) {
	BlockBoard* blockBoard = mainBlock->blockBoard;
	Block* bodyBlock = mainBlock->bodyBlock;
	int destX = blockBoard->x + blockBoard->width/2 - BLOCK_WIDTH/2;
	int destY = blockBoard->y;
	BLOCK->moveTo(bodyBlock, destX, destY);
}
// mainBlock�� ���� move�� �����ϰ� ������ ����� back�� �����Ѵ�.
// �̵� ���� ���� ��ȯ
static int mainBlockTurnRight(MainBlock* mainBlock) {
	int success = mainBlockMoveOneSpace(mainBlock, BLOCK->turnRight, BLOCK->turnLeft);
	if (success) {
		mainBlockEraseShadowBlock(mainBlock);
		mainBlockUpdateShawdowBlock(mainBlock);
		mainBlockDrawShadowBlock(mainBlock);
	}
	return success;
}
static int mainBlockTurnLeft(MainBlock* mainBlock) {
	int success = mainBlockMoveOneSpace(mainBlock, BLOCK->turnLeft, BLOCK->turnRight);
	if (success) {
		mainBlockEraseShadowBlock(mainBlock);
		mainBlockUpdateShawdowBlock(mainBlock);
		mainBlockDrawShadowBlock(mainBlock);
	}
	return success;
}
static int mainBlockMoveOneSpace(MainBlock* mainBlock, void (*move)(Block* block), void (*back)(Block* block)) {
	int flag = 1;
	if (mainBlock == NULL) {
		errorPrint("mainBlockManager is NULL");
	}
	BlockBoard* blockBoard = mainBlock->blockBoard;
	Block* bodyBlock = mainBlock->bodyBlock;
	mainBlockEraseMainBlock(mainBlock);
	move(bodyBlock);
	if (!BLOCK_BOARD->blockPositionPermitCheck(blockBoard, bodyBlock)) {
		back(bodyBlock);
		flag = 0;
	}
	mainBlockDrawMainBlock(mainBlock);
	return flag;
}
static void mainBlockDrawMainBlock(MainBlock* mainBlock) {
	BLOCK->drawBlock(mainBlock->bodyBlock);
}
static void mainBlockEraseMainBlock(MainBlock* mainBlock) {
	
	BLOCK->erase(mainBlock->bodyBlock);
}
static void mainBlockDrawShadowBlock(MainBlock* mainBlock) {
	BLOCK->drawBlock(mainBlock->shadowBlock);
}
static void mainBlockEraseShadowBlock(MainBlock* mainBlock) {
	BLOCK->erase(mainBlock->shadowBlock);
}