#pragma once

#include "Common.hpp"

class Client final 
{
public:
    ~Client();
    bool drive(const char* address = "127.0.0.1");
private:
    void manage();

    char buffer[buffer_size]{};
    int sock_fd{-1};
};
