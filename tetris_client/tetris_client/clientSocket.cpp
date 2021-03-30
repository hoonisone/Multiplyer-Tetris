#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "error.h"
#include "clientSocket.h"

ClientSocket* clientSocketCreate(char* ip, int port) {

    ClientSocket* cs = (ClientSocket*)malloc(sizeof(ClientSocket));
    if (WSAStartup(MAKEWORD(2, 2), &cs->wsaData) != 0) //���� ���̺귯���� �ʱ�ȭ�ϰ� �ִ�
        ErrorHandling((char*)"WSAStartup() error!");

    cs->hSocket = socket(PF_INET, SOCK_STREAM, 0); //������ �����ϰ�
    if (cs->hSocket == INVALID_SOCKET)
        ErrorHandling((char*)"socket() error");

    memset(&cs->servAddr, 0, sizeof(cs->servAddr));
    cs->servAddr.sin_family = AF_INET;
    cs->servAddr.sin_addr.s_addr = inet_addr(ip);
    cs->servAddr.sin_port = htons(port);

    if (connect(cs->hSocket, (SOCKADDR*)&cs->servAddr, sizeof(cs->servAddr)) == SOCKET_ERROR) //������ ������ �������� ������ �����û�� �ϰ� �ִ�
        ErrorHandling((char*)"connect() error!");

    return cs;
}

void clientSocketSend(ClientSocket* cs, char* message) {
    send(cs->hSocket, message, BUFFER_SIZE, 0);
}

int clientSocketReceive(ClientSocket* cs, char* buffer) {
    return recv(cs->hSocket, buffer, BUFFER_SIZE - 1, 0); //recv �Լ� ȣ���� ���ؼ� �����κ��� ���۵Ǵ� �����͸� �����ϰ� �ִ�.
}

void clientSocketTerminate(ClientSocket* cs) {
    closesocket(cs->hSocket); //���� ���̺귯�� ����
    WSACleanup();
    free(cs);
}