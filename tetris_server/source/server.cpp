#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include "error.h"
#include "server.h"


#define MAX_USER_NUM 100
#define BUFFER_SIZE 1024

WSADATA wsaData;             // ���� ���̺귯�� ����
SOCKET serverSocket;         // ������ Ŭ���̾�Ʈ ����
SOCKADDR_IN serverAddress;   // ������ Ŭ���̾�Ʈ �ּ� ����
ClientSocket* _clientSocket;

void (*_responseHandler)(char* request, char* response);

void serverRun(int port, void (*responseHandler)(char* request, char* response)) {
    _responseHandler = responseHandler; // ����(����)������ ���

    // ���� ���̺귯�� �ʱ�ȭ
    if (WSAStartup(MAKEWORD(2, 2), &(wsaData)) != 0)
        errorPrint((char*)"WSAStartup() error!");

    // ���� ���� ����
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
        errorPrint((char*)"socket() error");

    // ���� ����(ip, port) ����
    memset(&serverAddress, 0, sizeof(serverAddress));   // ���� ���� ����    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  // ���� ip �ּ�
    serverAddress.sin_port = htons(port);         // ���� port �ּ�

    // ���� ���Ͽ� ���� ���� ���
    if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) //���Ͽ� IP�ּҿ� PORT ��ȣ �Ҵ�
        errorPrint((char*)"bind() error");

    // ���� ���� �۵�(�޽��� ������ ���)
    if (listen(serverSocket, MAX_USER_NUM) == SOCKET_ERROR) //listen �Լ�ȣ���� ���ؼ� ������ ������ ���� �������� �ϼ�
        errorPrint((char*)"listen() error");

    HANDLE thread1 = CreateThread(NULL, 0, serverConnectHandler, NULL, 0, NULL);  // ���� ���� ��û�� �ް� ����� ������ communicateHandler�� �ѱ��.

    while (1) {}
    // ���� ����(��� ������� ��� ���� ����)
    closesocket(serverSocket);  // ���� ���� ����
    WSACleanup();               // ���� ���̺귯�� ����
}

DWORD WINAPI serverConnectHandler(void* data) {
    while (1) {
        ClientSocket* clientSocket = (ClientSocket*)malloc(sizeof(ClientSocket));
        clientSocket->addressSize = sizeof(clientSocket->address);
        clientSocket->socket = accept(serverSocket, (SOCKADDR*)&(clientSocket->address), &(clientSocket->addressSize)); //Ŭ���̾�Ʈ �����û �����ϱ� ���� accept�Լ� ȣ��
        if (clientSocket->socket == INVALID_SOCKET) {
            errorPrint((char*)"accept() error");
            free(clientSocket);
        }
        else {
            printf("Client[%s:%d]: SocketConnect\n", inet_ntoa(clientSocket->address.sin_addr), clientSocket->address.sin_port);

            _clientSocket = clientSocket;   // ����(����)������ ���
            HANDLE thread2 = CreateThread(NULL, 0, serverCommunicateHandler, NULL, 0, NULL);
        }
    }
    return 0;
}

DWORD WINAPI serverCommunicateHandler(void* data) {
    ClientSocket* clientSocket = _clientSocket; // ����(����)���� ��������
    void (*requestHandling)(char* request, char* response) = _responseHandler; // ����(����)���� ��������
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    while (1) {
        int code = recv(clientSocket->socket, request, BUFFER_SIZE, 0);
        if (code == -1) {
            closesocket(clientSocket->socket);  // Ŭ���̾�Ʈ ���� ����
            free(clientSocket);
            return 0;
        }
        printf("Client[%s:%d]: Receive-\"%s\"\n", inet_ntoa(clientSocket->address.sin_addr), clientSocket->address.sin_port, request);
        requestHandling(request, response);
        printf("%s\n", response);
        send(clientSocket->socket, response, BUFFER_SIZE-1, 0);
    }
    return 0;
}