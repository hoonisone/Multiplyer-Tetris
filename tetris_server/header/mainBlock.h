#pragma once
#include "mainBlock.h"
#include "blockBoard.h"
#include "block.h"

#define MAIN_BLOCK mainBlockFunctionCreate()
/*
* ��ü ����
	- ��Ʈ�������� Ű����� ���� ������ ����� �ٷ�� ��ü�̴�.
	- ���۵Ǵ� ����� �׸���(���� ������ ǥ��)����� �����Ѵ�.

* ��ü ���� ��
	- MainBlockManager�� ���� ���� �������� �׻� NULL�� �ƴ� �Ӽ��� ���´�.
	- MainBlockManager�� ��� �Ӽ��� ����� �� ����
		-> ��ȯ�� ����(���ο� �Ӽ� ���� �θ鼭 ���� ���� ���� �� �ִ�.)
		-> ������ ��ü ���ο��� �ش� �Ӽ� ����(zero or NULL)
	- mainBlock�� shadowBlock�� ȭ�鿡 �ڵ� ��µȴ�(�׷�����).
	- mainBlock�� bloakBoard������ �����ϸ� board���� �ٸ� ��ϰ� �浹���� �ʴ´�.
	- shadowBlock�� �׻� mainBlock�� �������� ǥ���Ѵ�.

* ��ü ���� ��
	- mainBlock��ȯ�� ���ο� mainBlock�� �ݵ�� board���� Ư�� ��ġ�� �̵��Ѵ�.(��� ������)
*/
typedef struct MainBlock {
	BlockBoard* blockBoard;	// mainBlock�� Ȱ�� ���� (�ش� ������ ��� �� ����.)
	Block* bodyBlock;	// blockBoard���� Ȱ���ϴ� ���
	Block* shadowBlock; // blockBoard�� �������� ��Ÿ���� ���
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