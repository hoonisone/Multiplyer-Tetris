#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include "error.h"
#include "server.h"


#define MAX_USER_NUM 100
#define BUFFER_SIZE 1024

WSADATA wsaData;             // 소켓 라이브러리 정보
SOCKET serverSocket;         // 서버와 클라이언트 소켓
SOCKADDR_IN serverAddress;   // 서버와 클라이언트 주소 정보
ClientSocket* _clientSocket;

void (*_responseHandler)(char* request, char* response);

void serverRun(int port, void (*responseHandler)(char* request, char* response)) {
    _responseHandler = responseHandler; // 전역(공유)변수로 등록

    // 소켓 라이브러리 초기화
    if (WSAStartup(MAKEWORD(2, 2), &(wsaData)) != 0)
        errorPrint((char*)"WSAStartup() error!");

    // 서버 소켓 생성
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
        errorPrint((char*)"socket() error");

    // 서버 정보(ip, port) 생성
    memset(&serverAddress, 0, sizeof(serverAddress));   // 서버 정보 비우기    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  // 서버 ip 주소
    serverAddress.sin_port = htons(port);         // 서버 port 주소

    // 서버 소켓에 서버 정보 등록
    if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) //소켓에 IP주소와 PORT 번호 할당
        errorPrint((char*)"bind() error");

    // 서버 소켓 작동(메시지 리스닝 모드)
    if (listen(serverSocket, MAX_USER_NUM) == SOCKET_ERROR) //listen 함수호출을 통해서 생성한 소켓을 서버 소켓으로 완성
        errorPrint((char*)"listen() error");

    HANDLE thread1 = CreateThread(NULL, 0, serverConnectHandler, NULL, 0, NULL);  // 소켓 연결 요청을 받고 연결된 소켓을 communicateHandler에 넘긴다.

    while (1) {}
    // 서버 종료(사실 여기까지 제어가 오지 않음)
    closesocket(serverSocket);  // 서버 소켓 정리
    WSACleanup();               // 소켓 라이브러리 정리
}

DWORD WINAPI serverConnectHandler(void* data) {
    while (1) {
        ClientSocket* clientSocket = (ClientSocket*)malloc(sizeof(ClientSocket));
        clientSocket->addressSize = sizeof(clientSocket->address);
        clientSocket->socket = accept(serverSocket, (SOCKADDR*)&(clientSocket->address), &(clientSocket->addressSize)); //클라이언트 연결요청 수락하기 위해 accept함수 호출
        if (clientSocket->socket == INVALID_SOCKET) {
            errorPrint((char*)"accept() error");
            free(clientSocket);
        }
        else {
            printf("Client[%s:%d]: SocketConnect\n", inet_ntoa(clientSocket->address.sin_addr), clientSocket->address.sin_port);

            _clientSocket = clientSocket;   // 전역(공유)변수로 등록
            HANDLE thread2 = CreateThread(NULL, 0, serverCommunicateHandler, NULL, 0, NULL);
        }
    }
    return 0;
}

DWORD WINAPI serverCommunicateHandler(void* data) {
    ClientSocket* clientSocket = _clientSocket; // 전역(공유)변수 가져오기
    void (*requestHandling)(char* request, char* response) = _responseHandler; // 전역(공유)변수 가져오기
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    while (1) {
        int code = recv(clientSocket->socket, request, BUFFER_SIZE, 0);
        if (code == -1) {
            closesocket(clientSocket->socket);  // 클라이언트 소켓 정리
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