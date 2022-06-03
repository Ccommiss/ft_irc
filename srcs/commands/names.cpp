/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:49:45 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 18:14:01 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
** 	  Command: NAMES
**    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**
**    By using the NAMES command, a user can list all nicknames that are
**    visible to him. For more details on what is visible and what is not,
**    see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
**    <channel> parameter specifies which channel(s) to return information
**    about.  There is no error reply for bad channel names.
**
**    If no <channel> parameter is given, a list of all channels and their
**    occupants is returned.  At the end of this list, a list of users who
**    are visible but either not on any channel or not on a visible channel
**    are listed as being on `channel' "*".
**
**    If the <target> parameter is specified, the request is forwarded to
**    that server which will generate the reply.
**
**    Wildcards are allowed in the <target> parameter.
**
**    Numerics:
**
**            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**            RPL_NAMREPLY                    RPL_ENDOFNAMES
**
**    Examples:
**
**    NAMES #twilight_zone,#42        ; Command to list visible users on
**                                    #twilight_zone and #42
**
**    NAMES                           ; Command to list all visible
**                                    channels and users
**
*/

void Commands::names(Server &s, User *u, std::vector<std::string> cmd)
{
	/* Display all users of all channels */
	if (cmd.size() == 1)
	{
		for (std::map<std::string, Channel *>::iterator it = s.chans.begin(); it != s.chans.end(); it++)
		{
			if (!it->second->isPrivateForUser(u))
			{
				s.numeric_reply(u, RPL_NAMREPLY, it->first, NONE, NONE);
				s.numeric_reply(u, RPL_ENDOFNAMES, it->first, NONE, NONE);
			}
		}
	}
	else
	{
		std::vector<std::string> chans = tokenize(*(cmd.begin() + 1), ',');
		for (size_t i = 0; i < chans.size(); i++)
		{
			if (s.chanExists(chans[i]) && !s.chans[chans[i]]->isPrivateForUser(u))
			{
				s.numeric_reply(u, RPL_NAMREPLY, chans[i], NONE, NONE);
				s.numeric_reply(u, RPL_ENDOFNAMES, chans[i], NONE, NONE);
			}
		}
	}
}
