#include "Client.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Client::~Client()
{
    if(sock_fd != -1) close(sock_fd);
}

void Client::manage()
{
    for(;;)
    {
        std::cout << "To server: " << std::flush;
        std::string line;
        if(!std::getline(std::cin, line)) line = "exit";

        write(sock_fd, line.data(), line.size());

        if(line == "exit")
        {
            std::cout << "Client exit...\n";
            return;
        }

        ssize_t received = read(sock_fd, buffer, sizeof(buffer) - 1);
        if(received <= 0)
        {
            std::cout << "Server disconnected\n";
            return;
        }
        buffer[received] = '\0';

        std::cout << "From server: " << buffer << "\n";

        if(std::string(buffer) == "exit")
        {
            std::cout << "Client exit...\n";
            return;
        }
    }
}

bool Client::drive(const char* address)
{
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1)
    {
        std::cout << "Socket creation failed\n";
        return false;
    }
    std::cout << "Socket created successfully\n";

    sockaddr_in servaddr{};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if(inet_pton(AF_INET, address, &servaddr.sin_addr) != 1)
    {
        std::cout << "Invalid address: " << address << "\n";
        return false;
    }

    if(connect(sock_fd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr)) != 0)
    {
        std::cout << "Connection to server failed\n";
        return false;
    }
    std::cout << "Connection successful\n";

    manage();
    return true;
}
