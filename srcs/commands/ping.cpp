
#include "Commands.hpp"
#include "Answers.hpp"

void Commands::ping(Server &s, User *u, std::vector<std::string> cmd)
{
	(void)s;
	out("PING Need to implement numeric reply in case of an error");
	cmd[0] = "PONG";
	std::string to_send = "PONG " + cmd[1] + "\r\n";
	send(u->socket_descriptor, to_send.c_str(), to_send.size(), 0);
}
