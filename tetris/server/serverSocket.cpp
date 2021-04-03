//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <WinSock2.h>
//#include "error.h"
//#include "serversocket.h"
//
//// 초기화
//ServerSocket* serverSocketCreate(int port) {
//    ServerSocket* ss = (ServerSocket*)malloc(sizeof(ServerSocket));
//
//    // 소켓 라이브러리 초기화
//    if (WSAStartup(MAKEWORD(2, 2), &(ss->wsaData)) != 0)
//        ErrorHandling((char*)"WSAStartup() error!");
//
//
//    // 서버 소켓 생성
//    ss->serverSocket = socket(PF_INET, SOCK_STREAM, 0);
//    if (ss->serverSocket == INVALID_SOCKET)
//        ErrorHandling((char*)"socket() error");
//
//
//    // 서버 정보(ip, port) 생성
//    memset(&(ss->serverAddress), 0, sizeof(ss->serverAddress));   // 서버 정보 비우기
//    ss->serverAddress.sin_family = AF_INET;
//    ss->serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  // 서버 ip 주소
//    ss->serverAddress.sin_port = htons(port);         // 서버 port 주소
//
//
//    // 서버 소켓에 서버 정보 등록
//    if (bind(ss->serverSocket, (SOCKADDR*)&ss->serverAddress, sizeof(ss->serverAddress)) == SOCKET_ERROR) //소켓에 IP주소와 PORT 번호 할당
//        ErrorHandling((char*)"bind() error");
//
//
//    // 서버 소켓 작동(메시지 리스닝 모드)
//    if (listen(ss->serverSocket, 5) == SOCKET_ERROR) //listen 함수호출을 통해서 생성한 소켓을 서버 소켓으로 완성
//        ErrorHandling((char*)"listen() error");
//    
//    ServerSocket* ss = global_ss;
//    int clientAddressSize = sizeof(ss->clientAddress);
//
//    while (1) {
//        printf("connect start\n");
//        ss->clientSocket = accept(ss->serverSocket, (SOCKADDR*)&ss->clientAddress, &clientAddressSize); //클라이언트 연결요청 수락하기 위해 accept함수 호출
//        printf("connect end\n");
//        if (ss->clientSocket == INVALID_SOCKET)
//            ErrorHandling((char*)"accept() error");
//        ServerSocket* global_ss;
//    }
//
//    return ss;
//}
//
//ServerSocket* global_ss;
//
//DWORD WINAPI ThreadFunc1(void* data) {
//    ServerSocket* global_ss;
//}
//// 연결
//void serverSocketConnect(ServerSocket* ss) {
//    // 클라이언트 요청 수락
//    //int clientAddressSize = sizeof(ss->clientAddress);
//    //ss->clientSocket = accept(ss->serverSocket, (SOCKADDR*)&ss->clientAddress, &clientAddressSize); //클라이언트 연결요청 수락하기 위해 accept함수 호출
//    //if (ss->clientSocket == INVALID_SOCKET)
//    //    ErrorHandling((char*)"accept() error");
//    global_ss = ss;
//    CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
//}
//
//// 송신
//void serverSocketSend(ServerSocket* ss, char* buffer) {
//    send(ss->clientSocket, buffer, BUFFER_SIZE, 0); //send함수 호출을 통해서 연결된 클라이언트에 데이터를 전송
//}
//
//// 수신
//int serverSocketReceive(ServerSocket* ss, char* buffer) {
//    return recv(ss->clientSocket, buffer, BUFFER_SIZE - 1, 0);
//}
//
//// 종료
//void serverSocketTerminate(ServerSocket* ss) {
//    closesocket(ss->clientSocket);  // 클라이언트 소켓 정리
//    closesocket(ss->serverSocket);  // 서버 소켓 정리
//    WSACleanup();               // 소켓 라이브러리 정리
//    free(ss);
//}