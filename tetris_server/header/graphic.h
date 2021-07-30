#pragma once

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
#define BRIGHT_WHITE 15

#define LETTER_SIZE 4

#define GRAPHIC createGraphicManager()

#define EMPTY_LETTER (char*)"  "
#define EMPTY_COLOR 0

#define DEFAULT_LETTER_LETTER (char*)"* "
#define DEFAULT_LETTER_COLOR WHITE
#define DEFAULT_BACKGROUND_COLOR BLACK


typedef char Letter[4];
typedef int Color;

typedef struct GraphicManager {
	void (*init)();
	void (*setFullScreen)();
	void (*setScreenSize)(int width, int height);
	void (*setColor)(Color color);
	void (*moveCursor)(int x, int y);
	void (*movePoint)(int x, int y);
	void (*drawPoint)(int x, int y);
	void (*drawVertical)(int x, int y, int len);
	void (*drawHorizontal)(int x, int y, int len);
	void (*drawRectangle)(int x, int y, int width, int height);
	void (*drawFilledRectangle)(int x, int y, int width, int height);
	void (*setLetter)(char* letter);
	void (*drawLineRectangle)(int x, int y, int width, int height);
	void (*setBackgroundColor)(int color);
	void (*del)(GraphicManager* gm);
	void (*erase)();
	void (*printText)(int x, int y, char* text);

} GraphicManager;

GraphicManager* createGraphicManager();