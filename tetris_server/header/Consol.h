#pragma once
#include <Windows.h>
#include <iostream>
/*
콘솔창의 텍스트 색 등 관리
*/
#define WIDTH 200
#define HEIGHT 50

#define BLACK		0
#define BLUE		1
#define GREEN		2
#define AQUA		3
#define RED			4
#define PURPLE		5
#define YELLOW		6
#define WHITE		7
#define GRAY		8
#define LIGHT_BLUE	9
#define LIGHT_GREEN	10
#define LIGHT_AQUA  11
#define LIGHT_RED	12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define LIGHT_WHITE 15

typedef int Color;

using namespace std;

class Consol {
private:
	Consol() {};
public:
	static void changeTextColor(Color color){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
	static void changeBackgroundColor(Color color) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((color & 0xf) << 4) | (info.wAttributes & 0xf));
	}
	static void move(int x, int y) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	static pair<int, int> getCurPos(){
		CONSOLE_SCREEN_BUFFER_INFO a;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
		return make_pair(a.dwCursorPosition.X, a.dwCursorPosition.Y);
	}
	static void clear() {
		system("cls");
	}
	static void changeScreenSize(int width, int height) {
		char order[100];
		sprintf(order, "mode con cols=%d lines=%d", width, height, 100);
		system(order);
	}
	static void fullScreen() {
		SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	}
};