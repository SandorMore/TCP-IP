#include "TCP/Server.hpp"

int main()
{
	Server server;
	return server.drive() ? 0 : 1;
}
