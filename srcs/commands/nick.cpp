#include "Server.hpp"
#include "Answers.hpp"
#include <ctime>
/*
 **    Command: NICK
 **    Parameters: <nickname>
 **
 **    NICK command is used to give user a nickname or change the existing
 **    one.
 **
 **    Numeric Replies:
 **
 **            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
 **            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
 **            ERR_UNAVAILRESOURCE             ERR_RESTRICTED
 **
 **    Examples:
 **
 **    NICK Wiz                ; Introducing new nick "Wiz" if session is
 **                            still unregistered, or user changing his
 **                            nickname to "Wiz"
 **
 **    :WiZ!jto@tolsun.oulu.fi NICK Kilroy
 **                            ; Server telling that WiZ changed his
 **                            nickname to Kilroy.
 */




/*
 ** TODO : IGNORER LA CASSE car cleminem Cleminem fout la merde  
 */
void Commands::nick(Server &s, User *u, std::vector<std::string> cmd)
{
	start;
	std::string nickname;
	time_t now = time(0);
	localtime(&now);
	if (cmd.size() == 1)
		return (s.numeric_reply(u, ERR_NONICKNAMEGIVEN, NONE, NONE, NONE));
	nickname = *(cmd.begin() + 1);


	if (u->hasMode('r'))
		return (s.numeric_reply(u, ERR_RESTRICTED, nickname, NONE, NONE));
	if (u->registered[User::NICK] == false)
	{
		if (!u->registered[User::PASS])
			return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, NONE, NONE, NONE));
		while (s.nicknameExists(nickname) == true)
			nickname.append(to_str(now)); // avoid collision and loop with client
		out (BOLD("Setting nickname to ") << nickname);
		u->registered[User::NICK] = true;
	}
	else if (u->registered[User::NICK] == true)
	{
		if (s.nicknameExists(nickname) == true)
		{
			s.numeric_reply(u, ERR_NEEDMOREPARAMS, NONE, NONE, NONE);
			quit_s(s, u, cmd);
			return;
		}
		out (BOLD("Changing nick name from ") << u->nickname << " to " << *(cmd.begin() + 1));
		server_relay(u, cmd, s.server_users);
	}
	if (u->HasCompletedRegistration() == true && u->registered[User::WELCOMED] == false)
	{
		s.numeric_reply(u, "001", NONE, NONE, NONE);
		s.numeric_reply(u, "002", NONE, NONE, NONE);
		s.numeric_reply(u, "003", NONE, NONE, NONE);
		s.numeric_reply(u, "004", NONE, NONE, NONE);
		u->registered[User::WELCOMED] = true;
		out("Answer sent to " << u->socket_descriptor);
	}
	u->setNickName(nickname);
}
