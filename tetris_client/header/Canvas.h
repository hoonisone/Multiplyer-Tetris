#pragma once
#include <vector>
#include "Painter.h"

using namespace std;

class Canvas {
private:
	vector<pair<Painter*, vector<int>>> figures;
	void (*updateHandler)(Canvas* object) = NULL;	// ���� �ݺ� ����� ���� �����Ͽ� ������Ʈ �Լ��� �ۼ��Ͽ� ����
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
	void update() {	// ���̳����� ������ ���� �Լ� -> �ۿ��� ������ ȣ�����ش�.
		if (updateHandler != NULL) {
			updateHandler(this);
		}
	}
	void erase() {
		for (int i = 0; i < figures.size(); i++) {
			Painter* painter = figures[i].first;
			vector<int> pos = figures[i].second;
			Painter({ " " }).rect(pos[0], pos[1], painter->getWidth(), painter->getHeight());	// ���� �����
		}
	}
};