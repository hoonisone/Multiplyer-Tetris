#pragma once
#include <Windows.h>
#include <iostream>
#pragma warning(disable : 4996)
/*
콘솔창의 텍스트 색 등 관리
*/
#define WIDTH 200
#define HEIGHT 50

enum Color { BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE, GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE };

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
	static void setCursorFlag(bool flag){
		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
		cursorInfo.bVisible = flag; //커서 Visible TRUE(보임) FALSE(숨김)
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}
};