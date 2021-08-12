#pragma once
#include <vector>
#include "Block.h"
#include "Consol.h"
#include "Painter.h"

static const vector<Color> colors = { BLUE, GREEN, AQUA, RED, PURPLE, YELLOW };

using namespace std;
class BlockCreator {
public:
	virtual Block* createBlock() = 0;
};

class SamePointBlockCreator : public BlockCreator {
private:
	PointShape pointShape;
public:
	SamePointBlockCreator(PointShape pointShape) : pointShape(pointShape) {};
	virtual Block* createBlock() {
			Color color = colors[Random::randomInt() % colors.size()];
			ColorPainter* painter = new ColorPainter(pointShape, color, BLACK);
			BlockName blockShape = (BlockName)Random::randomInt();
			BlockAngle angle = Random::randomInt();
			return new Block(0, 0, blockShape, angle, painter);
	}
};