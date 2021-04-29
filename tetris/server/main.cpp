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

#include <conio.h>

void responseHandler(char* request, char* response) {
	if (request) {

	}
	response[0] = NULL;
	strcpy(response, (char*)"hello c world!!!");
}

void Test() {
	ListTestAll();
}

int main(int argc, char* argv[]) {
	//UserManager* um = umCreateUserManager((char*)"userInfor.txt");
	//umReadUserInfor(um);
	//umWriteUserInfor(um);
	serverRun(5000, responseHandler);
}