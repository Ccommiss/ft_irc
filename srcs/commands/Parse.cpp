/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:52:28 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/06 12:14:50 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Commands.hpp"

/*
**  parse_cmd
**  @brief parses the commands as received for example : NICK <newname>
**  @param user the user (client) that initiated the request
**  @param s the server instance
**  @returns none
*/

void Commands::parse_cmd(User *user, Server &s) // envoyer users[i]
{
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
