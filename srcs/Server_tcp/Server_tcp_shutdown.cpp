
#include "Server.hpp"

		void	Server::shutdown(bool does_it_throw)
{
		if (this->_addrs)
		{
			freeaddrinfo (_addrs);
			_addrs = NULL;
		}
		close_fd(_listener, does_it_throw);
		for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
			delete_user(it->second);
		//clear??
}
