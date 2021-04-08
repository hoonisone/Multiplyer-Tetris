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
	if (request) {

	}
	strcpy(response, "hello c world!!!");
}

int main(int argc, char* argv[]) {
	//ListTestAll();
	UserManager* um = umCreateUserManager((char*)"userInfor.txt");
	umReadUserInfor(um);
	listPrintAllElement(um->users);
	umRemoveUser(um, userCreateUser((char*)"apple"));
	umRemoveUser(um, userCreateUser((char*)"apple"));
	umRemoveUser(um, userCreateUser((char*)"apple"));
	printf("***\n");
	listPrintAllElement(um->users);
	umWriteUserInfor(um);

	printf("count = %d\n", listCountElement(um->users, userCreateUser((char*)"apple")));

	//char buffer[100] = "asdf/asdgb/wertg/dfh/wertg/wertg/";
	//List* list = split(buffer, (char*)"/");
	//printf("hello");
	//listPrintAllElement(list);

	//serverRun(5000, responseHandler);
}