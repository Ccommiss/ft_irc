
#include "Server.hpp"

char *	Server::get_ip( void ) const
{
	return (inet_ntoa(((struct sockaddr_in *) &_client_saddr)->sin_addr));
}

User*	Server::create_user( void )
{
	/* Create socket */
	socklen_t addrlen = sizeof (struct sockaddr_storage);
	int new_sd;
	if (0 > (new_sd = accept (_listener, (struct sockaddr *) &_client_saddr, &addrlen)))
		throw std::runtime_error("accept error");

	/* Add to monitoring */ 
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = new_sd;
	if (0 > epoll_ctl (_efd, EPOLL_CTL_ADD, new_sd, &ev))
		throw std::runtime_error("epoll_ctl socket add failed");

	/* create obj */
	User *new_user = new User(new_sd, get_ip());
	users.insert(std::pair<int, User*>(new_sd, new_user));
	server_users.insert(std::pair<std::string *, User *>(&new_user->getNickName(), new_user));
	return(new_user);
}

void	Server::delete_user( User *to_del )
{
	start;
	std::vector<std::string> arg;
	arg.push_back("PART");
	arg.push_back("chan");
	arg.push_back(":disconnected from server");
	std::vector <Channel *>::const_iterator it = to_del->getJoinedChannels().begin(); 
	while (to_del->getJoinedChannels().size() > 0)
	{
		it = to_del->getJoinedChannels().begin();
		arg[1] = (*it)->_name;
	 	cmds.part(*this, to_del, arg);
	}
	/* remove from server_users */
	server_users.erase(&to_del->getNickName());	
	/* remove from users */
	users.erase(to_del->socket_descriptor);
	/* unset from monitoring */
	if (epoll_ctl (_efd, EPOLL_CTL_DEL, to_del->socket_descriptor, NULL) == -1)		 
		throw std::runtime_error("epoll_ctl socket del failed");
	/* close socket */ 
	close_fd(to_del->socket_descriptor, THROW);
	delete to_del;
	
}

bool	Server::oper_pass_check( std::string to_check) const
{
	if (!to_check.compare(_oper_pass))
		return (true);
	else
		return (false);
}

bool	Server::pass_check( std::string to_check) const
{
	if (!to_check.compare(_pass))
		return (true);
	else
		return (false);
}
