#include <iostream>
#include <netdb.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stddef.h>
#include <arpa/inet.h>

constexpr int max = 80;
constexpr int port = 8080;

class Client final 
{
public:
    void manage(int);
    void drive(int& , int&);
private:
    char buffer[max];
    int n;
};