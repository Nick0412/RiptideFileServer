#include "Client.h"

Client::Client(const std::string& server_ip, uint16_t server_port)
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET;
    inet_aton(server_ip.c_str(), &server_address.sin_addr);
    server_address.sin_port = htons(server_port);
}

void Client::connectToServer()
{
    connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address));
}

void Client::sendData(const std::vector<uint8_t>& data)
{
    for (size_t offset = 0; offset < data.size();)
    {
        size_t bytes_left = data.size() - offset;
        size_t increment = std::min(buffer_size, bytes_left);
        sendDataWithRange(data, offset, offset + increment - 1);
        offset += increment;
    }
}

void Client::sendDataWithRange(const std::vector<uint8_t>& data, size_t start, size_t end)
{
    size_t number_of_bytes = (end - start) + 1;
    std::memcpy(send_buffer.data(), data.data() + start, number_of_bytes);

    size_t offset = 0;
    while (number_of_bytes > 0)
    {
        size_t bytes_sent = send(socket_fd, send_buffer.data() + offset, number_of_bytes, 0);
        offset += bytes_sent;
        number_of_bytes -= bytes_sent;
    }
}

// TODO: remove main
int main()
{
    Client client1("127.0.0.1", 40000);
    client1.connectToServer();
    std::string test_string;
    while (true)
    {
        std::getline(std::cin, test_string);

        std::vector<uint8_t> my_data(test_string.begin(), test_string.end());
        client1.sendData(my_data);
    }
    
}