
#include "Server.hpp"
void	Server::run( void )
{
	start;
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
					create_user();
				else
					this->existing_connection(_ep_event[i].data.fd);
			}
		}
		if (!_nb_ev)
		{
			debug(SV, "Timeout - exit now");
			break;
			//delete_user(users[5]);
		}

	}
	out ("===> Leaving whil 1 loop")
}
