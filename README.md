
# Chat Application - Server and Client

This repository contains a simple chat application implementation with two clients connecting to a single server. The communication is done over TCP using Winsock API (for Windows). Each client can send and receive messages from the server. The server handles multiple clients and broadcasts messages to all connected clients.

## Features
- **Server**: Handles multiple clients, listens for incoming connections, receives messages, and broadcasts them to all connected clients.
- **Clients**: Connect to the server, send messages, and receive broadcasted messages from the server.

## Prerequisites

Before you begin, ensure you have met the following requirements:
- A system running Windows OS.
- Visual Studio or any C++ compiler that supports Winsock API.
- Basic knowledge of C++ and networking.

## Installation

1. Clone the repository:

    ```bash
    git clone [https://github.com/username/repository-name.git](https://github.com/TathagataSau/Chat_App-cpp)
    ```

2. Open the project in your preferred IDE (e.g., Visual Studio).

3. Make sure to link the Winsock library in your project settings:

    - Go to Project Properties > Linker > Input > Additional Dependencies.
    - Add `ws2_32.lib`.

## Usage

### Server

1. Compile and run the server code.
2. The server will listen for incoming client connections on a specified port (default: 12345).
3. The server will broadcast any messages received from one client to all connected clients.

### Clients

1. Compile and run the client code.
2. When prompted, enter the server's IP address and port to connect.
3. You can now send messages that will be broadcasted to all connected clients.

## Example Output

### Server:
```bash
Server Program
server has started listening on port: 12345
client connected
message from client: *Client1*: Hello Server!
message from client: *Client2*: Hi there!
```

### Client 1:
```bash
Client program started
Connected to the server!
Enter your chat name: Client1
*Client1*: Hello Server!
```

### Client 2:
```bash
Client program started
Connected to the server!
Enter your chat name: Client2
*Client2*: Hi there!
```

## Contributing

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contact

Your Name - [tathagatasau321@gmail.com](mailto:tathagatasau321@gmail.com)
Project Link: [https://github.com/TathagataSau/Chat_App-cpp](https://github.com/TathagataSau/Chat_App-cpp)
