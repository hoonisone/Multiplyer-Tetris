#pragma once
#include <string>
#include "ColorPainter.h"
#include "ColorPrinter.h"
#include "KeyInput.h"
#include <unordered_map>
#define DEFAULT_SELECTED_PAINTER new ColorPainter({"*"}, AQUA, BLACK)
#define DEFAULT_UNSELECTED_PAINTER new ColorPainter({"*"}, WHITE, BLACK)
#define DEFAULT_SELECTED_PRINTER new ColorPrinter(CENTER, MIDDLE, AQUA, BLACK)
#define DEFAULT_UNSELECTED_PRINTER new ColorPrinter(CENTER, MIDDLE, WHITE, BLACK)

/*
- �ܼ�â�� ��µǴ� �߻�ü�̴�.
- ��� ��ġ�� ũ�� �Ӽ��� ���´�.
- ��°� �����, ������Ʈ ���� �޼ҵ带 ���´�.
- ���¸� ��ȭ��Ű�� ��� �Լ��� redraw�Ű������� ���� ����� ���ÿ� ������� �� �ִ�.
*/
using State = unordered_map<string, string>;
class UIElement {
protected:

	//Parent
	UIElement* parent = NULL;


	//Self
	int x, y, w, h;	// ����� ��ǥ�� ũ��
	bool endFlag = false;	// UI ������ �������� ����
	string name; // ����� �̸�
	bool borderFlag = true;	// �׵θ� ��� ����
	bool terminalFlag = true; // ���� ��� ����
	bool pointableSubElementEnrollFlag = false;	// ���ð����� �ڽ��� �� ���̶󵵵�ϵǾ��°�?
	bool statePropagationFlag = true; // state���� �� ���� ����� state�� �������� ����
	/*
		true: state���� �� �ڱ� �ڽ��� ������ ���� ����� ��� state�� ����
		false: state���� �� �ڱ� �ڽŸ��� state�� ����
	*/
	bool selectPropagationFlag = true; // select �� ���� ��ҷ� �������� ����
	/* - false -> �ݵ�� �ڱ� �ڽ��� ���õ�
	*  - true  -> �ڽ��� �ִٸ� �ѱ�� ���ٸ� �ڱ� �ڽ��� ���õ�
	*/
	bool selectedFlag;// UIManager�� ���� ���õǾ��ִ��� ����(�߿����� ������...)
	Printer* unselectedPrinter = NULL, * selectedPrinter = NULL, * printer = NULL;
	Painter* unselectedPainter = NULL, * selectedPainter = NULL, * painter = NULL;

	

	//Children: ���� ��Ҹ� map�������� ����
	int mapW, mapH;	// map�� ũ��
	vector<vector<pair<UIElement*, bool>>> map;	// ���� ��� map <���, ���ð��� ����>
	vector<UIElement*> children;	// ������� ����Ʈ (map�� ���ϴ� ��� ��Ҹ� �����Ѵ�.)
	int selectPointX, selectPointY;	// ���õǴ� ����� map������ ��ǥ
	/* - ���� ��Ұ� �ϳ��� �ִٸ� ��ȿ�� ���� ���´�.
	*/


	void setSelectedState() {
		selectedFlag = true;
		printer = selectedPrinter;
		painter = selectedPainter;
	}
	void setUnselectedState() {
		selectedFlag = false;
		printer = unselectedPrinter;
		painter = unselectedPainter;
	}\

	bool checkSubElementPosRange(int x, int y) { return 0 <= x && x < mapW && 0 <= y && y < mapH; }
	bool checkSubElementExist(int x, int y) {
		return checkSubElementPosRange(x, y) && (map[y][x].first != NULL);
	}
	bool checkSubElementPointable(int x, int y) {
		return checkSubElementExist(x, y) && (map[y][x].second);
	}
	bool checkSubElementsIsEmpty() {
		return children.size() == 0;
	}

	void pointOtherSubElement(int x, int y) {
		if (!checkSubElementExist(x, y)) {
			errorPrint("no exist");
		}
		else {
			this->selectPointX = x;
			this->selectPointY = y;
		}
	}
	void selectOtherSubElement(int x, int y, bool redraw = true) {	// �ٸ� �ڽ� ��Ҹ� �����Ѵ�.
		if (!checkSubElementExist(x, y)) {
			errorPrint("no exist");
		}
		else {
			unselect(redraw);
			pointOtherSubElement(x, y);
			select(redraw);
		}
	}
	UIElement* getPointedSubElement() {
		if (checkSubElementsIsEmpty())// �ڽ��� �ִ� ��츸 ȣ��Ǿ�� �Ѵ�.
			errorPrint("no child"); 

		// �ڽ��� �����ϸ� �ݵ�� ��ȿ�� �ڽ��� �ִ�.
		return map[selectPointY][selectPointX].first; // ���õǾ��ִ� �ڽ� ��ȯ
	}	 
	int getSubElementNum() {
		return children.size();
	}
	void drawBorder() {
		if (borderFlag)	painter->rectBorder(x, y, w, h, CURSOR_STD);
	}
	void drawText() {
		vector<string>tokens = split(name, "\n");
		printer->printText(x + painter->getWidth(), y + painter->getHeight(), w - 2 * painter->getWidth(), h - 2 * painter->getHeight(), tokens);
	}


	bool selectUpChild(bool redraw = true) {	// ���� ���� ���� ��� ������ ������ �� ���� ���� ��ȯ
		if (checkSubElementPointable(selectPointX, selectPointY - 1)) {
			selectOtherSubElement(selectPointX, selectPointY - 1, redraw);
			return true;
		}
		return false;
	}
	bool selectDownChild(bool redraw = true) {
		if (checkSubElementPointable(selectPointX, selectPointY + 1)) {
			selectOtherSubElement(selectPointX, selectPointY + 1, redraw);
			return true;
		}
		cout << checkSubElementPosRange(selectPointX, selectPointY + 1) << endl;
		cout << checkSubElementExist(selectPointX, selectPointY + 1) << endl;
		return false;
	}
	bool selectRightChild(bool redraw = true) {
		if (checkSubElementPointable(selectPointX + 1, selectPointY)) {
			selectOtherSubElement(selectPointX + 1, selectPointY, redraw);
			return true;
		}
		return false;
	}
	bool selectLeftChild(bool redraw = true) {
		if (checkSubElementPointable(selectPointX - 1, selectPointY)) {
			selectOtherSubElement(selectPointX - 1, selectPointY, redraw);
			return true;
		}
		return false;
	}
	virtual void select(bool redraw = true) {	// (����)������ ��Ҹ� �����Ѵ�.
		if (selectPropagationFlag) {
			if (checkSubElementsIsEmpty()) {
				setSelectedState();
			}
			else {
				getPointedSubElement()->select(false);	// ��¥�� �Լ� ������ �ٽñ׸� ���̱� ������ ������ ��Ұ� �ٽ� �׷��� �ʿ� ����
			}
		}
		else {
			setSelectedState();
			for (auto child : children) {	// ���� terminal�̱� ������ ������ ���� ��Ҵ� ��� �θ� ������.
				child->select(false);
			}
		}
		if (redraw)draw();
	}
	virtual void unselect(bool redraw = true) {// (����)������ ��Ҹ� ���� ����Ѵ�.
		if (selectPropagationFlag) {
			if (checkSubElementsIsEmpty()) {
				setUnselectedState();
			}
			else {
				getPointedSubElement()->unselect(false);	// ��¥�� �Լ� ������ �ٽñ׸� ���̱� ������ ������ ��Ұ� �ٽ� �׷��� �ʿ� ����
			}
		}
		else {
			setUnselectedState();
			for (auto child : children) {	// ���� terminal�̱� ������ ������ ���� ��Ҵ� ��� �θ� ������.
				child->unselect(false);
			}
		}
		if (redraw)draw();
	}
	
	State(*customizedGetState)(UIElement& element) = NULL;	// ����� ���� getState()
	// tool
	void combineState(State& s1, const State& s2) {	// s2�� s1�� �����ش�.
		try {
			for (auto s : s2) {
				s1[s.first] = s.second;
			}
		}catch(...) {
			errorPrint("maybe same key alread exist!");
		}
	}
public:
	UIElement(int x, int y, int w, int h, string text) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, 0, 0) {};
	UIElement(int x, int y, int w, int h, string text, int mapW, int mapY) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, mapW, mapY) {};
	UIElement(int x, int y, int w, int h, string text, Painter* selectedPainter, Painter* unselectedPainter, Printer* selectedPrinter, Printer* unselectedPrinter, bool borderFlag, int mapW, int mapH) :
		x(x), y(y), w(w), h(h), name(text),
		selectedPainter(selectedPainter), unselectedPainter(unselectedPainter),
		selectedPrinter(selectedPrinter), unselectedPrinter(unselectedPrinter),
		borderFlag(borderFlag), mapW(mapW), mapH(mapH) {
		map = vector<vector<pair<UIElement*, bool>>>(mapH, vector<pair<UIElement*, bool>>(mapW, pair<UIElement*, bool>(NULL, false)));
		unselect(false);

	};


	// setter
	void setParent(UIElement* parent) { this->parent = parent; }
	void setBorderFlag(bool borderFlag) {
		this->borderFlag = borderFlag;
	}
	void setTerminalFlag(bool terminalFlag) { this->terminalFlag = terminalFlag; }
	void setRootEndFlag(bool endFlag) {	// root�� endFlag�� ���� ������ ����// ���Ḧ ���� ���
		if (parent != NULL) {
			parent->setRootEndFlag(endFlag);
		}
		else {
			this->endFlag = endFlag;
		}
	}
	void setSelectPropagationFlag(bool flag) {
		this->selectPropagationFlag = flag;
	}
	void setStatepropagationFlag(bool flag) {
		this->statePropagationFlag = flag;
	}

	//getter
	string getName() { return name; }
	int getWidth() { return w; }
	int getHeight() { return h; }
	UIElement* getSelectedSubElement() {	// element���� ���������� ���õǾ��ִ� ���� �ڽĳ�� ��ȯ
		if (selectPropagationFlag) {	//���� ���ο� ����
			if (!checkSubElementsIsEmpty()) {	// �ڽ��� �ִٸ� ����
				return getPointedSubElement()->getSelectedSubElement();
			}else{ // �ڽ��� ���ٸ� �ڱ� �ڽ��̴�.
				return this;
			}
		}
		else {	// �������� �ʴ´ٸ� �ڱ� �ڽ��̴�.
			return this;
		}
	}
	virtual State getWholeState() {	// �ڱ� �ڽŰ� �ڽſ��� ���� ��� ���� ����� state�� �����Ͽ� ��ȯ
		State state = getState();	// �ڽ��� state����
		if (statePropagationFlag) {	// ���� ���ο� ���� ���� ��� state �߰�
			State childState = getSubElementState();
			combineState(state, childState);
		}
		return state;
	}
	virtual State getState() {	// �ڽ��� state�� ��ȯ
		if (customizedGetState != NULL) {	// ����� ���� �Լ� �켱
			return customizedGetState(*this);
		}
		else {
			State state;
			if (name != "") {	// �̸��� ���ٸ� state�� ������ ����
				state[name] = "";
			}
			return state;

		}
	}
	virtual State getSubElementState() {
		State state;
		for (int i = 0; i < children.size(); i++) {	// ��� ���� ����� state�� ��´�.
			State childState = children[i]->getWholeState();
			combineState(state, childState);
		}
		return state;
	}
	bool checkEnd() { return endFlag; }


	virtual void enroll(UIElement* element, int x, int y, bool selectable = true, bool selectFlag = false) {
		// ��� �Ұ��� ���� ó��
		if (!checkSubElementPosRange(x, y) || checkSubElementExist(x, y)) {
			char errorBuffer[100];
			sprintf(errorBuffer, "can not enroll button in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}

		// �ڽ� ���  
		element->setParent(this);	// �ڽ� ��忡 �ڽ��� �θ�� ����Ѵ�.
		children.push_back(element);	// �ڽ� ��� ���
		element->move(this->x, this->y, false);	// �θ��� ��ǥ�� �������� ��ġ ������
		map[y][x] = make_pair(element, selectable);

		if (pointableSubElementEnrollFlag == false && selectable) {	// ó������ ��ϵ� ���
			pointableSubElementEnrollFlag = true;
			pointOtherSubElement(x, y);
			select(false);
		}
		else if (selectFlag) {
			selectOtherSubElement(x, y, false);
		}
		else {
			element->unselect(false);
		}
	}

	virtual void move(int dx, int dy, bool redraw = true) {
		if (redraw)erase();
		this->x += dx;
		this->y += dy;
		for (int i = 0; i < children.size(); i++) {
			children[i]->move(dx, dy, redraw);
		}
		if (redraw) draw();
	}
	virtual void moveTo(int x, int y, bool redraw = true) {	// ��ü�� (x, y)�� �̵�
		move(x - this->x, y - this->y, redraw);
	}


	// plot
	virtual void draw() {
		for (int i = 0; i < children.size(); i++) {
			children[i]->draw();
		}
		drawBorder();
		drawText();

	};
	virtual void redraw() {
		erase();
		draw();
	}
	void drawAllText() {//All�� �ڽ��� ��� ����
		for (int i = 0; i < children.size(); i++) {
			children[i]->drawAllText();
		}
		drawText();
		if (!terminalFlag) {
			if (getPointedSubElement() != NULL) {
				getPointedSubElement()->draw();
			}
		}
	}
	virtual void erase() {
		Painter::GetEraser(w, h).point(x, y);	// ��ü�� ũ��� ���� ������ ���� �ٷ�� Painter�� �ش� ��ġ�� ���� ��´�.
		//Painter({ " " }).rect(x, y, w, h);
	};	// ���� ��ġ�� ��ü�� �����.


	//handler
	virtual bool keyInputHandler(char key) {
		/*	key �Է¿� ���� handling(ó��)�� �� ���� ���� ��ȯ
			�ڽ� -> �ڽ� -> �θ� ������ ������ �� ���� ��ͷ� �̾�����.
		*/
		if (selectPropagationFlag) {	// ������ҷ� ����
			if (!checkSubElementsIsEmpty()) {
				UIElement* selectedChild = getPointedSubElement();	// ���õ� �ڽ��� ã�´�.
				if (selectedChild->keyInputHandler(key)) { // ���õ� �ڽ� ��尡 �����ϸ� �ڵ鸵�� �����ϸ� true��ȯ
					return true;
				}
			}
		}
		switch ((Key)key) {
		case KEY_UP:    if (selectUpChild())		return true; break;	// key�� �ش��ϴ� handling �� ���� �� true��ȯ
		case KEY_DOWN:  if (selectDownChild())	return true; break;
		case KEY_LEFT:  if (selectLeftChild())	return true; break;
		case KEY_RIGHT: if (selectRightChild())	return true; break;
		case KEY_SPACE: setRootEndFlag(true); return true; break;
			return false; // �θ� ��ȯ���� üũ�ϰ� ���� �ڵ鸵 �Ѵ�.
		}
	}
};