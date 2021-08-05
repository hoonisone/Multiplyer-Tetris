//#include <stdio.h>
//#include <windows.h>
//#include "pen.h"
//#include "pen2D.h"
//#include <string.h>
//#include "coordinate.h"
//#include "string.h"
//
//static Shape textShape;
//static Pen* usingPen = NULL;
//
//static void press(Pen2* pen2);
//
//Pen2* createPen2(Color textColor, Color backgroundColor, Shape2 textShape, int width, int height) {
//	Pen2* object = (Pen2*)malloc(sizeof(Pen2));
//	object->pen = PEN(textColor, backgroundColor, (char*)"");
//	memcpy(object->textShape, textShape, sizeof(object->textShape));
//	//setShape(object, textShape);
//	object->press = press;
//	object->width = width;
//	object->height = height;
//	return object;
//}
//
//void setShape(Pen2* pen2, Shape2 textShape) {
//	for (int i = 0; i < 10; i++) {
//		if (textShape[i] == NULL) {
//			break;
//		}
//		strcpy(pen2->textShape[i], textShape[i]);
//	}
//}
//
//static void press(Pen2* pen2) {
//	pen2->pen->press(pen2->pen);
//	COORD coord = getXY();
//	int X = coord.X;
//	int Y = coord.Y;
//	for (int y = 0; y < pen2->height; y++) {
//			CURSOR->move(X, Y+y);
//			printf("%s", pen2->textShape[y]);
//	}
//}