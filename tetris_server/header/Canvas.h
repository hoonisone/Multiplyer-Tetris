#pragma once
#include <vector>
#include "Painter.h"

using namespace std;

class Canvas {
private:
	vector<pair<Painter*, vector<int>>> figures;

public:
	Canvas() {};
	void enrollFigure(Painter* painter, int x, int y) {
		figures.push_back(pair<Painter*, vector<int>> (painter, {x, y}));
	}
	void draw() {
		for (int i = 0; i < figures.size(); i++) {
			Painter* painter = figures[i].first;
			vector<int> pos = figures[i].second;
			painter->point(pos[0], pos[1]);
		}
	}
};