#pragma once

#define FILE_NAME_SIZE 100
#define FILE_LINE_SIZE 1024

typedef struct UserManager {
	char fileName[FILE_NAME_SIZE];
	List* users; // User List
};

UserManager* umCreateUserManager(char* fileName);
void umEnrollUser(UserManager* um, User* user);
void umRemoveUser(UserManager* um, User* user);

void umReadUserInfor(UserManager* um);
void umWriteUserInfor(UserManager* um);

int userEqual(const Data data1, const Data data2);
int userCompare(const Data data1, const Data data2);
void userPrint(const Data data);
void userDelete(Data data);