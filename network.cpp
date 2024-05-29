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

