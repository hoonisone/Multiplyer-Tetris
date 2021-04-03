//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <WinSock2.h>
//#include "error.h"
//#include "serversocket.h"
//
//// �ʱ�ȭ
//ServerSocket* serverSocketCreate(int port) {
//    ServerSocket* ss = (ServerSocket*)malloc(sizeof(ServerSocket));
//
//    // ���� ���̺귯�� �ʱ�ȭ
//    if (WSAStartup(MAKEWORD(2, 2), &(ss->wsaData)) != 0)
//        ErrorHandling((char*)"WSAStartup() error!");
//
//
//    // ���� ���� ����
//    ss->serverSocket = socket(PF_INET, SOCK_STREAM, 0);
//    if (ss->serverSocket == INVALID_SOCKET)
//        ErrorHandling((char*)"socket() error");
//
//
//    // ���� ����(ip, port) ����
//    memset(&(ss->serverAddress), 0, sizeof(ss->serverAddress));   // ���� ���� ����
//    ss->serverAddress.sin_family = AF_INET;
//    ss->serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  // ���� ip �ּ�
//    ss->serverAddress.sin_port = htons(port);         // ���� port �ּ�
//
//
//    // ���� ���Ͽ� ���� ���� ���
//    if (bind(ss->serverSocket, (SOCKADDR*)&ss->serverAddress, sizeof(ss->serverAddress)) == SOCKET_ERROR) //���Ͽ� IP�ּҿ� PORT ��ȣ �Ҵ�
//        ErrorHandling((char*)"bind() error");
//
//
//    // ���� ���� �۵�(�޽��� ������ ���)
//    if (listen(ss->serverSocket, 5) == SOCKET_ERROR) //listen �Լ�ȣ���� ���ؼ� ������ ������ ���� �������� �ϼ�
//        ErrorHandling((char*)"listen() error");
//    
//    ServerSocket* ss = global_ss;
//    int clientAddressSize = sizeof(ss->clientAddress);
//
//    while (1) {
//        printf("connect start\n");
//        ss->clientSocket = accept(ss->serverSocket, (SOCKADDR*)&ss->clientAddress, &clientAddressSize); //Ŭ���̾�Ʈ �����û �����ϱ� ���� accept�Լ� ȣ��
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
//// ����
//void serverSocketConnect(ServerSocket* ss) {
//    // Ŭ���̾�Ʈ ��û ����
//    //int clientAddressSize = sizeof(ss->clientAddress);
//    //ss->clientSocket = accept(ss->serverSocket, (SOCKADDR*)&ss->clientAddress, &clientAddressSize); //Ŭ���̾�Ʈ �����û �����ϱ� ���� accept�Լ� ȣ��
//    //if (ss->clientSocket == INVALID_SOCKET)
//    //    ErrorHandling((char*)"accept() error");
//    global_ss = ss;
//    CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
//}
//
//// �۽�
//void serverSocketSend(ServerSocket* ss, char* buffer) {
//    send(ss->clientSocket, buffer, BUFFER_SIZE, 0); //send�Լ� ȣ���� ���ؼ� ����� Ŭ���̾�Ʈ�� �����͸� ����
//}
//
//// ����
//int serverSocketReceive(ServerSocket* ss, char* buffer) {
//    return recv(ss->clientSocket, buffer, BUFFER_SIZE - 1, 0);
//}
//
//// ����
//void serverSocketTerminate(ServerSocket* ss) {
//    closesocket(ss->clientSocket);  // Ŭ���̾�Ʈ ���� ����
//    closesocket(ss->serverSocket);  // ���� ���� ����
//    WSACleanup();               // ���� ���̺귯�� ����
//    free(ss);
//}