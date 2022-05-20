#include "Server.hpp"
#include <iostream>

int main (int ac, char**av)
{
	if (ac != 3)
	{
		std::cerr << "Syntax needed : " << av[0] << " <port> <password>" << std::endl;
		return(-1);
	}

	Server *sv;
	try 
	{
		sv = new Server(av[1], av[2]);
		sv->run();
	}
	catch (std::exception &	e)
	{
		std::cerr << e.what() << std::endl;
	}

}
