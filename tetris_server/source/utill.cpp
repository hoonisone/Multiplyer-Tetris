#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* newChar(char value) {
	char* ptr = (char*)malloc(sizeof(char));
	*ptr = value;
	return ptr;
}

int* newInt(int value) {
	int* ptr = (int*)malloc(sizeof(int));
	*ptr = value;
	return ptr;
}

float* newFloat(float value) {
	float* ptr = (float*)malloc(sizeof(float));
	*ptr = value;
	
	return ptr;
}

double* newDouble(double value) {
	double* ptr = (double*)malloc(sizeof(double));
	*ptr = value;
	return ptr;
}
char* newString(char* string) {
	char* ptr = (char*)malloc(sizeof(char)* strlen(string)+1);
	strcpy(ptr, string);
	return ptr;
}

int isInRange(int X, int Y, int W, int H, int x, int y) {
	if (X <= x && x < X + W) {
		if (Y <= y && y < Y + H) {
			return 1;
		}
	}
	return 0;
}