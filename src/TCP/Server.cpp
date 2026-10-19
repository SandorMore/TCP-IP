#include "Server.hpp"
#include <string_view>

void Server::manage(int conn_fd)
{
    for(;;)
    {
        bzero(buffer, max);

        read(conn_fd, buffer, sizeof(buffer));
        
        std::cout << buffer << "\n";
        
        bzero(buffer, max);
        n = 0;

        while((buffer[n++] = getchar()) != '\n');

        write(conn_fd, buffer, sizeof(buffer));

        if(std::string_view(buffer) == "exit")
        {
            std::cout << "Server exits" << "\n";
            break;
        }
    }
}

void Server::drive(int& sock_fd, int& conn_fd, unsigned len)
{
    struct sockaddr_in servaddr, cli;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_fd == -1)
    {
        std::cout << "Error during socket initialization\n";
        return;
    }
    else 
    {
        std::cout << "Socket created sucessfully\n";
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if((bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0)
    {
        std::cout << "Socket bind failed\n";
        return;
    }
    else
    {
        std::cout << "Socket sucessfully created\n";
    }

    if(listen(sock_fd, 5) != 0)
    {
        std::cout << "Listen failed\n";
    }
    else 
    {
        std::cout << "Server listening...\n";
    }

    conn_fd = accept(sock_fd, (struct sockaddr*)&cli, &len);
    if(conn_fd <  0)
    {
        std::cout << "Server accept failed\n";
    }
    else 
    {
        std::cout << "server accepting the client\n";
    }
    manage(conn_fd);
    close(sock_fd);
}
