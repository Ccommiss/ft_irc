
#include "Server.hpp"

void Server::existing_connection( struct epoll_event &ev )
{

	memset (&buffer, '\0', sizeof (buffer));
	ssize_t numbytes = recv (ev.data.fd, &buffer, sizeof (buffer), 0);

	if (numbytes == -1) //failed
		throw std::runtime_error("Recv Failed");
	else if (numbytes == 0) // connection closed by client
	{
		debug("socket ", NOCR);
		debug(ev.data.fd, NOCR);
		debug(" closed by client");

		// delete fd from epoll
		// event = NULL because we dont need it since kernel 2.6.9
		if (epoll_ctl (_efd, EPOLL_CTL_DEL, ev.data.fd, NULL) == -1)
			throw std::runtime_error("epoll_ctl socket del failed");
		close_fd((ev.data.fd), THROW);
	}
	else //do_action
	{
		debug("receved data to process : ",NOCR);
		debug("BUFF_MAX_SIZE = ", NOCR);
		debug(sizeof(buffer), NOCR);
		debug(" - BYTES = ",NOCR);
		debug(numbytes,NOCR);
		debug(" - LEN = ",NOCR);
		debug(strlen(buffer), NOCR);
		debug(" - MESSAGE = ", NOCR);
		debug(buffer);
		std::cout << users[ev.data.fd]->nickname << " says : " << buffer;
		cmds.parse_cmd(users[ev.data.fd], *this);
	}
}
