#include "Server.hpp"
#include <algorithm> 
#include <string>

/*
**      File dedicated to funciton that display/debug things it contains (if chan exists or users for example)
*/

bool Server::chanExists(std::string chan_name)
{
	if (chans.count(chan_name) == 1)
		return (true);
	return (false);
}

bool Server::findByName(std::string nick, User **u)
{
	std::map<const std::string *, User *>::iterator it;
	for (it = server_users.begin(); it != server_users.end(); it++)
	{
		if (*(it->first) == nick)
		{
			*u = (it->second);
			return true;
		}
	}
	return false;
}

bool Server::nicknameExists(std::string nick)
{
	std::map<const std::string *, User *>::iterator it;
	for (it = server_users.begin(); it != server_users.end(); it++)
	{
		if (toLower(*(it)->first) == toLower(nick))
			return true; 
	}
	return false;
}
