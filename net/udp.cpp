#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "udp.h"
void broadcastSend(const std::string& data, const int& port) {
    int senderSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (senderSocket < 0) {
        std::cerr << "Failed to create socket\n";
        return;
    }

    int broadcastPermission = 1;
    setsockopt(senderSocket, SOL_SOCKET, SO_BROADCAST, &broadcastPermission, sizeof(broadcastPermission));

    sockaddr_in broadcastAddr;
    std::memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    // TODO:测试修改端口
    broadcastAddr.sin_port = htons(port);

    sendto(senderSocket, data.c_str(), data.length(), 0, (sockaddr*)&broadcastAddr, sizeof(broadcastAddr));

    close(senderSocket);
}

void broadcastReceive(const int& port) {
    int receiverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (receiverSocket < 0) {
        std::cerr << "Failed to create socket\n";
        return;
    }

    sockaddr_in receiverAddr;
    std::memset(&receiverAddr, 0, sizeof(receiverAddr));
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(port);
    if (bind(receiverSocket, (sockaddr*)&receiverAddr, sizeof(receiverAddr)) < 0) {
        std::cerr << "Failed to bind socket\n";
        close(receiverSocket);
        return;
    }

    char buffer[1024];
    sockaddr_in senderAddr;
    socklen_t senderLen = sizeof(senderAddr);

    while (true) {
        int recvLen = recvfrom(receiverSocket, buffer, 1024, 0, (sockaddr*)&senderAddr, &senderLen);
        if (recvLen > 0) {
            buffer[recvLen] = '\0';
            std::cout << "Received: " << buffer << std::endl;
        }
    }

    close(receiverSocket);
}