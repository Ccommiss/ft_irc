/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:48:11 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 18:23:29 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**  Command: LIST
**    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**
**    The list command is used to list channels and their topics.  If the
**    <channel> parameter is used, only the status of that channel is
**    displayed.
**
**    If the <target> parameter is specified, the request is forwarded to
**    that server which will generate the reply.
**
**    Wildcards are allowed in the <target> parameter.
**
**    Numeric Replies:
**
**            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**            RPL_LIST                        RPL_LISTEND
**
**    Examples:
**
**    LIST                            ; Command to list all channels.
**
**    LIST #twilight_zone,#42         ; Command to list channels
**                                    #twilight_zone and #42
*/

void Commands::list			(Server &s, User *u, std::vector<std::string> cmd)
{
	std::map<std::string, Channel *> chans = s.chans;

	if (cmd.size() == 1) /* LIST */
	{
		for (std::map<std::string, Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
		{
			if (!it->second->isPrivateForUser(u))
				s.numeric_reply(u, RPL_LIST, it->second->_name, it->second->_name, it->second->getTopic());
		}
		s.numeric_reply(u, RPL_LISTEND, NONE, NONE, NONE);
	}
	else				/* LIST #chan1,#chan2 */
	{
		std::vector<std::string> chansToDisplay = tokenize(cmd[0], ',');
		for (std::vector<std::string>::iterator it = chansToDisplay.begin(); it != chansToDisplay.end(); it++)
		{
			if (s.chanExists(*it) && !s.chans[*it]->isPrivateForUser(u))
				s.numeric_reply(u, RPL_LIST, s.chans[*it]->_name, s.chans[*it]->_name, s.chans[*it]->getTopic());
			
		}
		s.numeric_reply(u, RPL_LISTEND, NONE, NONE, NONE);
	}
}
