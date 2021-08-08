#include <Windows.h>
#include "Consol.h"

void Consol::changeTextColor(Color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void Consol::changeBackgroundColor(Color color){
			CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((color & 0xf) << 4) | (info.wAttributes & 0xf));
}