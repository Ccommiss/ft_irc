#include "Server.hpp"
#include <iostream>

int main (int ac, char**av)
{
	if (ac != 3)
	{
		std::cerr << "Syntax needed : " << av[0] << " <port> <password>" << std::endl;
		return(-1);
	}

	Server *sv = NULL;
	try { sv = new Server(av[1], av[2]); }
	catch (std::exception &	e)
	{
		std::cerr <<"[MAIN] - Exception catched during sv INIT: " << e.what() << std::endl;
		exit(-1);
	}

	try { sv->run(); }
	catch (std::exception &	e)
	{
		std::cerr <<"[MAIN] - Exception catched during sv RUN: " << e.what() << std::endl;
		sv->shutdown(NO_THROW);
		delete sv;
		exit(-1);
	}


	sv->shutdown(THROW);
	delete sv;
	exit(0);

}
