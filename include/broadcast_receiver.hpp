#ifndef BROADCAST_RECEIVER_H
#define BROADCAST_RECEIVER_H

#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <unistd.h>
#include <string>
#include <ws2tcpip.h>
#include <thread>
#include "monitoring_station.hpp"

class Receiver {
public:
    explicit Receiver(MonitoringStation& m);
    ~Receiver();
    void start();

private:
    int sockfd;
    const char *port;
    std::string message;
    MonitoringStation *monitor;
    Receiver();
    std::thread socketThread;

};

#endif // BROADCAST_RECEIVER_H
