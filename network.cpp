#include "network.hpp"

#include <iostream>
#include <cstring> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define PORT 12345

using namespace std;

int connectToServer(const std::string& serverAddress) {
    int sock = 0; 
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if(inet_pton(AF_INET, serverAddress.c_str(), &serv_addr.sin_addr) <= 0)  {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    std::cout << "Connected to server at " << serverAddress << std::endl;
    return sock;
}

int createServerSocket(){
    int serverFd;
    struct sockaddr _in serverAddr;

    //creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //setting up the server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; //listen on all available interfaces
    serverAddr.sin_port = htons(PORT);

    //binding the socket to the specified address and port
    if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //listen for incoming connections
    if (listen(serverFd, 3) < 0) //allow up to 3 pending connections
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server listening on port " << PORT << endl;
    return serverFd;

}

int acceptClientConnection(int serverFd) {
    int newSocket;
    struct sockaddr _in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    //accepting a new incoming connection
    if ((newSocket = accept(serverFd, (struct sockaddr *)&clientAddr, &addrLen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //getting the client's IP
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), ipstr, INET_ADDRSTRLEN);
    cout << "New connection from " << ipstr << endl;

    return newSocket;
    
}

