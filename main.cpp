#include <iostream>
#include <string>
#include <vector>
#include <thread> 

#include "network.hpp"
#include "ui.hpp"

using namespace std;

// structure that holds client information
struct Client {
    string name;
    int socketFd;

};

void receiveMessages(int clientSocket) {
    while (true) {
        string receivedMessage = receiveMessage(clientSocket);
        displayMessage("Server", receivedMessage);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2)
    {
        string serverAddress = getServerAddressFromUser(); //ui.cpp
        int clientSocket = connectToServer(serverAddress); //implement it in network.cpp

        thread receiveThread(receiveMessages, clientSocket);

        while(true) {       
            string message = getMessageFromUser(); //ui.cpp
            sendMessage(clientSocket, message); //implement in network.cpp
        }
    } else if(strcmp(argv[1], "--server") == 0) {
        //server mode
        int serverSocket = createServerSocket(); //network.cpp

        while (true)
        {
            string message = getMessageFromUser(); //ui.cpp
            sendMessage(clientSocket, message); // implement in nework.cpp

            int clientSocket = acceptClientConnection(serverSocket); //network.cpp
            string clientName = getClientConnection(serverSocket);

            //storing client information
            clients.push_back({clientName, clientSocket});

            thread clientThread(handleClient, clientSocket);
            clientThread.detach(); //let the thread run independently

        }
        
    } else {
        cout << "Invalid argument. Use --server to run as a server." << endl;
        return 1;
    }
    
    return 0;
}