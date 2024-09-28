#include <bits/stdc++.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

/*
1. Initialize Winsock
2. Create a socket
3. Connect to the server
4. Send data to the server
5. Receive data from the server
6. Close the socket and clean up
*/

// Initialize Winsock
bool Initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void SendMsg(SOCKET clientSocket) {
    cout << "Enter your chat name: " << endl;
    string name;
    getline(cin, name);
    string message;

    while (1) {
        //cout << ">> ";
        getline(cin, message);
        string msg = "*" + name + "* : " + message;
        int bytesent = send(clientSocket, msg.c_str(), msg.length(), 0);

        if (bytesent == SOCKET_ERROR) {
            cout << "cannot send, error in sending message!!" << endl;
            break;
        }

        if (message == "/quit" || message == "/end") {
            cout << "stopping the application" << endl;
            break;
        }

    }
    closesocket(clientSocket);
    WSACleanup();

}

void ReceiveMsg(SOCKET clientSocket) {
    char buffer[4096]; 

    while (1) {
        // Receive data from the server/client
        int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        // Error handling
        if (bytesrecvd == SOCKET_ERROR) {
            cout << "Error receiving message!!" << endl;
            break;
        }

        // If the server/client gracefully disconnects
        if (bytesrecvd <= 0) {
            cout << "Server disconnected!" << endl;
            break;
        }

        // Null-terminate the received data and print it
        buffer[bytesrecvd] = '\0';
        cout << ">> " << buffer << endl;

        // Optionally, you can add a condition to exit on a specific message like "@quit"
        string message(buffer);
        if (message == "/quit" || message == "/end") {
            cout << "The other side has stopped the communication!" << endl;
            break;
        }
    }

    // Close the socket after done with receiving messages
    closesocket(clientSocket);
    WSACleanup();
}


int main() {
    if (!Initialize()) {
        cout << "Winsock Initialization failed!" << endl;
        return 1;
    }

    
    int port = 12345;

    cout << "Client program started" << endl;

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    // Specify the server address and port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);  // Same port as server

    // Convert the server's IP address (assuming localhost for now)
    if (InetPton(AF_INET, _T("127.0.0.1"), &serverAddr.sin_addr) != 1) {
        cout << "Invalid IP address!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Connect to the server
    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Connection to server failed!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to the server successfully!" << endl;

    thread senderthread(SendMsg, clientSocket);
    thread receiverthread(ReceiveMsg, clientSocket);

    /*
    // Send data to the server
    string message = "Hello from client!...... I'm DEVIL ";
    int sendResult = send(clientSocket, message.c_str(), message.size() + 1, 0);
    if (sendResult == SOCKET_ERROR) {
        cout << "Send failed!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Receive data from the server
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        cout << "Received from server: " << string(buffer, 0, bytesReceived) << endl;
    }
    */

    senderthread.join();
    receiverthread.join();

    return 0;
}
