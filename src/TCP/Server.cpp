#include "Server.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Server::~Server()
{
    if(conn_fd != -1) close(conn_fd);
    if(sock_fd != -1) close(sock_fd);
}

void Server::manage()
{
    for(;;)
    {
        ssize_t received = read(conn_fd, buffer, sizeof(buffer) - 1);
        if(received <= 0)
        {
            std::cout << "Client disconnected\n";
            return;
        }
        buffer[received] = '\0';

        std::cout << "From client: " << buffer << "\n";

        if(std::string(buffer) == "exit")
        {
            std::cout << "Server exits\n";
            return;
        }

        std::cout << "To client: " << std::flush;
        std::string line;
        if(!std::getline(std::cin, line)) line = "exit";

        write(conn_fd, line.data(), line.size());

        if(line == "exit")
        {
            std::cout << "Server exits\n";
            return;
        }
    }
}

bool Server::drive()
{
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1)
    {
        std::cout << "Error during socket initialization\n";
        return false;
    }
    std::cout << "Socket created successfully\n";

    // Allow restarting the server right away without "address already in use"
    int opt = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in servaddr{};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock_fd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr)) != 0)
    {
        std::cout << "Socket bind failed\n";
        return false;
    }
    std::cout << "Socket successfully bound\n";

    if(listen(sock_fd, 5) != 0)
    {
        std::cout << "Listen failed\n";
        return false;
    }
    std::cout << "Server listening on port " << port << "...\n";

    sockaddr_in cli{};
    socklen_t len = sizeof(cli);
    conn_fd = accept(sock_fd, reinterpret_cast<sockaddr*>(&cli), &len);
    if(conn_fd < 0)
    {
        std::cout << "Server accept failed\n";
        return false;
    }
    std::cout << "Server accepted the client\n";

    manage();
    return true;
}
