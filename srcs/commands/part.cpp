
#include "Server.hpp"
/*
**  Command: PART
**    Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
** 
**    The PART command causes the user sending the message to be removed
**    from the list of active members for all given channels listed in the
**    parameter string.  If a "Part Message" is given, this will be sent
**    instead of the default message, the nickname.  This request is always
**    granted by the server.
** 
**    Servers MUST be able to parse arguments in the form of a list of
**    target, but SHOULD NOT use lists when sending PART messages to
**    clients.
*/


//un seul channel 

void Commands::part(Server &s, User *u, std::vector<std::string> arg)
{
	start;
	std::string                                         chan_name = *(arg.begin() + 1);
	std::map<std::string, Channel *>::const_iterator	it = s.chans.find(chan_name); // ptr sur le chan 

	
	if ( it != s.chans.end())
	{
		std::map<std::string *, User *> chan_users = it->second->getUsers(); // on recup les users du chan
		std::cout << "removing user " << u->getName() << std::endl;

		s.chans[chan_name]->remove_user(u); 
		server_relay(u, arg, chan_users);             
	}
}