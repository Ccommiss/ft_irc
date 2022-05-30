#include "Server.hpp"
#include "Answers.hpp"

void Commands::quit_s(Server &s, User *u, std::vector<std::string> cmd) // exit ou quit
{
    out("QUIT CMD" << *cmd.begin())
	s.delete_user(u);
}
