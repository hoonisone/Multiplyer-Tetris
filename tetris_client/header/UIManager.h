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
//Ű �Է��� �޾� ��ư�� ���� ���� ��Ų��.
//����Ű�� ��ư �̵�(����)
//�����̽��� ��ư Ŭ��(���õ� ��ư ������ ��ȯ�Ѵ�.)
//������ Ű�� ��ư���� �Ѱ� �ڵ鸵�Ѵ�.
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
//		map[this->y][this->x]->draw();	// ���õ� ��ư�� �� ���� �ø��� ���� �ٽ� �ѹ� �׸���
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
//			if (!up() && um != NULL)	// �̵� ���� ��
//				um->up();
//			break;
//		case KEY_DOWN:  
//			if (!down() && um != NULL)	// �̵� ���� ��
//				um->down();
//			break;
//		case KEY_LEFT:  
//			if (!left() && um != NULL)	// �̵� ���� ��
//				um->left();
//			break;
//		case KEY_RIGHT: 
//			if (!right() && um != NULL)	// �̵� ���� ��
//				um->right();
//			break;
//		default: 
//			getSelectedUIElement()->keyInputHandler(key, this); 
//			break;	// ����Ű �̿��� �Է��� scanner���� �ѱ��.
//		}
//	}
//	~UIManager() {
//		for (int i = 0; i < blocks.size(); i++) {
//			delete blocks[i];
//		}
//	}
//
//};