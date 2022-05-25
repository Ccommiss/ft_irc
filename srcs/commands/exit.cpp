#include "Server.hpp"
#include "Answers.hpp"

void Commands::quit_s(Server &s, User *u, std::vector<std::string> arg) // exit ou quit
{
	(void)arg;
    out("QUIT CMD" << *arg.begin())
	s.end_connection(u->socket_descriptor);
}
