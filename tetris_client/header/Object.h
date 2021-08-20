#pragma once
/*
- �ܼ�â�� ��µǴ� �߻�ü�̴�.
- ��� ��ġ�� ũ�� �Ӽ��� ���´�.
- ��°� �����, ������Ʈ ���� �޼ҵ带 ���´�.
- ���¸� ��ȭ��Ű�� ��� �Լ��� redraw�Ű������� ���� ����� ���ÿ� ������� �� �ִ�.
*/
class ConsolObject {
protected:

public:
	int x, y;// ��ü�� ��� ��ġ
	int w, h;// ��ü�� ��� ũ��
	ConsolObject(int x, int y, int w, int h) :x(x), y(y), w(w), h(h){};
	virtual void move(int x, int y, bool redraw = true) {	// ��ü�� ��ġ�� �̵�
		this->x = x;
		this->y = y;
		if (redraw) draw();
	}
	//virtual void draw(const int x, const int y) = 0;	// ��ü�� ��ġ�� �����԰� ���ÿ� ����Ѵ�.
	virtual void draw()  = 0;	// ���� ��ġ�� ��ü�� �׸���.
	virtual void update(string data, bool redraw=true) {} // �Է¿� ���� ��ü�� �����Ѵ�.
	virtual void update(char data, bool redraw = true) {} // �Է¿� ���� ��ü�� �����Ѵ�.
	virtual void update(bool redraw = true) {} // �Է¿� ���� ��ü�� �����Ѵ�.
	virtual void erase() = 0;	// ���� ��ġ�� ��ü�� �����.
	int getWidth() {
		return w;
	}
	int getHeight() {
		return h;
	}
};