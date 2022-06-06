
#include "Commands.hpp"
#include "Answers.hpp"


void Commands::kill(Server &s, User *u, std::vector<std::string> cmd)
{
	User *to_kill;

	if (cmd.size() < 2)
		return s.numeric_reply(u, ERR_NEEDMOREPARAMS, NONE, NONE, NONE);
 	if (!u->hasMode('O'))
	 	return s.numeric_reply(u, ERR_NOPRIVILEGES, NONE, NONE, NONE);
	if (!s.findByName(cmd[1], &to_kill))
		return s.numeric_reply(u, ERR_NOSUCHNICK, NONE, NONE, NONE);
	server_relay(u, cmd, s.server_users);
	s.delete_user(to_kill);
}
