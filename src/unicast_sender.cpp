#include "unicast_sender.hpp"

Unicast::Unicast() {
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0) {
        perror("WSA failed");
    }
}

void Unicast::sendMessageTo(char * message, std::string IPAdress, int size) {
    int sockfd;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
    }

    struct sockaddr_in recipientAddr;
    const char* recipientIP = IPAdress.c_str();
    const int port = 1999;              // Port to send to

    // Set up recipient address
    memset(&recipientAddr, 0, sizeof(recipientAddr));
    recipientAddr.sin_family = AF_INET;
    recipientAddr.sin_port = htons(port);
    recipientAddr.sin_addr.s_addr = inet_addr(recipientIP);

    // Send the message
    int sentBytes = sendto(sockfd, message, size, 0,
                           (struct sockaddr*)&recipientAddr, sizeof(recipientAddr));
    if (sentBytes < 0) {
        perror("sendto failed");
    }

    close(sockfd);
    WSACleanup();
}
