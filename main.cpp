#include <iostream>
#include <string>
#include <vector>
#include <thread> 


using namespace std;

// structure that holds client information
struct Client {
    string name;
    int socketFd;

};