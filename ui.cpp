#include "ui.hpp"

#include <iostream>
#include <string>

using namespace std;

string getServerAddressFromUser() {
    string serverAddress;
    cout << "Enter server IP address: ";
    getline(cin, serverAddress);
    return serverAddress;
}

string getMessageFromUser() {
    string message;
    cout << "Enter message: ";
    getline(cin, message);
    return message;
}

void displayMessage(const string& sender, const string& message) {
    cout << sender << ":" << message << endl;
}