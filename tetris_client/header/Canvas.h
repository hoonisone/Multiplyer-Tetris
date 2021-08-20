#pragma once
#include <vector>
#include "Painter.h"

using namespace std;

class Canvas {
private:
	vector<pair<Painter*, vector<int>>> figures;
	void (*updateHandler)(Canvas* object) = NULL;	// 무한 반복 실행될 것을 가정하여 업데이트 함수를 작성하여 삽입
public:
	Canvas() {};
	void enrollFigure(Painter* painter, int x, int y) {
		figures.push_back(pair<Painter*, vector<int>> (painter, vector<int>({x, y})));
	}
	void draw() {
		for (int i = 0; i < figures.size(); i++) {
			Painter* painter = figures[i].first;
			vector<int> pos = figures[i].second;
			painter->point(pos[0], pos[1]);
		}
	}
	void setUpdateHandler(void (*updateHandler)(Canvas* object)) {
		this->updateHandler = updateHandler;
	}
	void update() {	// 다이나믹한 연출을 위한 함수 -> 밖에서 무한히 호출해준다.
		if (updateHandler != NULL) {
			updateHandler(this);
		}
	}
	void erase() {
		for (int i = 0; i < figures.size(); i++) {
			Painter* painter = figures[i].first;
			vector<int> pos = figures[i].second;
			Painter({ " " }).rect(pos[0], pos[1], painter->getWidth(), painter->getHeight());	// 도형 지우기
		}
	}
};