
#include "Server.hpp"

bool	Server::pass_check( std::string to_check)
{
	if (!to_check.compare(_pass))
		return (true);
	else
		return (false);
}
