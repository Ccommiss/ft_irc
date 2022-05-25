#include "Server.hpp"
#include "Answers.hpp"

void Commands::nick(Server &s, User *u, std::vector<std::string> arg)
{
	start;
	out (u->nickname);
	if (u->registered == 0)
		out (BOLD("Setting nickname to ") << *(arg.begin() + 1));	
	if (u->registered == 1)
	{
		out (BOLD("Changing nick name from ") << u->nickname << " to " << *(arg.begin() + 1));
		server_relay(u, arg, s.server_users);
	}
	u->setNickName(*(arg.begin() + 1));
}