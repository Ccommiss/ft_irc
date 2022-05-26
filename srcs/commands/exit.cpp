#include "Server.hpp"
#include "Answers.hpp"

void Commands::quit_s(Server &s, User *u, std::vector<std::string> cmd) // exit ou quit
{
	(void)cmd;
    out("QUIT CMD" << *cmd.begin())
	s.end_connection(u->socket_descriptor);
}
