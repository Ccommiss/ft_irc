/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:53:47 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 14:54:06 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**  Command: PART
**    Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
**
**    The PART command causes the user sending the message to be removed
**    from the list of active members for all given channels listed in the
**    parameter string.  If a "Part Message" is given, this will be sent
**    instead of the default message, the nickname.  This request is always
**    granted by the server.
**
**    Servers MUST be able to parse arguments in the form of a list of
**    target, but SHOULD NOT use lists when sending PART messages to
**    clients.
**
**   Numeric Replies:
**
**         ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
**         ERR_NOTONCHANNEL
*/

void Commands::part(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() == 1)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	std::vector<std::string> out = tokenize(*(cmd.begin() + 1), ','); /* Channel names */
	std::string bye_msg = implodeMessage(cmd.begin() + 2, cmd.end()); /* Leave message */

	for (std::vector<std::string>::iterator nb_chans_it = out.begin(); nb_chans_it != out.end(); nb_chans_it++)
	{
		std::string chan_name = trim(*nb_chans_it);
		if (!s.chanExists(chan_name) || (s.chanExists(chan_name) && s.chans[chan_name]->isPrivateForUser(u)))
			s.numeric_reply(u, ERR_NOSUCHCHANNEL, chan_name, NONE, NONE);
		else
		{
			std::map<std::string *, User *> chan_users = s.chans[chan_name]->getUsers();
			if (!s.chans[chan_name]->isInChan(u))
				s.numeric_reply(u, ERR_NOTONCHANNEL, chan_name, NONE, NONE);
			else
			{
				s.chans[chan_name]->remove_user(u);
				u->leaveChan(s.chans[chan_name]);
				if (s.chans[chan_name]->getUsers().size() == 0) /* Deleting channel if nobody is in */
				{
					delete s.chans[chan_name];
					s.chans.erase(s.chans.find(chan_name));
				}
				std::string msg[] = {*(cmd.begin()), chan_name, bye_msg};
				std::vector<std::string> part_chan_msg(msg, msg + 3);
				server_relay(u, part_chan_msg, chan_users);
			}
		}
	}
}
