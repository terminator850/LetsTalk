#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include "net/udp.h"
#include "connection/connection.h"

int main() {
    string nickname;
    string pwd;
    int port;
    std::cout << "Enter the nickname: ";
    std::cin >> nickname;
    std::cin.ignore(); // Ignore the newline character left in the input buffer
    std::cout << "Enter the pwd: ";
    std::cin >> pwd;
    std::cin.ignore(); // Ignore the newline character left in the input buffer
    std::cout << "Enter the port number: ";
    std::cin >> port;
    std::cin.ignore(); // Ignore the newline character left in the input buffer

    std::string data;
    std::thread sendThread([&data, port]() {
        while (true) {
            std::getline(std::cin, data);
            if (!data.empty()) {
                broadcastSend(data, port);
            }
        }
    });

    std::thread receiveThread([port]() {
        broadcastReceive(port);
    });

    sendThread.join();
    receiveThread.join();

    return 0;
}