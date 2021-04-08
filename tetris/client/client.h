#include <WinSock2.h>

#define BUFFER_SIZE 1024

typedef struct ClientSocket {
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;
} ClientSocket;

ClientSocket* clientSocketCreate(char* ip, int port);
int clientSocketRequest(ClientSocket* cs, char* message);
void clientSocketTerminate(ClientSocket* cs);