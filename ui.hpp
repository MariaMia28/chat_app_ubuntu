#ifndef UI_HPP
#define UI_HPP

#include <string> 

//get the server IP address from the user
std::string getServerAddressFromUser();

//get a chat message from the user
std::string getMessageFromUser();

//display a message to the user
void displayMessage(const std::string& sender, const std::string& message);

#endif //UI_HPP
