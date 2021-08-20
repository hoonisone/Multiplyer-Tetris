#pragma once
/*
- 콘솔창에 출력되는 추상객체이다.
- 출력 위치와 크기 속성을 갖는다.
- 출력과 지우기, 업데이트 등의 메소드를 갖는다.
- 상태를 변화시키는 모든 함수는 redraw매개변수를 통해 변경과 동시에 재출력할 수 있다.
*/
class ConsolObject {
protected:

public:
	int x, y;// 객체의 출력 위치
	int w, h;// 객체의 출력 크기
	ConsolObject(int x, int y, int w, int h) :x(x), y(y), w(w), h(h){};
	virtual void move(int x, int y, bool redraw = true) {	// 객체의 위치를 이동
		this->x = x;
		this->y = y;
		if (redraw) draw();
	}
	//virtual void draw(const int x, const int y) = 0;	// 객체의 위치를 변경함과 동시에 출력한다.
	virtual void draw()  = 0;	// 기존 위치에 객체를 그린다.
	virtual void update(string data, bool redraw=true) {} // 입력에 대해 객체를 갱신한다.
	virtual void update(char data, bool redraw = true) {} // 입력에 대해 객체를 갱신한다.
	virtual void update(bool redraw = true) {} // 입력에 대해 객체를 갱신한다.
	virtual void erase() = 0;	// 기존 위치에 객체를 지운다.
	int getWidth() {
		return w;
	}
	int getHeight() {
		return h;
	}
};