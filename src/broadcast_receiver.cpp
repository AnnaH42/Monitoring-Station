#include "broadcast_receiver.hpp"


    Receiver::Receiver(MonitoringStation &m) {
        monitor = &m;
        WSADATA wsaData;
        int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (err != 0) {
            perror("error with WSA");
        }


    }

    Receiver::~Receiver(){
        close(sockfd);
        if (socketThread.joinable()) {
            socketThread.join();
        }
        WSACleanup();
    }


    void Receiver::start() {
        socketThread = std::thread([this]() {

        int sockfd;
        struct sockaddr_in recvAddr;
        char buffer[2304];
        const int port = 1999;

        // Create socket
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            perror("socket creation failed");
        }

        // Set up receive address
        memset(&recvAddr, 0, sizeof(recvAddr));
        recvAddr.sin_family = AF_INET;
        recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        recvAddr.sin_port = htons(port);

        // Bind socket to port
        if (bind(sockfd, (struct sockaddr*)&recvAddr, sizeof(recvAddr)) < 0) {
            perror("bind failed");
            close(sockfd);
        }

        int count = 0;
        // Receive message
        while (true) {
            socklen_t addrLen = sizeof(recvAddr);
            int recvLen = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                                   (struct sockaddr*)&recvAddr, &addrLen);
            if (recvLen < 0) {
                perror("recvfrom failed");
                break;
            }

            buffer[recvLen] = '\0'; // Null-terminate the string
            char* address = inet_ntoa(recvAddr.sin_addr);
            count++;
            monitor->receivedMessage(buffer, address);
            //std::cout << "Message recv: " << count << std::endl;
        }
        });
    }

