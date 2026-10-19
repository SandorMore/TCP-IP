#pragma once

#include "Common.hpp"

class Server final
{
public:
    ~Server();
    bool drive();
private:
    void manage();

    char buffer[buffer_size]{};
    int sock_fd{-1};
    int conn_fd{-1};
};
