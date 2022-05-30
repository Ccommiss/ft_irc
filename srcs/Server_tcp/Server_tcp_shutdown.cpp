
#include "Server.hpp"

void	Server::shutdown(bool does_it_throw)
{
	start;
	if (this->_addrs)
	{
		freeaddrinfo (_addrs);
		_addrs = NULL;
	}
	while(users.begin() != users.end())
		delete_user(users.begin()->second);
	close_fd(_listener, does_it_throw);
	users.clear();
	server_users.clear();
	chans.clear();

	//clear??
}
