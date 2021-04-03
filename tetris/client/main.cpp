#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "clientSocket.h"



int main(int argc, char* argv[])
{
    char ip[100] = "127.0.0.1";
    int port = 5000;
    char buffer[BUFFER_SIZE];
    ClientSocket* cs = clientSocketCreate(ip, port);
    int len = clientSocketReceive(cs, buffer);
    printf("Massage(%d): %s\n", len, buffer);
    clientSocketSend(cs, (char*)"hello");
    clientSocketTerminate(cs);
}
