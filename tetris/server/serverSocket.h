//#pragma once
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <WinSock2.h>
//
//#define BUFFER_SIZE 1024
//
//typedef struct ServerSocket {
//    WSADATA wsaData;                            // 소켓 라이브러리 정보
//    SOCKET serverSocket, clientSocket;          // 서버와 클라이언트 소켓
//    SOCKADDR_IN serverAddress, clientAddress;   // 서버와 클라이언트 주소 정보
//} ServerSocket;
//
//ServerSocket* serverSocketCreate(int port);         // 초기화
//void serverSocketConnect(ServerSocket* ss);                  // 연결
//void serverSocketSend(ServerSocket* ss, char *buffer);       // 송신
//int serverSocketReceive(ServerSocket* ss, char *buffer);    // 수신
//void serverSocketTerminate(ServerSocket* ss);                // 종료