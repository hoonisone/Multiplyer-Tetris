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

void Test() {
	ListTestAll();

}
int main(int argc, char* argv[]) {
	UserManager* um = umCreateUserManager((char*)"userInfor.txt");
	umReadUserInfor(um);
	umWriteUserInfor(um);
	listPrintAllElement(um->users);
	printf("count = %d\n", listCountElement(um->users, userCreateUser((char*)"apple")));

	//char buffer[100] = "asdf/asdgb/wertg/dfh/wertg/wertg/";
	//List* list = split(buffer, (char*)"/");
	//printf("hello");
	//listPrintAllElement(list);

	//serverRun(5000, responseHandler);
}