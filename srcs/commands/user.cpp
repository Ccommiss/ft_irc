/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:15:54 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 18:22:38 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**    Command: USER
**    Parameters: <user> <mode> <unused> <realname>
**
**    The USER command is used at the beginning of connection to specify
**    the username, hostname and realname of a new user.
**
**    The <mode> parameter should be a numeric, and can be used to
**    automatically set user modes when registering with the server.  This
**    parameter is a bitmask, with only 2 bits having any signification: if
**    the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
**    set, the user mode 'i' will be set.  (See Section 3.1.5 "User
**    Modes").
**
**    The <realname> may contain space characters.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
**
**    Example:
**
**    USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
**                                    username of "guest" and real name
**                                    "Ronnie Reagan".
**
**    USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
**                                    username of "guest" and real name
**                                    "Ronnie Reagan", and asking to be set
**                                    invisible.
*/

void Commands::setUser(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() < 5)
		return(s.numeric_reply(u, ERR_NEEDMOREPARAMS, NONE, NONE, NONE));
	u->setName(*(cmd.begin() + 1));
	u->real_name = (*(cmd.begin() + 4));
	if (u->registered[User::USER] == false)
	{
		if (!u->registered[User::PASS])
		{
			s.numeric_reply(u, ERR_NEEDMOREPARAMS, NONE, NONE, NONE);
			quit_s(s, u, cmd);
			return;
		}
		u->registered[User::USER] = true;
	}
	if (u->HasCompletedRegistration() == true && u->registered[User::WELCOMED] == false)
	{
		s.numeric_reply(u, "001", NONE, NONE, NONE);
		s.numeric_reply(u, "002", NONE, NONE, NONE);
		s.numeric_reply(u, "003", NONE, NONE, NONE);
		s.numeric_reply(u, "004", NONE, NONE, NONE);
		u->registered[User::WELCOMED] = true;
	}
}
