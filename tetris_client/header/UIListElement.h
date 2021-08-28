#pragma once

#include "UIElement.h"
#include "Painter.h"
#include "Printer.h"
#include "error.h"

class UIListElement :public UIElement {
private:
	int listLen = 10;	// list에 보여줄 element의 개수
	int startIdx = 0;	// list에서 가장 상단에 보여줄 element의 idx
	// startIdx부터 listLen개 만큼 보여준다.
	bool elementSettingFlag = false;
	int elementW = -1;	// 동일한 크기의 element를 가져야 한다. element를 처음 등록할 때 세팅 또는 직접 세팅 가능하다.
	int elementH = -1;
	bool checkElementSize(UIElement* element) {	// 자식의 크기가 정해진 크기에 맞는지 체크
		return (elementW == element->getWidth() && elementH == element->getHeight());
	}
	void pullDownOneElement() {
		//리스트를 element한개 만큼 끌어 내린다.
		move(0, elementH - 1, false);
	}
	void pullUpOneElement() {
		//리스트를 element한개 만큼 끌어 올린다.
		move(0, elementH - 1, false);
	}
public:
	UIListElement(int x, int y) :UIElement(x, y, 0, 0, "", 1, 10) { setBorderFlag(false); setTerminalFlag(false); };
	UIListElement(int x, int y, int len) :UIElement(x, y, 0, 0, "", 1, len), listLen(len) { setBorderFlag(false); setTerminalFlag(false); };
	UIListElement(int x, int y, int len, Painter* selectedPainter, Painter* unselectedPainter, Printer* selectedPrinter, Printer* unselectedPrinter) :
		UIElement(x, y, 0, 0, "", selectedPainter, unselectedPainter, selectedPrinter, unselectedPrinter, false, 1, len) {setTerminalFlag(false);};
	void setElementSize(int w, int h) {
		// 단 1번만 세팅 가능하다.	동일한 크기의 element를 지니기 위함
		if (elementSettingFlag == false) {
			elementSettingFlag = true;	// 더이상 함수 호출 불가
			elementW = w;
			elementH = h;
		}
		else {
			errorPrint("element size is already set");	// 이미 세팅 되었기에 오류 생성
		}
	}
	void enroll(UIElement* element, int x, int y, bool selectable = true, bool selectFlag = false) override {
		if (elementSettingFlag) {	// elementSize가 이미 세팅 된 경우 (직접 size 세팅 없이 처음 등록하는 경우)
			if (!checkElementSize(element)) {	// 세팅된 크기에 맞지 않다면 에러 생성
				errorPrint("element Size does not match with set size");
			}
		}
		else {	// elementSize가 아직 세팅되지 않은 경우
			setElementSize(element->getWidth(), element->getHeight());	// 삽입될 element의 크기로 세팅
		}
		UIElement::enroll(element, x, y, true, selectFlag);	// 기존 enroll 함수로 자식 등록
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
		int& y = selectY;	// 선택된 자식의 index;

		switch ((Key)key) {
		case KEY_UP:
			if (selectUpChild())
				if (y < startIdx) {// y가 출력 범위를 뚫고 위로 튀어나오면
					startIdx--; // 출력 범위 재조정 (이전 element 부터)
					pullDownOneElement(); // 리스트 한 칸 내리기
				}
			return true;
			break;	// key에 해당하는 handling 후 성공 시 true반환
		case KEY_DOWN:
			if (selectDownChild()) {
				int endIdx = startIdx + listLen - 1;
				if (y > endIdx) {	// y가 출력 범위를 뚫고 아래로 튀어나오면
					startIdx++;// 출력 범위 재조정 (다음 element 부터)
					pullUpOneElement();	// 리스트 한 칸 올리기
				}
			}
			return true;
			break;
		case KEY_SPACE:
			setRootEndFlag(true);
			return true;
			break;
		}
		return false; // 부모가 반환값을 체크하고 직접 핸들링 한다.
	}
};