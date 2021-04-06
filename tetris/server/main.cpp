#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "error.h"
#include "list.h"
#include "user.h"
#include "list_test.h"
void responseHandler(char* request, char* response) {
	if (request) {

	}
	strcpy(response, "hello c world!!!");
}

int main(int argc, char* argv[]) {
	/*ListTestAll();*/
	//serverRun(5000, responseHandler);
}