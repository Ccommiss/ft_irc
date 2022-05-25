
#include "Server.hpp"
void Server::end_connection( int sd )
{
	debug(SV,"socket ", NOCR);
	debug(SV, sd, NOCR);
	debug(SV," closed by client");

	// delete fd from epoll
	// event = NULL because we dont need it since kernel 2.6.9
	if (epoll_ctl (_efd, EPOLL_CTL_DEL, sd, NULL) == -1)
		throw std::runtime_error("epoll_ctl socket del failed");
	delete_user(users[sd]);

	//out(u->nickname << " has left the chat");
	//close_fd(u->socket_descriptor, THROW);
}
