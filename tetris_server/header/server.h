#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include "error.h"
#include <unordered_map>
#include <thread>
#include <functional>
#include "string+.h"
#define MAX_USER_NUM 100
#define BUFFER_SIZE 1024

/*
query는 하나의 기능을 말하며 handler는 해당 query의 기능을 수행하는 함수이다.
client가 request(query, data)를 보내면 query에 해당하는 handler에 (data)를 입력으로 주어 기능을 수행한다.
*/

using string = std::string;

class Server {
private:
	int port;
	WSADATA wsaData;             // 소켓 라이브러리 정보
	SOCKET serverSocket;         // 서버와 클라이언트 소켓

	std::unordered_map<string, std::function<string(string ip, int port, string data)>> handlers; // request에 따른 handler를 관리
	string requestHandler(string ip, int port, string request) {
		std::vector<string> token = split(request, "/");
		if (token.size() != 2) return "wrongQuery";
		string query = token[0];
		string data = token[1];
		std::cout << query << " " << data << std::endl;
		if (handlers.find(query) == handlers.end()) return "wrongQuery";
		return handlers[query](ip, port, data);
	}
	void initSocketLibrary() {
		if (WSAStartup(MAKEWORD(2, 2), &(wsaData)) != 0)
			errorPrint((char*)"WSAStartup() error!");
	}
	void createServerSocket() {
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (serverSocket == INVALID_SOCKET)
			errorPrint((char*)"socket() error");
	}
	void serverSetting() {
		SOCKADDR_IN serverAddress;   // 서버와 클라이언트 주소 정보
		memset(&serverAddress, 0, sizeof(serverAddress));   // 서버 정보 비우기    
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");  // 서버 ip 주소
		serverAddress.sin_port = htons(port);         // 서버 port 주소

		// 서버 소켓에 서버 정보 등록
		if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) //소켓에 IP주소와 PORT 번호 할당
			errorPrint((char*)"bind() error");
	}
	void startToListen() {
		if (listen(serverSocket, MAX_USER_NUM) == SOCKET_ERROR) //listen 함수호출을 통해서 생성한 소켓을 서버 소켓으로 완성
			errorPrint((char*)"listen() error");
	}
	void connectToClient() {
		SOCKADDR_IN clientAddress;
		int clientAddressSize = sizeof(clientAddress);
		SOCKET clientSocket = accept(serverSocket, reinterpret_cast<SOCKADDR*>(&clientAddress), &clientAddressSize); //클라이언트 연결요청 수락하기 위해 accept함수 호출
		if (clientSocket == INVALID_SOCKET) {
			errorPrint((char*)"accept() error");
		}
		else {
			printf("Client[%s:%d]: SocketConnect\n", inet_ntoa(clientAddress.sin_addr), clientAddress.sin_port);
			requestHandler(inet_ntoa(clientAddress.sin_addr), clientAddress.sin_port, "connect");	// 연결에 대한 핸들러 수행
			std::thread([clientSocket, clientAddress, this](void)->int {
				char buffer[BUFFER_SIZE];
				while (true) {
					int code = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
					if (code == -1) {
						closesocket(clientSocket);  // 클라이언트 소켓 정리
						printf("Client[%s:%d]: SocketDisconnect\n", inet_ntoa(clientAddress.sin_addr), clientAddress.sin_port);
						return 0;
					}
					std::cout << "hello";
					string request(buffer);
					printf("Client[%s:%d]: Receive-\"%s\"\n", inet_ntoa(clientAddress.sin_addr), clientAddress.sin_port, buffer);
					string response = requestHandler(inet_ntoa(clientAddress.sin_addr), clientAddress.sin_port, request);
					strcpy(buffer, response.c_str());
					send(clientSocket, buffer, BUFFER_SIZE - 1, 0);
				}
				}).detach();
		}
	}
public:
	Server(int port) :port(port) {};
	void enroll(string query, std::function<string(string ip, int port, string data)> handler) {
		if (handlers.find(query) != handlers.end()) {
			errorPrint(query + " already exists");
		}
		else {
			handlers[query] = handler;
		}
	}
	void run() {
		initSocketLibrary(); 		// 소켓 라이브러리 초기화
		createServerSocket();		// 서버 소켓 생성 및 세팅
		serverSetting();			// 서버 정보(ip, port) 생성
		startToListen();		// 서버 소켓 작동(메시지 리스닝 모드)

		while (1) {
			connectToClient();
		}
		// 서버 종료(사실 여기까지 제어가 오지 않음)
		closesocket(serverSocket);  // 서버 소켓 정리
		WSACleanup();               // 소켓 라이브러리 정리
	}
};