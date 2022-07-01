#include "Server.h"

Server::Server(const std::string& ip_address, uint16_t port)
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    inet_aton(ip_address.c_str(), &server_address.sin_addr);
    server_address.sin_port = htons(port);
}

void Server::bindAndListen()
{
    bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(socket_fd, 0);
}

void Server::acceptClientThread()
{
    while (true)
    {
        struct sockaddr_in client_address;
        socklen_t address_size;
        int client_socket = accept(socket_fd, (struct sockaddr*)&client_address, &address_size);
        client_connections.push_back(std::thread(processData, client_socket));
    }
}

void Server::processData(int client_socket)
{
    char buffer[1024];
    recv(client_socket, buffer, 1024, 0);
    std::cout << buffer << "\n";
}

int main()
{
    Server b("127.0.0.1", 40000);
    b.bindAndListen();
    b.acceptClientThread();
}