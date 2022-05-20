
#include "Server.hpp"

char *	Server::get_ip( void )
{
		return (inet_ntoa(((struct sockaddr_in *) &_client_saddr)->sin_addr));
}
