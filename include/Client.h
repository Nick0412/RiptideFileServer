#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <cstring>
#include <iostream>

class Client
{
private:
    static constexpr size_t buffer_size = 1<<3;
    int socket_fd;
    struct sockaddr_in server_address;
    std::array<uint8_t, buffer_size> send_buffer;
    std::array<uint8_t, buffer_size> receive_buffer;

public: 
    Client() = delete;
    Client(const std::string& server_ip, uint16_t server_port);
    void connectToServer();
    void sendData(const std::vector<uint8_t>& data);

private:
    void sendDataWithRange(const std::vector<uint8_t>& data, size_t start, size_t end);
};

#endif