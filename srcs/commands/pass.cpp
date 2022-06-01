
#include "Commands.hpp"
#include "Answers.hpp"

void Commands::pass(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() <= 1)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, NONE, NONE, NONE));
	if (s.pass_check(cmd[1]))
	{
		if (!u->registered[User::PASS])
			u->registered[User::PASS] = true;
		else
			return (s.numeric_reply(u, ERR_ALREADYREGISTERED, NONE, NONE, NONE));
	}

}
