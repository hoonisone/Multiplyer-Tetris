//#pragma once
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <WinSock2.h>
//
//#define BUFFER_SIZE 1024
//
//typedef struct ServerSocket {
//    WSADATA wsaData;                            // ���� ���̺귯�� ����
//    SOCKET serverSocket, clientSocket;          // ������ Ŭ���̾�Ʈ ����
//    SOCKADDR_IN serverAddress, clientAddress;   // ������ Ŭ���̾�Ʈ �ּ� ����
//} ServerSocket;
//
//ServerSocket* serverSocketCreate(int port);         // �ʱ�ȭ
//void serverSocketConnect(ServerSocket* ss);                  // ����
//void serverSocketSend(ServerSocket* ss, char *buffer);       // �۽�
//int serverSocketReceive(ServerSocket* ss, char *buffer);    // ����
//void serverSocketTerminate(ServerSocket* ss);                // ����