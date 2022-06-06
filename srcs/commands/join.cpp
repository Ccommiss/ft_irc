/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:47:34 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/06 11:47:51 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

#define MAX_CHANNEL 30

/*
**       Command: JOIN
**    Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
**                / "0"
**
**    The JOIN command is used by a user to request to start listening to
**    the specific channel.  Servers MUST be able to parse arguments in the
**    form of a list of target, but SHOULD NOT use lists when sending JOIN
**    messages to clients.
**
**    Once a user has joined a channel, he receives information about
**    all commands his server receives affecting the channel.  This
**    includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
**    This allows channel members to keep track of the other channel
**    members, as well as channel modes.
**
**    If a JOIN is successful, the user receives a JOIN message as
**    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
**    the list of users who are on the channel (using RPL_NAMREPLY), which
**    MUST include the user joining.
**
**    Note that this message accepts a special argument ("0"), which is
**    a special request to leave all channels the user is currently a member
**    of.  The server will process this message as if the user had sent
**    a PART command (See Section 3.2.2) for each channel he is a member
**    of.
**
** 	JOIN #foo,#bar fubar,foobar ==> ex with key
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS OK            ERR_BANNEDFROMCHAN
**            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
**            ERR_CHANNELISFULL               ERR_BADCHANMASK
**            ERR_NOSUCHCHANNEL OK              ERR_TOOMANYCHANNELS
**            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
**            RPL_TOPIC OK
*/

void Commands::leaveAllChans(User *u)
{
	for (std::vector<Channel *>::const_iterator chans = u->getJoinedChannels().begin(); chans != u->getJoinedChannels().end(); chans++)
	{
		u->leaveChan(*chans);
		std::string msg[] = {"PART", (*chans)->_name};
		std::vector<std::string> part_msg(msg, msg + 2);
		server_relay(u, part_msg, u);
	}
}

void Commands::createChan(Server &s, std::string chan_name, User *u, bool *joined)
{
	Channel *chan = new Channel(chan_name, u);
	if (chan_name[0] == '+')
		chan->setMode(u, 't', true, ""); /* + channel are unmoderated, only t is toggled see 2.3 rfc 2811 */
	u->joinChan(chan);
	s.chans.insert(std::pair<std::string, Channel *>(chan_name, chan));
	*joined = true;
}

void Commands::simpleAdd(Server &s, Channel *chan, User *u, bool *joined, std::vector<std::string> *pass, size_t i)
{
	if (chan->isInChan(u))
		return;
	else if (chan->hasKey() && ((pass->size() <= i) || (!chan->isCorrectPass(pass->at(i)))))
		s.numeric_reply(u, ERR_BADCHANNELKEY, chan->_name, NONE, NONE);
	else if (chan->isBanned(u) || chan->matchBannedMask(u))
		s.numeric_reply(u, ERR_BANNEDFROMCHAN, chan->_name, NONE, NONE);
	else if (chan->hasMode('l') && chan->getUsers().size() + 1 > chan->getLimit())
		s.numeric_reply(u, ERR_CHANNELISFULL, chan->_name, NONE, NONE);
	else if (u->getJoinedChannels().size() >= MAX_CHANNEL)
		s.numeric_reply(u, ERR_TOOMANYCHANNELS, chan->_name, NONE, NONE);
	else
	{
		u->joinChan(chan);
		chan->add_user(u);
		*joined = true;
	}
}

void Commands::join(Server &s, User *u, std::vector<std::string> cmd) 
{
	if (cmd.size() == 1) 
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	size_t i = 0;
	bool joined = false;
	std::vector<std::string> chans = tokenize((cmd[1]), ',');
	std::vector<std::string> pass;

	if (cmd.size() >= 3)
		pass = tokenize((cmd[2]), ',');

	for (std::vector<std::string>::iterator nb_chans_it = chans.begin(); nb_chans_it != chans.end(); nb_chans_it++)
	{
		std::string chan_name = chans[i];
		joined = false;

		/* Case 0 : Channel name is not well fomatted */
		if (chan_name[0] != '#' && chan_name[0] != '+') /* # and + chans are the only supported */ 
			s.numeric_reply(u, ERR_BADCHANMASK, chan_name, NONE, NONE);
		/* Case 1 : JOIN 0 -> leaving all chans */
		else if (*nb_chans_it == "0")
			return (leaveAllChans(u));
		/* Case 2 : Channel does not exist */
		else if (!s.chanExists(chan_name))
			createChan(s, chan_name, u, &joined);
		/* Case 4 : Channel does exist but invite only */
		else if (s.chans[chan_name]->hasMode('i') && (!s.chans[chan_name]->isInvited(u) && !s.chans[chan_name]->matchInviteMask(u)))
			s.numeric_reply(u, ERR_INVITEONLYCHAN, chan_name, NONE, NONE);
		/* Case 5 : Channel does exist and ok !! */
		else
			simpleAdd(s, s.chans[chan_name], u, &joined, &pass, i);

		/* Server informing all chan users */
		if (joined == true)
		{
			std::map<std::string *, User *> chan_users = s.chans[chan_name]->getUsers();
			std::string msg[] = {*(cmd.begin()), chan_name};
			std::vector<std::string> join_chan_msg(msg, msg + 2);

			server_relay(u, join_chan_msg, chan_users);
			s.numeric_reply(u, RPL_NAMREPLY, chan_name, NONE, NONE);
			s.numeric_reply(u, RPL_ENDOFNAMES, chan_name, NONE, NONE);
			if (s.chans[chan_name]->isTopicSet() == true)
				s.numeric_reply(u, RPL_TOPIC, chan_name, s.chans[chan_name]->getTopic(), NONE);
		}
		i++;
	}
}
