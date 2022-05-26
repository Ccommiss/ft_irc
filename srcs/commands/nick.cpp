#include "Server.hpp"
#include "Answers.hpp"

void Commands::nick(Server &s, User *u, std::vector<std::string> cmd)
{
	start;
	out (u->nickname);
	if (u->registered == 0)
		out (BOLD("Setting nickname to ") << *(cmd.begin() + 1));	
	if (u->registered == 1)
	{
		out (BOLD("Changing nick name from ") << u->nickname << " to " << *(cmd.begin() + 1));
		server_relay(u, cmd, s.server_users);
	}
	u->setNickName(*(cmd.begin() + 1));
}