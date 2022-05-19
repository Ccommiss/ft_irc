
#include "Server_tcp.hpp"

void Server_tcp::existing_connection( struct epoll_event &ev )
{

	memset (&recv_message, '\0', sizeof (recv_message));
	ssize_t numbytes = recv (ev.data.fd, &recv_message, sizeof (recv_message), 0);

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
		debug(sizeof(recv_message), NOCR);
		debug(" - BYTES = ",NOCR);
		debug(numbytes,NOCR);
		debug(" - LEN = ",NOCR);
		debug(strlen(recv_message), NOCR);
		debug(" - MESSAGE = ", NOCR);
		debug(recv_message);
	}
}
