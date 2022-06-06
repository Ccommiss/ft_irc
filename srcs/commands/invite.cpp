/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:47:26 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/06 13:09:08 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**	  Command: INVITE
**    Parameters: <nickname> <channel>
**
**    The INVITE command is used to invite a user to a channel.  The
**    parameter <nickname> is the nickname of the person to be invited to
**    the target channel <channel>.  There is no requirement that the
**    channel the target user is being invited to must exist or be a valid
**    channel.  However, if the channel exists, only members of the channel
**    are allowed to invite other users.  When the channel has invite-only
**    flag set, only channel operators may issue INVITE command.
**
**    Only the user inviting and the user being invited will receive
**    notification of the invitation.  Other channel members are not
**    notified.  (This is unlike the MODE changes, and is occasionally the
**    source of trouble for users.)
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
**            ERR_NOTONCHANNEL                ERR_USERONCHANNEL
**            ERR_CHANOPRIVSNEEDED
**            RPL_INVITING                    RPL_AWAY
**
**    Examples:
**
**    :Angel!wings@irc.org INVITE Wiz #Dust
**
**                                    ; Message to WiZ when he has been
**                                    invited by user Angel to channel
**                                    #Dust
**
**    INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
**                                    #Twilight_zone
**
**
*/

void Commands::invite(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() < 3)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	std::string target = cmd[1];
	std::string chan_name = cmd[2];
	User *to_invite = NULL;
	Channel *chan = NULL;

	if (s.findByName(target, &to_invite) == false) /* Cannot invite a non existing user */
		return (s.numeric_reply(u, ERR_NOSUCHNICK, target, NONE, NONE));
	if (!s.chanExists(chan_name)) /* Cannot invite to an unexisting chan */
		return (s.numeric_reply(u, ERR_NOSUCHNICK, chan_name, NONE, NONE));

	chan = s.chans[chan_name];
	if (!chan->isInChan(u)) /* User inviting is not currently on channel */
		return (s.numeric_reply(u, ERR_NOTONCHANNEL, chan_name, NONE, NONE));
	if (chan->isInChan(to_invite)) /* User invited has already joined channel */
		return (s.numeric_reply(u, ERR_USERONCHANNEL, chan_name, to_invite->nickname, NONE));

	if (!chan->hasMode('i') || (chan->hasMode('i') && chan->isOperator(u)))
		s.chans[chan_name]->addToInviteList(to_invite);
	else if (chan->hasMode('i') && !chan->isOperator(u)) /* In invite only chans, only ope can invite */
		return (s.numeric_reply(u, ERR_CHANOPRIVSNEEDED, chan_name, NONE, NONE));

	server_relay(u, cmd, to_invite);
	s.numeric_reply(u, RPL_INVITING, to_invite->nickname, chan_name, NONE);
	if (to_invite->hasMode('a')) /* Away Mode */
		s.numeric_reply(u, RPL_AWAY, to_invite->nickname, to_invite->getAwayMsg(), NONE);
}