#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "error.h"
#include "list.h"
#include "user.h"
#include "utill.h"
#include "string+.h"
#include "file.h"
#include "userManager.h"

void responseHandler(char* request, char* response) {
	/*if (strcmp(request, "hello") == 0) {
		strcpy(response, "hello");
	}
	else {
		
	}*/

	strcpy(response, "hello c world!!!");
	return;
}

void Test() {
	ListTestAll();

}
struct Person {
	int a;
	int b;
} person;
int main(int argc, char* argv[]) {
	serverRun(5000, responseHandler);
}