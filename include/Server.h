#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <thread>
#include <vector>
#include <iostream>

class Server
{
private:
    int socket_fd;
    struct sockaddr_in server_address;
    std::vector<std::thread> client_connections;

public:
    Server(const std::string& ip_address, uint16_t port);
    void bindAndListen();
    void acceptClientThread();

private:
    static void processData(int client_socket);
};

#endif