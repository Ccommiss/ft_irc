/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:48:03 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/06 11:48:25 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**      Command: KICK
**    Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
**                [<comment>]
**
**    The KICK command can be used to request the forced removal of a user
**    from a channel.  It causes the <user> to PART from the <channel> by
**    force.  For the message to be syntactically correct, there MUST be
**    either one channel parameter and multiple user parameter, or as many
**    channel parameters as there are user parameters.  If a "comment" is
**    given, this will be sent instead of the default message, the nickname
**    of the user issuing the KICK.
**
**    The server MUST NOT send KICK messages with multiple channels or
**    users to clients.  This is necessarily to maintain backward
**    compatibility with old client software.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
**            ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
**            ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL
**
**    Examples:
**
**    KICK &Melbourne Matthew         ; Command to kick Matthew from
**                                    &Melbourne
**
**    KICK #Finnish John :Speaking English
**                                    ; Command to kick John from #Finnish
**                                    using "Speaking English" as the
**                                    reason (comment).
**
**    :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
**                                    ; KICK message on channel #Finnish
**                                    from WiZ to remove John from channel
*/

void Commands::kick(Server &s, User *u, std::vector<std::string> cmd)
{
	start;
	if (cmd.size() < 3)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	std::list<std::string> chan_names = tokenize_list((cmd[1]), ',');
	std::list<std::string> user_names = tokenize_list((cmd[2]), ',');
	std::string msg = implodeMessage(cmd.begin() + 3, cmd.end());
	User *to_kick = NULL;

	for (std::list<std::string>::iterator chanToKick = chan_names.begin(); chanToKick != chan_names.end(); chanToKick++)
	{
		std::vector<std::string> txt;
		txt.push_back("KICK");
		std::string chan_name = *chanToKick;
		txt.push_back(chan_name);
		if (!s.chanExists(chan_name))
			return (s.numeric_reply(u, ERR_NOSUCHCHANNEL, chan_name, NONE, NONE));
		else if (!s.chans[chan_name]->isOperator(u))
			return (s.numeric_reply(u, ERR_CHANOPRIVSNEEDED, chan_name, NONE, NONE));
		for (std::list<std::string>::iterator user_name = user_names.begin(); user_name != user_names.end(); user_name++)
		{
			if (s.chans[chan_name]->findByName(*user_name, &to_kick) == false)
				return (s.numeric_reply(u, ERR_USERNOTINCHANNEL, chan_name, NONE, NONE));
			else if (s.chans[chan_name]->findByName(*user_name, &to_kick) == true)
			{
				txt.push_back(to_kick->getNickName());
				txt.push_back(msg);
				server_relay(u, txt, s.chans[chan_name]->getUsers());
				s.chans[chan_name]->remove_user(to_kick);
				to_kick->leaveChan(s.chans[chan_name]);
				if (s.chans[chan_name]->getUsers().size() == 0)
				{
					delete s.chans[chan_name];
					s.chans.erase(s.chans.find(chan_name));
				}
			}
		}
	}
}