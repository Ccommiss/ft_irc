/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:55:41 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/06 11:50:48 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**  Command: TOPIC
**    Parameters: <channel> [ <topic> ]
**
**    The TOPIC command is used to change or view the topic of a channel.
**    The topic for channel <channel> is returned if there is no <topic>
**    given.  If the <topic> parameter is present, the topic for that
**    channel will be changed, if this action is allowed for the user
**    requesting it.  If the <topic> parameter is an empty string, the
**    topic for that channel will be removed.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS    ok          ERR_NOTONCHANNEL ok
**            RPL_NOTOPIC             ok        RPL_TOPIC ok
**            ERR_CHANOPRIVSNEEDED    ok        ERR_NOCHANMODES
** 		Channels with '+' as prefix do not support channel modes.
**		t - toggle the topic settable by channel operator only flag;
**    Examples:
**
**    :WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic ; User Wiz setting the
**                                    topic.
**
**    TOPIC #test :another topic      ; Command to set the topic on #test
**                                    to "another topic".
**
**    TOPIC #test :                   ; Command to clear the topic on
**                                    #test.
**
**    TOPIC #test                     ; Command to check the topic for
**                                    #test.
**
*/

void Commands::topic(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() == 1)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	std::string chan_name = cmd[1];
	if (!s.chanExists(chan_name)) 
		return;

	Channel *chan = (s.chans[chan_name]); 
	if (chan->isPrivateForUser(u))
		return;
	if (!chan->isInChan(u))
		return (s.numeric_reply(u, ERR_NOTONCHANNEL, chan_name, "", ""));
	if ((cmd.begin() + 2) != cmd.end()) /* Asking for a change */
	{
		if (chan->hasMode('t') && !chan->isOperator(u))
			return (s.numeric_reply(u, ERR_CHANOPRIVSNEEDED, chan_name, NONE, NONE));
		std::map<std::string *, User *> chan_users = chan->getUsers();
		server_relay(u, cmd, chan_users);
		chan->setTopic(implodeMessage((cmd.begin() + 2), cmd.end()).erase(0,1));
	}
	
	/* In all cases, just topic or after a topic change request : */
	if (chan->isTopicSet() == false) 
		s.numeric_reply(u, RPL_NOTOPIC, chan->_name, NONE, NONE);
	else
		s.numeric_reply(u, RPL_TOPIC, chan->_name, chan->_topic, NONE);
}
