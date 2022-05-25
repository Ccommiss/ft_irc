
#include "Server.hpp"

char *	Server::get_ip( void )
{
		return (inet_ntoa(((struct sockaddr_in *) &_client_saddr)->sin_addr));
}

User*	Server::create_user( int sd)
{
	User *new_user = new User(sd);
	users.insert(std::pair<int, User*>(sd,new_user));
	server_users.insert(std::pair<std::string *, User *>(&new_user->nickname, new_user));
	out ("Adding " << server_users.begin()->first << " with nick " << server_users.begin()->second->nickname <<" to database");
	return(new_user);
}

void	Server::delete_user( User *to_del )
{
		//std::map<int, User *>     					users;
		//std::map<const std::string *, const User *>	server_users; // sd et ref
	debug(SV,to_del->nickname, NOCR);
	if (server_users.erase(&to_del->nickname))
		debug(SV,"has been removed from server_users");
	else
		debug(SV,"has NOT been removed from server_users");
	if (users.erase(to_del->socket_descriptor))
		debug(SV,"has been removed from users");
	else
		debug(SV,"has NOT been removed from users");
	close_fd(to_del->socket_descriptor, THROW);
	delete to_del;
	//out ("Adding " << server_users.begin()->first << " with nick " << server_users.begin()->second->nickname <<" to database");
}

bool	Server::pass_check( std::string to_check)
{
	if (!to_check.compare(_pass))
		return (true);
	else
		return (false);
}
