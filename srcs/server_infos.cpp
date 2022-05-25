#include "Server.hpp"

/*
**      File dedicated to funciton that display/debug things it contains (if chan exists or users for example) 
*/


bool Server::chanExists(std::string chan_name) // a mettre ailleurs 
{
	if (chans.count(chan_name) == 1)
		return (true);
	return (false);
} 