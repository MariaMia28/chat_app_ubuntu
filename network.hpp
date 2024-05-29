#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string> 

//conection to the server
int connectToServer(const std::string& serverAddress);

//create a server socket and start listening
int createServerSocket();

//accept a new client connection
int acceptClientConnection(int serverFd);

//send a message through a socket
void sendMessage(int socketFd, const std::string& message);

//receive a message from a socket
std::string receiveMessage(int socketFd);

#endif //Network_HPP

