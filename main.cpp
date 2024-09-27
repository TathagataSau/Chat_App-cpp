#include <bits/stdc++.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>

using namespace std;
#pragma comment(lib, "ws2_32.lib")
/*
1. Initialize the Winsock library
2. create the socket
3. get IP and Port
4. bind the IP and port with the socket
5. Listen on the socket
6. Accept (blocking)
7. receive and send
8. close the socket
9. cleanup the winsocket
*/

bool Initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main() {
	if (!Initialize()) {
		cout << "Winsock Initialization failed!!"<<endl;
		return 1;
	}

	cout << "Server Program " << endl;

	// api = socket(ipv4 or ipv6, tcp or udp, protocol)
	// in socket programing or api always check if the api is working or not or has and error

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSocket == INVALID_SOCKET) {
		cout << "socket creation failed!!" << endl;
		return 1;
	}


	// create address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	//convert the ipaddress(0.0.0.0) put it insise sin_family in binary format
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "setting address structure failed!!" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//bind
	int bindResult = ::bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (bindResult == SOCKET_ERROR) {
		cout << "bind failed!! Error Code: " << WSAGetLastError() << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}



	//Listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "LIsten failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;

	}

	cout << "server has started listning on port : " <<port<< endl;

	//accept
	SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET) {
		cout << "invalid client socket!!" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	char buffer[4096];
	int bytesrecvd =  recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytesrecvd == SOCKET_ERROR) {
		cout << "Error in receiving data!!" << endl;
		closesocket(clientSocket);
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	buffer[bytesrecvd] = '\0';  // Null-terminate the received data

	string message(buffer);
	cout << "message from client :" << message << endl;

	closesocket(clientSocket);
	closesocket(listenSocket);

	WSACleanup();
	return 0;
}
