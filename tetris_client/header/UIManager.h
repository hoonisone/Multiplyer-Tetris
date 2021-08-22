//#pragma once
//#include "UIElement.h"
//#include "error.h"
//#include "string+.h"
//#include <vector>
//
//#pragma warning(disable : 4996)
//
//using namespace std;
///*
//키 입력을 받아 버튼을 선택 동작 시킨다.
//방향키는 버튼 이동(선택)
//스페이스는 버튼 클릭(선택된 버튼 정보를 반환한다.)
//나머지 키는 버튼에게 넘겨 핸들링한다.
//*/
//class UIManager: public UIElement{
//private:
//	int width, height;
//	int x = 0, y = 0;
//	vector<vector<UIElement*>> map;
//	
//	bool rangeCheck(int x, int y) {return 0 <= x && x < width && 0 <= y && y < height;}
//	bool existCheck(int x, int y) { return map[y][x] != NULL; }
//	void select(int x, int y, bool redraw = true) {
//		if (existCheck(this->x, this->y)) {
//			map[this->y][this->x]->unselect(redraw);
//		}
//		this->x = x;
//		this->y = y;
//		map[this->y][this->x]->select(redraw);
//	}
//
//	string (*action)(UIManager* button) = NULL;
//	UIElement* getSelectedUIElement() {
//		return map[y][x];
//	}
//public:
//	vector<UIElement*> getButtons() {
//		return blocks;
//	}
//	UIManager(int x, int y, int w, int h, int width, int height):UIElement(x, y, w, h), width(width), height(height) {
//		map = vector<vector<UIElement*>>(height, vector<UIElement*>(width, NULL));
//	}
//
//
//	void draw()const {
//		for (int i = 0; i < blocks.size(); i++) {
//			blocks[i]->draw();
//		}
//		map[this->y][this->x]->draw();	// 선택된 버튼을 맨 위로 올리기 위해 다시 한번 그리기
//	}
//	void erase() {
//		for (int i = 0; i < blocks.size(); i++) {
//			blocks[i]->erase();
//		}
//	}
//
//	void keyInputHandler(char key, UIManager* um) override{
//		switch ((Key)key) {
//		case KEY_UP:    
//			if (!up() && um != NULL)	// 이동 실패 시
//				um->up();
//			break;
//		case KEY_DOWN:  
//			if (!down() && um != NULL)	// 이동 실패 시
//				um->down();
//			break;
//		case KEY_LEFT:  
//			if (!left() && um != NULL)	// 이동 실패 시
//				um->left();
//			break;
//		case KEY_RIGHT: 
//			if (!right() && um != NULL)	// 이동 실패 시
//				um->right();
//			break;
//		default: 
//			getSelectedUIElement()->keyInputHandler(key, this); 
//			break;	// 방향키 이외의 입력은 scanner에게 넘긴다.
//		}
//	}
//	~UIManager() {
//		for (int i = 0; i < blocks.size(); i++) {
//			delete blocks[i];
//		}
//	}
//
//};