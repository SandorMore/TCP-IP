#include "TCP/Client.hpp"

int main(int argc, char** argv)
{
	Client client;
	bool ok = argc > 1 ? client.drive(argv[1]) : client.drive();
	return ok ? 0 : 1;
}
