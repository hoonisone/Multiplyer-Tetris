#pragma once
#include "mainBlock.h"
#include "blockBoard.h"
#include "block.h"

#define MAIN_BLOCK mainBlockFunctionCreate()
/*
* 객체 설명
	- 테트리스에서 키보드로 조작 가능한 블록을 다루는 객체이다.
	- 조작되는 블록의 그림자(최종 목적지 표시)기능을 지원한다.

* 객체 상태 명세
	- MainBlockManager는 생성 부터 삭제까지 항상 NULL이 아닌 속성을 갖는다.
	- MainBlockManager의 모든 속성은 복사될 수 없다
		-> 교환만 가능(새로운 속성 값을 두면서 기존 값을 취할 수 있다.)
		-> 꺼내는 객체 내부에서 해당 속성 삭제(zero or NULL)
	- mainBlock과 shadowBlock은 화면에 자동 출력된다(그려진다).
	- mainBlock은 bloakBoard내에만 존재하며 board내의 다른 블록과 충돌하지 않는다.
	- shadowBlock은 항상 mainBlock의 목적지를 표현한다.

* 객체 동작 명세
	- mainBlock교환시 새로운 mainBlock은 반드시 board내의 특정 위치로 이동한다.(블록 시작점)
*/
typedef struct MainBlock {
	BlockBoard* blockBoard;	// mainBlock의 활동 공간 (해당 공간을 벗어날 수 없다.)
	Block* bodyBlock;	// blockBoard에서 활동하는 블록
	Block* shadowBlock; // blockBoard의 목적지를 나타내는 블록
};

typedef struct MainBlockFunction {
	MainBlock* (*create)(BlockBoard* blockBoard, Block* firstBlock);
	Block* (*changeBlock)(MainBlock* mainBlockManager, Block* block);
	int (*moveDown)(MainBlock* mainBlock);
	int (*moveRight)(MainBlock* mainBlock);
	int (*moveLeft)(MainBlock* mainBlock);
	int (*turnRight)(MainBlock* mainBlock);
	int (*turnLeft)(MainBlock* mainBlock);
};

MainBlockFunction* mainBlockFunctionCreate();