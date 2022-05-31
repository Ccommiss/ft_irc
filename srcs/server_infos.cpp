#include "Server.hpp"
#include <algorithm> 
#include <string>

/*
**      File dedicated to funciton that display/debug things it contains (if chan exists or users for example)
*/

bool Server::chanExists(std::string chan_name) // a mettre ailleurs
{
	if (chans.count(chan_name) == 1)
		return (true);
	return (false);
}

void Server::printChans()
{
	out ("Printing chans in Server :")
	for (std::map<std::string, Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
		out ("Chan : "<< it->first)
}


bool Server::findByName(std::string nick, User **u)
{
	start;
	std::map<const std::string *, User *>::iterator it;
	for (it = server_users.begin(); it != server_users.end(); it++)
	{
		if (*(it->first) == nick)
		{
			*u = (it->second); // on fait pointer User recu sur l'instance
			return true;
		}
	}
	return false;
}

bool Server::nicknameExists(std::string nick)
{
	start;
	std::map<const std::string *, User *>::iterator it;
	for (it = server_users.begin(); it != server_users.end(); it++)
	{
		if (toLower(*(it)->first) == toLower(nick))
			return true; 
	}
	return false;
}



//void Server::printUsers();