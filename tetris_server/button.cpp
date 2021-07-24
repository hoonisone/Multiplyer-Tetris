#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"
#include "string+.h"
#include "button.h"

Button* buttonCreate(int x, int y, int width, int height, char* name, int textAlign, void(*action)()) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonSetX(object, x);
	buttonSetY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	buttonSetTextAlgin(object, textAlign);
	object->action = action;

	return object;
}

void buttonSetX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonSetY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if (width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->width = height;
}

void buttonSelect(Button* button) {
	button->selectFlag = 1;
}

void buttonUnselect(Button* button) {
	button->selectFlag = 0;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void buttonSetTextAlgin(Button* button, int textAlgin) {
	if(textAlgin < 0 || textAlgin > 2)
		errorPrint("Range error");
	button->textAlign = textAlgin;
}
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"
#include "string+.h"
#include "button.h"

Button* buttonCreate(int x, int y, int width, int height, char* name, int textAlign, void(*action)()) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonSetX(object, x);
	buttonSetY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	buttonSetTextAlgin(object, textAlign);
	object->action = action;

	return object;
}

void buttonSetX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonSetY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if (width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->width = height;
}

void buttonSelect(Button* button) {
	button->selectFlag = 1;
}

void buttonUnselect(Button* button) {
	button->selectFlag = 0;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void buttonSetTextAlgin(Button* button, int textAlgin) {
	if (textAlgin < 0 || textAlgin > 2)
		errorPrint("Range error");
	button->textAlign = textAlgin;
}

void draw(Button* button) {
	if (button->selectFlag = 0) {
		GRAPHIC->changeColor(BLACK);
	}
	else if (button->selectFlag = 1) {
		GRAPHIC->changeColor(GREEN);
	}
	GRAPHIC->drawLineRectangle(button->x, button->y, button->width, button->height);
	textPrintAlign(button->x, button->y, button->width, button->height, button->name, button->textAlign);
}#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"
#include "string+.h"
#include "button.h"

Button* buttonCreate(int x, int y, int width, int height, char* name, int textAlign, void(*action)()) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonSetX(object, x);
	buttonSetY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	buttonSetTextAlgin(object, textAlign);
	object->action = action;

	return object;
}

void buttonSetX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonSetY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if (width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->width = height;
}

void buttonSelect(Button* button) {
	button->selectFlag = 1;
}

void buttonUnselect(Button* button) {
	button->selectFlag = 0;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void buttonSetTextAlgin(Button* button, int textAlgin) {
	if (textAlgin < 0 || textAlgin > 2)
		errorPrint("Range error");
	button->textAlign = textAlgin;
}

void draw(Button* button) {
	if (button->selectFlag = 0) {
		GRAPHIC->changeColor(BLACK);
	}
	else if (button->selectFlag = 1) {
		GRAPHIC->changeColor(GREEN);
	}
	GRAPHIC->drawLineRectangle(button->x, button->y, button->width, button->height);
	textPrintAlign(button->x, button->y, button->width, button->height, button->name, button->textAlign);
}#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"
#include "string+.h"
#include "button.h"

Button* buttonCreate(int x, int y, int width, int height, char* name, int textAlign, void(*action)()) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonSetX(object, x);
	buttonSetY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	buttonSetTextAlgin(object, textAlign);
	object->action = action;

	return object;
}

void buttonSetX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonSetY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if (width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->width = height;
}

void buttonSelect(Button* button) {
	button->selectFlag = 1;
}

void buttonUnselect(Button* button) {
	button->selectFlag = 0;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void buttonSetTextAlgin(Button* button, int textAlgin) {
	if (textAlgin < 0 || textAlgin > 2)
		errorPrint("Range error");
	button->textAlign = textAlgin;
}

void draw(Button* button) {
	if (button->selectFlag = 0) {
		GRAPHIC->changeColor(BLACK);
	}
	else if (button->selectFlag = 1) {
		GRAPHIC->changeColor(GREEN);
	}
	GRAPHIC->drawLineRectangle(button->x, button->y, button->width, button->height);
	textPrintAlign(button->x, button->y, button->width, button->height, button->name, button->textAlign);
}#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"
#include "string+.h"
#include "button.h"

Button* buttonCreate(int x, int y, int width, int height, char* name, int textAlign, void(*action)()) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonSetX(object, x);
	buttonSetY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	buttonSetTextAlgin(object, textAlign);
	object->action = action;

	return object;
}

void buttonSetX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonSetY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if (width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->width = height;
}

void buttonSelect(Button* button) {
	button->selectFlag = 1;
}

void buttonUnselect(Button* button) {
	button->selectFlag = 0;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void buttonSetTextAlgin(Button* button, int textAlgin) {
	if (textAlgin < 0 || textAlgin > 2)
		errorPrint("Range error");
	button->textAlign = textAlgin;
}

void draw(Button* button) {
	if (button->selectFlag = 0) {
		GRAPHIC->changeColor(BLACK);
	}
	else if (button->selectFlag = 1) {
		GRAPHIC->changeColor(GREEN);
	}
	GRAPHIC->drawLineRectangle(button->x, button->y, button->width, button->height);
	textPrintAlign(button->x, button->y, button->width, button->height, button->name, button->textAlign);
}#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"
#include "string+.h"
#include "button.h"

Button* buttonCreate(int x, int y, int width, int height, char* name, int textAlign, void(*action)()) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonSetX(object, x);
	buttonSetY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	buttonSetTextAlgin(object, textAlign);
	object->action = action;

	return object;
}

void buttonSetX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonSetY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if (width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->width = height;
}

void buttonSelect(Button* button) {
	button->selectFlag = 1;
}

void buttonUnselect(Button* button) {
	button->selectFlag = 0;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void buttonSetTextAlgin(Button* button, int textAlgin) {
	if (textAlgin < 0 || textAlgin > 2)
		errorPrint("Range error");
	button->textAlign = textAlgin;
}

void draw(Button* button) {
	if (button->selectFlag = 0) {
		GRAPHIC->changeColor(BLACK);
	}
	else if (button->selectFlag = 1) {
		GRAPHIC->changeColor(GREEN);
	}
	GRAPHIC->drawLineRectangle(button->x, button->y, button->width, button->height);
	textPrintAlign(button->x, button->y, button->width, button->height, button->name, button->textAlign);
}
void draw(Button* button) {
	if (button->selectFlag = 0) {
		GRAPHIC->changeColor(BLACK);
	}
	else if (button->selectFlag = 1) {
		GRAPHIC->changeColor(GREEN);
	}
	GRAPHIC->drawLineRectangle(button->x, button->y, button->width, button->height);
	textPrintAlign(button->x, button->y, button->width, button->height, button->name, button->textAlign);
}