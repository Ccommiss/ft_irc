
#include "Commands.hpp"
#include "Answers.hpp"

void Commands::pass(Server &s, User *u, std::vector<std::string> cmd)
{
	(void)s;
	(void)u;
	(void)cmd;

	out("NEET TO CHECK NUERIC REPLY");
	if (s.pass_check(cmd[1]))
		u->registered[User::PASS] = true;
}
