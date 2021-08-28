#pragma once

#include "UIElement.h"
#include "Painter.h"
#include "Printer.h"
#include "error.h"

class UIListElement :public UIElement {
private:
	int listLen = 10;	// list�� ������ element�� ����
	int startIdx = 0;	// list���� ���� ��ܿ� ������ element�� idx
	// startIdx���� listLen�� ��ŭ �����ش�.
	bool elementSettingFlag = false;
	int elementW = -1;	// ������ ũ���� element�� ������ �Ѵ�. element�� ó�� ����� �� ���� �Ǵ� ���� ���� �����ϴ�.
	int elementH = -1;
	bool checkElementSize(UIElement* element) {	// �ڽ��� ũ�Ⱑ ������ ũ�⿡ �´��� üũ
		return (elementW == element->getWidth() && elementH == element->getHeight());
	}
	void pullDownOneElement() {
		//����Ʈ�� element�Ѱ� ��ŭ ���� ������.
		move(0, elementH - 1, false);
	}
	void pullUpOneElement() {
		//����Ʈ�� element�Ѱ� ��ŭ ���� �ø���.
		move(0, elementH - 1, false);
	}
public:
	UIListElement(int x, int y) :UIElement(x, y, 0, 0, "", 1, 10) { setBorderFlag(false); setTerminalFlag(false); };
	UIListElement(int x, int y, int len) :UIElement(x, y, 0, 0, "", 1, len), listLen(len) { setBorderFlag(false); setTerminalFlag(false); };
	UIListElement(int x, int y, int len, Painter* selectedPainter, Painter* unselectedPainter, Printer* selectedPrinter, Printer* unselectedPrinter) :
		UIElement(x, y, 0, 0, "", selectedPainter, unselectedPainter, selectedPrinter, unselectedPrinter, false, 1, len) {setTerminalFlag(false);};
	void setElementSize(int w, int h) {
		// �� 1���� ���� �����ϴ�.	������ ũ���� element�� ���ϱ� ����
		if (elementSettingFlag == false) {
			elementSettingFlag = true;	// ���̻� �Լ� ȣ�� �Ұ�
			elementW = w;
			elementH = h;
		}
		else {
			errorPrint("element size is already set");	// �̹� ���� �Ǿ��⿡ ���� ����
		}
	}
	void enroll(UIElement* element, int x, int y, bool selectable = true, bool selectFlag = false) override {
		if (elementSettingFlag) {	// elementSize�� �̹� ���� �� ��� (���� size ���� ���� ó�� ����ϴ� ���)
			if (!checkElementSize(element)) {	// ���õ� ũ�⿡ ���� �ʴٸ� ���� ����
				errorPrint("element Size does not match with set size");
			}
		}
		else {	// elementSize�� ���� ���õ��� ���� ���
			setElementSize(element->getWidth(), element->getHeight());	// ���Ե� element�� ũ��� ����
		}
		UIElement::enroll(element, x, y, true, selectFlag);	// ���� enroll �Լ��� �ڽ� ���
	}
	virtual void draw() override {
		int endIdx = min(startIdx + listLen - 1, children.size() - 1);
		for (int i = startIdx; i <= endIdx; i++) {
			children[i]->draw();
		}
		drawBorder();
		drawText();
		getSelectedChild()->draw();
	}
	virtual bool keyInputHandler(char key) override {
		int& y = selectY;	// ���õ� �ڽ��� index;

		switch ((Key)key) {
		case KEY_UP:
			if (selectUpChild())
				if (y < startIdx) {// y�� ��� ������ �հ� ���� Ƣ�����
					startIdx--; // ��� ���� ������ (���� element ����)
					pullDownOneElement(); // ����Ʈ �� ĭ ������
				}
			return true;
			break;	// key�� �ش��ϴ� handling �� ���� �� true��ȯ
		case KEY_DOWN:
			if (selectDownChild()) {
				int endIdx = startIdx + listLen - 1;
				if (y > endIdx) {	// y�� ��� ������ �հ� �Ʒ��� Ƣ�����
					startIdx++;// ��� ���� ������ (���� element ����)
					pullUpOneElement();	// ����Ʈ �� ĭ �ø���
				}
			}
			return true;
			break;
		case KEY_SPACE:
			setRootEndFlag(true);
			return true;
			break;
		}
		return false; // �θ� ��ȯ���� üũ�ϰ� ���� �ڵ鸵 �Ѵ�.
	}
};