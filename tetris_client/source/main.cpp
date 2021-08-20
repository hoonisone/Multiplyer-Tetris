#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "client.h"
#include "bean.h"
#define SCENE_LOGIN 0
#define COMMAND_SIZE 1024

char ip[100] = "127.0.0.1";
int port = 5000;
char request[BUFFER_SIZE];
char response[BUFFER_SIZE];
int scene = SCENE_LOGIN;
ClientSocket* cs;

int main(int argc, char* argv[])
{
    cs = clientSocketCreate(ip, port);
    while (1) {

        switch (scene) {
        case SCENE_LOGIN:
            gets_s(request, BUFFER_SIZE);
            int len = clientSocketRequest(cs, request, response);
            printf("Massage(%d): %s\n", len, response);
        }

    }
    clientSocketTerminate(cs);
 

    //Consol::changeScreenSize(WIDTH, HEIGHT);
    //Consol::setCursorFlag(false);
    //Bean::getDirector()->run("main menu");
}
