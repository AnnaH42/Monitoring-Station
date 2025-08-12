#ifndef UNICAST_SENDER_HPP
#define UNICAST_SENDER_HPP

#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <unistd.h>
#include <sstream>

class Unicast {
public:
    Unicast();
    ~Unicast() = default;
    void sendMessageTo(char *message, std::string IPAdress, int size);

private:
    int sockfd;
    const char *port;

};

#endif // UNICAST_SENDER_HPP
