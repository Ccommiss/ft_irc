
#include "Server_tcp.hpp"
void	Server_tcp::run( void )
{
	while (1)
	{
		// monitor readfds for readiness for reading. if TIMEOUT = -1 == infinity
		// fill ep_event ???
		// return nb of evenements
		if (0 > (_nb_ev = epoll_wait (_efd, _ep_event, MAX_EVENTS,  TIMEOUT)))
			throw std::runtime_error("epoll_wait failed");
		for (int i = 0; i < _nb_ev; i++)
		{
			if 	((_ep_event[i].events & EPOLLIN) == EPOLLIN) // mask EPOLLIN event
			{
				if (_ep_event [i].data.fd == _listener)
					this->new_connection();
				else
					this->existing_connection(_ep_event[i]);
			}
		}

	}
}
