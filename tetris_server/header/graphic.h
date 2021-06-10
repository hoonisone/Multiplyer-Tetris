#define BLACK		0
#define BLUE		1
#define GERRN		2
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

void graphicChangeColor(int color);
void graphicMoveCursor(int x, int y);

void graphicMovePoint(int x, int y);

void graphicDrawPoint(int x, int y);
void graphicDrawVertical(int x, int y, int len);
void graphicDrawHorizontal(int x, int y, int len);
void graphicDrawRectangle(int x, int y, int width, int height);
void graphicChangeLetter(char *letter);

void graphicDrawLineRectangle(int x, int y, int width, int height);
