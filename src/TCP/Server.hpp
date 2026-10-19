#include <iostream>
#include <netdb.h>
#include <stddef.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>

constexpr int max = 80;
constexpr int port = 8080;

struct Server 
{
public:
    void manage(int);
    void drive(int&, int&, unsigned);
private:
    char buffer[max];
    int n{};
};