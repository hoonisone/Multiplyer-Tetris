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
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //���� ���̺귯���� �ʱ�ȭ�ϰ� �ִ�.
                errorPrint("WSAStartup() error!");

            hSocket = socket(PF_INET, SOCK_STREAM, 0); //������ �����ϰ�
            if (hSocket == INVALID_SOCKET)
                errorPrint((char*)"socket() error");

            memset(&servAddr, 0, sizeof(servAddr));
            servAddr.sin_family = AF_INET;
            servAddr.sin_addr.s_addr = inet_addr(ip.c_str());
            servAddr.sin_port = htons(port);

            if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //������ ������ �������� ������ �����û�� �ϰ� �ִ�
                errorPrint((char*)"connect() error!");
        }catch(...) {
            throw;
        };

    };

    string request(string query, string data) {
        string message = query + "/" + data;
        char buffer[BUFFER_SIZE];
        send(hSocket, message.c_str() , BUFFER_SIZE - 1, 0);
        int result = recv(hSocket, buffer, BUFFER_SIZE - 1, 0); //recv �Լ� ȣ���� ���ؼ� �����κ��� ���۵Ǵ� �����͸� �����ϰ� �ִ�.
        return string(buffer);
    }

    void close() {
        closesocket(hSocket); //���� ���̺귯�� ����
        WSACleanup();
    }
};
