#include "Server.hpp"

void Commands::setUser(Server &s, User *u, std::vector<std::string> arg)
{
	(void)s;
	out("Setting name to : " << *(arg.begin() + 1));
	u->setName(*(arg.begin() + 1));
	if (u->registered == 0)
	{
		numeric_reply(s, u, "001", NULL);
		numeric_reply(s, u, "002", NULL);
		numeric_reply(s, u, "003", NULL);
		numeric_reply(s, u, "004", NULL);
		u->registered = 1;
		out("Answer sent to " << u->socket_descriptor);
	}
}