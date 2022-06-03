
#include "Commands.hpp"
#include "Answers.hpp"

void Commands::ping(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() <= 1)
		return (s.numeric_reply(u, ERR_NOORIGIN, NONE, NONE, NONE));
	else if (cmd.size() <= 2)
	{
		if (cmd[1] != s.hostname)
			return (s.numeric_reply(u, ERR_NOSUCHSERVER, cmd[1], NONE, NONE));
		std::string to_send = "PONG " + cmd[1] + "\r\n";
		 out ( "--> send pong(" + to_send + ")");
		send(u->socket_descriptor, to_send.c_str(), to_send.size(), 0);
	}
}
