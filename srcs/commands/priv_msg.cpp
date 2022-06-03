#include "Server.hpp"
#include "Answers.hpp"

/*
**       Command: PRIVMSG
**    Parameters: <msgtarget> <text to be sent>
**
**    PRIVMSG is used to send private messages between users, as well as to
**    send messages to channels.  <msgtarget> is usually the nickname of
**    the recipient of the message, or a channel name.
**
**    The <msgtarget> parameter may also be a host mask (#<mask>) or server
**    mask ($<mask>).  In both cases the server will only send the PRIVMSG
**    to those who have a server or host matching the mask.  The mask MUST
**    have at least 1 (one) "." in it and no wildcards following the last
**    ".".  This requirement exists to prevent people sending messages to
**    "#*" or "$*", which would broadcast to all users.  Wildcards are the
**    '*' and '?'  characters.  This extension to the PRIVMSG command is
**    only available to operators.
**
**    Numeric Replies:
**
**            ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
**            ERR_CANNOTSENDTOCHAN ok           ERR_NOTOPLEVEL
**            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
**            ERR_NOSUCHNICK
**            RPL_AWAY
**
**    Examples:
**
**    :Angel!wings@irc.org PRIVMSG Wiz :Are you receiving this message ?
**                                    ; Message from Angel to Wiz.
**
**    PRIVMSG Angel :yes I'm receiving it !
**                                    ; Command to send a message to Angel.
**
**    PRIVMSG jto@tolsun.oulu.fi :Hello !
**                                    ; Command to send a message to a user
**                                    on server tolsun.oulu.fi with
**                                    username of "jto".
**
**    PRIVMSG kalt%millennium.stealth.net@irc.stealth.net :Are you a frog?
**                                    ; Message to a user on server
**                                    irc.stealth.net with username of
**                                    "kalt", and connected from the host
**                                    millennium.stealth.net.
**
**    PRIVMSG kalt%millennium.stealth.net :Do you like cheese?
**                                    ; Message to a user on the local
**                                    server with username of "kalt", and
**                                    connected from the host
**                                    millennium.stealth.net.
**
**    PRIVMSG Wiz!jto@tolsun.oulu.fi :Hello !
**                                    ; Message to the user with nickname
**                                    Wiz who is connected from the host
**                                    tolsun.oulu.fi and has the username
**                                    "jto".
**
**    PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
**                                    ; Message to everyone on a server
**                                    which has a name matching *.fi.
**
**    PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
**                                    ; Message to all users who come from
**                                    a host which has a name matching
**                                    *.edu.
**
*/

void send_pm(Server &s, User *u, std::string dest_nick, std::vector<std::string> cmd)
{
	User *target = NULL;
	if (s.findByName(dest_nick, &target) == true)
	{
		server_relay(u, cmd, target);
		if (target->isAway())
			s.numeric_reply(u, RPL_AWAY, dest_nick, target->getAwayMsg(), NONE);
	}
	else
		return (s.numeric_reply(u, ERR_NOSUCHNICK, dest_nick, NONE, NONE));
}


/* Can i send msg without joining chan ?
** In principle yes but most servers forbid (channel are + n mode )
**   n - toggle the no messages to channel from clients on the
**            outside; // le faire par defaut ?
** source : https://stackoverflow.com/questions/21528058/can-i-send-a-message-to-an-irc-channel-without-joining-it
*/

void send_channel(Server &s, User *u, std::string dest_channel, std::vector<std::string> cmd)
{

	if (!s.chanExists(dest_channel))
		return (s.numeric_reply(u, ERR_NOSUCHNICK, dest_channel, NONE, NONE));
	Channel *chan = s.chans[dest_channel];
	if (chan->isBanned(u) || chan->matchBannedMask(u))
		return (s.numeric_reply(u, ERR_CANNOTSENDTOCHAN, dest_channel, NONE, NONE));
	if (chan->hasMode('n') && !chan->isInChan(u))
		return (s.numeric_reply(u, ERR_CANNOTSENDTOCHAN, dest_channel, NONE, NONE));
	/* On moderated channel ('m' flag), only operators and voiced ppl can talk */
	if (chan->hasMode('m') && !chan->isOperator(u) && !chan->isVoiced(u))
		return (s.numeric_reply(u, ERR_CANNOTSENDTOCHAN, dest_channel, NONE, NONE));
	{
		out("Sending to channel >>> " << dest_channel)
			s.chans[dest_channel]
				->printUsers();
		std::map<std::string *, User *> chan_users(s.chans[dest_channel]->getUsers());
		chan_users.erase(&u->nickname);
		server_relay(u, cmd, chan_users);
	}
}

/*
**  Command: PRIVMSG
**  @param cmd : <msgtarget> <text to be sent>
**  Triggered by /msg (login)
** or talking in a chan
*/

void Commands::priv_msg(Server &s, User *u, std::vector<std::string> cmd)
{
	start;
	if (cmd.size() < 3)
		return (s.numeric_reply(u, ERR_NOTEXTTOSEND, NONE, NONE, NONE));
	std::string dest = *(cmd.begin() + 1);
	if (dest.compare(0, 1, "#", 0, 1) == 0 || dest.compare(0, 1, "+", 0, 1) == 0 )
		send_channel(s, u, dest, cmd);
	else
		send_pm(s, u, dest, cmd);
}
