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

#define EMPTY_LETTER (char*)"  "
#define EMPTY_COLOR 0

#define DEFAULT_LETTER_LETTER (char*)"* "
#define DEFAULT_LETTER_COLOR WHITE
#define DEFAULT_BACKGROUND_COLOR BLACK

#define PEN createPen

typedef char Shape[10][10];
typedef int Color;


typedef struct Pen {
	int width, height;
	Color textColor, backgroundColor;
	Shape textShape;
	int settingFlag;
	void (*press)(Pen* pen);
} Pen;

Pen* createPen(Color textColor, Color backgroundColor, Shape textShape, int width, int height);