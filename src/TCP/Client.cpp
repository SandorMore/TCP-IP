#include "Client.hpp"
#include <string_view>

void Client::manage(int sock_fd)
{
    for(;;)
    {
        bzero(buffer, sizeof(buffer));
        
        read(sock_fd, buffer, sizeof(buffer));
        
        std::cout << buffer << "\n";

        bzero(buffer, sizeof(buffer));

        n = 0;
        while((buffer[n++] = getchar()) != '\n');

        write(sock_fd, buffer, sizeof(buffer));
        
        bzero(buffer, sizeof(buffer));

        read(sock_fd, buffer, sizeof(buffer));
        std::cout << "From server: " << buffer << "\n";

        if(std::string_view(buffer) == "exit")
        {
            std::cout << "Client exit..." << "\n";
            return;
        }
    }
}

void Client::drive(int& sock_fd, int& conn_fd)
{
    struct sockaddr_in servaddr, cli;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_fd == -1)
    {
        std::cout << "Socket creation failed" << "\n";
        return;
    }
    else 
    {
        std::cout << "Socket created sucessfully" << "\n";
    }

    bzero(&servaddr, sizeof(sockaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);

    if(connect(sock_fd, (sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
        std::cout << "Server creation failed" << "\n";
        return;
    }
    else
    {
        std::cout << "Connection sucessful" << "\n";
    }

    manage(sock_fd);
    close(sock_fd);
}
