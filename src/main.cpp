#include <iostream>
#include "network/Server.hpp"

void dev(void);

int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;
	
	std::cout << "Wow c'est vraiment cool !" << std::endl;
	Server s = Server(1000, "coucou");
	return 0;


}
