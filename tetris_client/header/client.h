#pragma once
#include <WinSock2.h>
#include "error.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning(disable : 4996)
#define BUFFER_SIZE 1024

class Client {
private:
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;
    string ip;
    int port;
public:
    Client(string ip, int port) :ip(ip), port(port) {
        try {
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리를 초기화하고 있다.
                errorPrint("WSAStartup() error!");

            hSocket = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성하고
            if (hSocket == INVALID_SOCKET)
                errorPrint((char*)"socket() error");

            memset(&servAddr, 0, sizeof(servAddr));
            servAddr.sin_family = AF_INET;
            servAddr.sin_addr.s_addr = inet_addr(ip.c_str());
            servAddr.sin_port = htons(port);

            if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //생성된 소켓을 바탕으로 서버에 연결요청을 하고 있다
                errorPrint((char*)"connect() error!");
        }catch(...) {
            throw;
        };

    };

    string request(string query, string data) {
        string message = query + "/" + data;
        char buffer[BUFFER_SIZE];
        send(hSocket, message.c_str() , BUFFER_SIZE - 1, 0);
        int result = recv(hSocket, buffer, BUFFER_SIZE - 1, 0); //recv 함수 호출을 통해서 서버로부터 전송되는 데이터를 수신하고 있다.
        return string(buffer);
    }

    void close() {
        closesocket(hSocket); //소켓 라이브러리 해제
        WSACleanup();
    }
};
