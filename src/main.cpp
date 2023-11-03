#include <iostream>
#include "network/Server.hpp"

void dev(void);

int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;
	
	Server s = Server(4000, "coucou");
	return 0;
}
