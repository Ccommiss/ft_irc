#include "Server_tcp.hpp"
#include <iostream>

int main (int ac, char**av)
{
	if (ac != 3)
	{
		std::cerr << "Syntax needed : " << av[0] << " <port> <password>" << std::endl;
		return(-1);
	}
	Server_tcp *sv;

	try 
	{
		sv = new Server_tcp(av[1], av[2]);
	}
	catch (std::exception &	e)
	{
		std::cerr << e.what() << std::endl;
	}

}
