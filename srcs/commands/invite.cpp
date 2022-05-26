
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
	start;
	std::string chan_name = (*(cmd.begin() + 2));
	out("Chan name :" << chan_name);

	if (!s.chanExists(chan_name))
		return;

	if (!s.chans[chan_name]->isInChan(u))
		return (s.numeric_reply(u, ERR_NOTONCHANNEL, chan_name, NONE, NONE));
	std::map<const std::string *, const User *>::iterator it = s.server_users.begin();
	while (it != s.server_users.end())
	{
		if (*(cmd.begin() + 1) == it->second->nickname)
		{
			out("found user !");

			User *to_add = const_cast<User *>(s.server_users[&(it->second->nickname)]); // car mapped type est const
			// seulement si user est un op et que invite only
			if (!s.chans[chan_name]->hasMode('i') || (s.chans[chan_name]->hasMode('i') && s.chans[chan_name]->isOperator(u)))
				s.chans[chan_name]->addToInviteList(to_add);
			if (s.chans[chan_name]->isInChan(to_add))
				return (s.numeric_reply(u, ERR_USERONCHANNEL, to_add->nickname, chan_name, NONE));
			server_relay(to_add, cmd, to_add);
			s.numeric_reply(u, RPL_INVITING, chan_name, NONE, NONE);
			return;
		}
		it++;
	}
}