#include <WinSock2.h>

#define BUFFER_SIZE 1024

typedef struct ClientSocket {
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;
} ClientSocket;

ClientSocket* clientSocketCreate(char* ip, int port);
void clientSocketSend(ClientSocket* cs, char* message);
int clientSocketReceive(ClientSocket* cs, char* buffer);
void clientSocketTerminate(ClientSocket* cs);