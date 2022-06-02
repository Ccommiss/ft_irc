#include "User.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Commands.hpp"

void print(std::vector<std::string> vec)
{

	std::vector<std::string>::iterator it;
	for (it = vec.begin(); it != vec.end(); it++)
		out("PARSE CMD = " << *it)
}

/*
**  parse_cmd
**  @brief parses the commands as received for example : NICK <newname>
**  @param user the user (client) that initiated the request
**  @param s the server instance
**  @returns none
*/
void Commands::parse_cmd(User *user, Server &s) // envoyer users[i]
{
	start;
	out ("Buffer : " << user->buffer);
	std::string buff(user->buffer);
	std::vector<std::string> res = tokenize(buff, '\n');
	for (std::vector<std::string>::iterator line = res.begin(); line != res.end(); line++)
	{
		std::vector<std::string> cmd = tokenize(*line, ' ');
		if (cmd.size() > 0 && cmd_map.find(*(cmd.begin())) != cmd_map.end())
		{
			Commands::Cmd a = cmd_map.at(*(cmd.begin()));
			(this->*a)(s, user, cmd);
		}
	}
}
