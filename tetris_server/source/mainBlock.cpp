#include "mainBlock.h"
#include "error.h"


static MainBlock* mainBlockCreate(BlockBoard* blockBoard, Block* firstBlock);
static Block* mainBlockChangeBlock(MainBlock* mainBlock, Block* block);
static void mainBlockInitShadowBlock(MainBlock* mainBlock);
static void mainBlockUpdateShawdowBlockShape(MainBlock* mainBlock);
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
static int overlapCheck(MainBlock* mainBlock);
static int shadowDrawCheck(MainBlock* mainBlock);

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
	mainBlockUpdateShawdowBlockShape(object);
	mainBlockUpdateShawdowBlockPosition(object);
	mainBlockDrawShadowBlock(object);
	mainBlockDrawMainBlock(object);
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
	mainBlockUpdateShawdowBlockShape(mainBlock);
	mainBlockUpdateShawdowBlockPosition(mainBlock);
	mainBlockDrawShadowBlock(mainBlock);
	mainBlockDrawMainBlock(mainBlock);
	return originBlock;
}
static void mainBlockInitShadowBlock(MainBlock* mainBlock) {	// 한 번만 수행
	Block* shadowBlock = BLOCK->create(0, 0, 0, 0, 0);
	GRAPHIC->changeColor(WHITE);
	mainBlock->shadowBlock = shadowBlock;
}
static void mainBlockUpdateShawdowBlockShape(MainBlock* mainBlock) {
	Block* shadowBlock = mainBlock->shadowBlock;
	Block* bodyBlock = mainBlock->bodyBlock;
	memcpy(shadowBlock, bodyBlock, sizeof(Block));
	BLOCK->setLetter(shadowBlock, (char*)"□");
}
static void mainBlockUpdateShawdowBlockPosition(MainBlock* mainBlock) {
	BlockBoard* blockBoard = mainBlock->blockBoard;
	Block* bodyBlock = mainBlock->bodyBlock;
	Block* shadowBlock = mainBlock->shadowBlock;
	int originY = bodyBlock->y;
	while (BLOCK_BOARD->blockPositionPermitCheck(blockBoard, bodyBlock)) {	// mainBlock을 끝까지 내린다.
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
	return mainBlockMoveOneSpace(mainBlock, BLOCK->moveRight, BLOCK->moveLeft);
}
static int mainBlockMoveLeft(MainBlock* mainBlock) {
	return mainBlockMoveOneSpace(mainBlock, BLOCK->moveLeft, BLOCK->moveRight);
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
// mainBlock에 대해 move를 수행하고 범위를 벗어나면 back를 수행한다.
// 이동 성공 여부 반환
static int mainBlockTurnRight(MainBlock* mainBlock) {
	return mainBlockMoveOneSpace(mainBlock, BLOCK->turnRight, BLOCK->turnLeft);
}
static int mainBlockTurnLeft(MainBlock* mainBlock) {
	return mainBlockMoveOneSpace(mainBlock, BLOCK->turnLeft, BLOCK->turnRight);
}
static int mainBlockMoveOneSpace(MainBlock* mainBlock, void (*move)(Block* block), void (*back)(Block* block)) {
	int flag = 1;
	if (mainBlock == NULL) {
		errorPrint("mainBlockManager is NULL");
	}
	BlockBoard* blockBoard = mainBlock->blockBoard;
	Block* bodyBlock = mainBlock->bodyBlock;
	mainBlockEraseMainBlock(mainBlock);
	mainBlockEraseShadowBlock(mainBlock);
	move(bodyBlock);
	if (!BLOCK_BOARD->blockPositionPermitCheck(blockBoard, bodyBlock)) {
		back(bodyBlock);
		flag = 0;
	}
	mainBlockUpdateShawdowBlockShape(mainBlock);
	mainBlockUpdateShawdowBlockPosition(mainBlock);
	mainBlockDrawShadowBlock(mainBlock);
	mainBlockDrawMainBlock(mainBlock);
	return flag;

}
static void mainBlockDrawMainBlock(MainBlock* mainBlock) {
	BLOCK->draw(mainBlock->bodyBlock);
}
static void mainBlockEraseMainBlock(MainBlock* mainBlock) {
	BLOCK->erase(mainBlock->bodyBlock);
}
static void mainBlockDrawShadowBlock(MainBlock* mainBlock) {
	if (shadowDrawCheck(mainBlock)) {
		BLOCK->draw(mainBlock->shadowBlock);
	}
}
static void mainBlockEraseShadowBlock(MainBlock* mainBlock) {
	if (shadowDrawCheck(mainBlock)) {
		BLOCK->erase(mainBlock->shadowBlock);
	}
}
static int overlapCheck(MainBlock* mainBlock) {
	Block* body = mainBlock->bodyBlock;
	int(*bShape)[BLOCK_WIDTH] = BLOCK->getShape(body);
	int bx = body->x;
	int by = body->y;
	Block* shadow = mainBlock->shadowBlock;
	int(*sShape)[BLOCK_WIDTH] = BLOCK->getShape(shadow);
	int sx = shadow->x;
	int sy = shadow->y;
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (BLOCK->rangeCheck(body, sx + x, sy + y)) {
				if (bShape[y+sy-by][x+sx-bx] == 1 && sShape[y][x] == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
}

static int shadowDrawCheck(MainBlock* mainBlock) {
	mainBlock->shadowBlock->y--;
	int check = !overlapCheck(mainBlock);
	mainBlock->shadowBlock->y++;
	return check;
}