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
query�� �ϳ��� ����� ���ϸ� handler�� �ش� query�� ����� �����ϴ� �Լ��̴�.
client�� request(query, data)�� ������ query�� �ش��ϴ� handler�� (data)�� �Է����� �־� ����� �����Ѵ�.
*/

using string = std::string;

class Server {
private:
	int port;
	WSADATA wsaData;             // ���� ���̺귯�� ����
	SOCKET serverSocket;         // ������ Ŭ���̾�Ʈ ����

	std::unordered_map<string, std::function<string(string ip, int port, string data)>> handlers; // request�� ���� handler�� ����
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
		SOCKADDR_IN serverAddress;   // ������ Ŭ���̾�Ʈ �ּ� ����
		memset(&serverAddress, 0, sizeof(serverAddress));   // ���� ���� ����    
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");  // ���� ip �ּ�
		serverAddress.sin_port = htons(port);         // ���� port �ּ�

		// ���� ���Ͽ� ���� ���� ���
		if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) //���Ͽ� IP�ּҿ� PORT ��ȣ �Ҵ�
			errorPrint((char*)"bind() error");
	}
	void startToListen() {
		if (listen(serverSocket, MAX_USER_NUM) == SOCKET_ERROR) //listen �Լ�ȣ���� ���ؼ� ������ ������ ���� �������� �ϼ�
			errorPrint((char*)"listen() error");
	}
	void connectToClient() {
		SOCKADDR_IN clientAddress;
		int clientAddressSize = sizeof(clientAddress);
		SOCKET clientSocket = accept(serverSocket, reinterpret_cast<SOCKADDR*>(&clientAddress), &clientAddressSize); //Ŭ���̾�Ʈ �����û �����ϱ� ���� accept�Լ� ȣ��
		if (clientSocket == INVALID_SOCKET) {
			errorPrint((char*)"accept() error");
		}
		else {
			printf("Client[%s:%d]: SocketConnect\n", inet_ntoa(clientAddress.sin_addr), clientAddress.sin_port);
			requestHandler(inet_ntoa(clientAddress.sin_addr), clientAddress.sin_port, "connect");	// ���ῡ ���� �ڵ鷯 ����
			std::thread([clientSocket, clientAddress, this](void)->int {
				char buffer[BUFFER_SIZE];
				while (true) {
					int code = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
					if (code == -1) {
						closesocket(clientSocket);  // Ŭ���̾�Ʈ ���� ����
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
		initSocketLibrary(); 		// ���� ���̺귯�� �ʱ�ȭ
		createServerSocket();		// ���� ���� ���� �� ����
		serverSetting();			// ���� ����(ip, port) ����
		startToListen();		// ���� ���� �۵�(�޽��� ������ ���)

		while (1) {
			connectToClient();
		}
		// ���� ����(��� ������� ��� ���� ����)
		closesocket(serverSocket);  // ���� ���� ����
		WSACleanup();               // ���� ���̺귯�� ����
	}
};