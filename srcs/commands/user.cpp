#include "Server.hpp"
#include "Answers.hpp"

void Commands::setUser(Server &s, User *u, std::vector<std::string> cmd)
{
	(void)s;
	out("Setting name to : " << *(cmd.begin() + 1));
	u->setName(*(cmd.begin() + 1));
	if (u->registered == 0)
	{
		s.numeric_reply(u, "001", u);
		s.numeric_reply(u, "002", u);
		s.numeric_reply(u, "003", u);
		s.numeric_reply(u, "004", u);
		u->registered = 1;
		out("Answer sent to " << u->socket_descriptor);
	}
}