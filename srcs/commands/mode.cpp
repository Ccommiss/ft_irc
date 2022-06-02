
#include "Server.hpp"
#include "Answers.hpp"

/*
**
**    Command: MODE
**    Parameters: <nickname>
**                *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
**
**    The user MODE's are typically changes which affect either how the
**    client is seen by others or what 'extra' messages the client is sent.
**
**    A user MODE command MUST only be accepted if both the sender of the
**    message and the nickname given as a parameter are both the same.  If
**    no other parameter is given, then the server will return the current
**    settings for the nick.
**
**       The available modes are as follows:
**
**            a - user is flagged as away;
**            i - marks a users as invisible;
**            w - user receives wallops;
**            r - restricted user connection;
**            o - operator flag;
**            O - local operator flag;
**            s - marks a user for receipt of server notices.
**
**    Additional modes may be available later on.
**
**    The flag 'a' SHALL NOT be toggled by the user using the MODE command,
**    instead use of the AWAY command is REQUIRED.
**
**    If a user attempts to make themselves an operator using the "+o" or
**    "+O" flag, the attempt SHOULD be ignored as users could bypass the
**    authentication mechanisms of the OPER command.  There is no
**    restriction, however, on anyone `deopping' themselves (using "-o" or
**    "-O").
**
**    On the other hand, if a user attempts to make themselves unrestricted
**    using the "-r" flag, the attempt SHOULD be ignored.  There is no
**    restriction, however, on anyone `deopping' themselves (using "+r").
**    This flag is typically set by the server upon connection for
**    administrative reasons.  While the restrictions imposed are left up
**    to the implementation, it is typical that a restricted user not be
**    allowed to change nicknames, nor make use of the channel operator
**    status on channels.
**
**    The flag 's' is obsolete but MAY still be used.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
**            ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS
**
**    Examples:
**
**    MODE WiZ -w                     ; Command by WiZ to turn off
**                                    reception of WALLOPS messages.
**
**    MODE Angel +i                   ; Command from Angel to make herself
**                                    invisible.
**
**    MODE WiZ -o                     ; WiZ 'deopping' (removing operator
**                                    status).
**
*/

void handleUserModes(Server &s, User *u, std::string nickname_asked, std::vector<std::string> cmd)
{
	start;
	/* No argument supplied, e.g. "MODE Wiz" : information is sent back */
	if (cmd.size() == 2)
		return (s.numeric_reply(u, RPL_UMODEIS, nickname_asked, NONE, NONE));

	std::string modes = trim(*(cmd.begin() + 2));		   // +=letters....
	std::vector<std::string> mode_params; // vaut peut etre le coup d'envoyer juste une string car pas sure que puisse y avoir plusieurs args

	(cmd.size() > 3) ? (mode_params.insert(mode_params.begin(), cmd.begin() + 3, cmd.end())) : (mode_params.push_back(""));

	/* Cannot ask modification for another username */
	if (nickname_asked != u->nickname)
		return s.numeric_reply(u, ERR_USERSDONTMATCH, u->nickname, NONE, NONE); // pas le droit de demander mode pour les autres

	/* Setting the value. + is true, - is false */
	bool value = modes[0] == '+' ? true : false;
	for (size_t i = 1; i < modes.length(); i++)
	{
		std::string res = u->setMode(modes[i], value, mode_params);
		if (res.length() != 0)
			s.numeric_reply(u, res, u->nickname, NONE, NONE);
		else
		{
			s.numeric_reply(u, RPL_CHANNELMODEIS, u->nickname, modes, vecToString(mode_params)); //
			server_relay(u, cmd, u);
		}
	}
}



/*
**    Command: MODE (channel)
**    Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
**
**    The MODE command is provided so that users may query and change the
**    characteristics of a channel.  For more details on available modes
**    and their uses, see "Internet Relay Chat: Channel Management" [IRC-
**    CHAN].  Note that there is a maximum limit of three (3) changes per
**    command for modes that take a parameter.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_KEYSET
**            ERR_NOCHANMODES  ok               ERR_CHANOPRIVSNEEDED ok
**            ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
**            RPL_CHANNELMODEIS
**            RPL_BANLIST                     RPL_ENDOFBANLIST
**            RPL_EXCEPTLIST (mask etc)       RPL_ENDOFEXCEPTLIST
**            RPL_INVITELIST                  RPL_ENDOFINVITELIST
**            RPL_UNIQOPIS
**
**    The various modes available for channels are as follows:
**
**         O - give "channel creator" status;
**         o - give/take channel operator privilege;
**         v - give/take the voice privilege;
**
**         a - toggle the anonymous channel flag;
**         i - toggle the invite-only channel flag;
**         m - toggle the moderated channel;
**         n - toggle the no messages to channel from clients on the
**             outside;
**         q - toggle the quiet channel flag;
**         p - toggle the private channel flag;
**         s - toggle the secret channel flag;
**         r - toggle the server reop channel flag;
**         t - toggle the topic settable by channel operator only flag;
**
**         k - set/remove the channel key (password);
**         l - set/remove the user limit to channel;
**
**         b - set/remove ban mask to keep users out;
**         e - set/remove an exception mask to override a ban mask;
**         I - set/remove an invitation mask to automatically override
**             the invite-only flag;
*/




void	rpl_lists(Server &s, User *u, std::string chan_name, std::vector<std::string> list, std::string rpl_name, std::string rpl_end_name)
{
	for (size_t i = 0; i < list.size(); i++)
		s.numeric_reply(u, rpl_name, chan_name, list.at(i), NONE);
	s.numeric_reply(u, rpl_end_name, chan_name, to_str(list.size()), NONE);
}


bool	takeArg(char mode)
{
	switch (mode)
	{
		case 'l':
			return true;
		case 'e':
			return true;
		case 'I':
			return true;
		case 'k':
			return true;
		case 'b':
			return true;
		case 'v':
			return true;
		case 'o':
			return true;
		case 'O':
			return true;
	}
	return false;
}

void handleChannelModes(Server &s, User *u, std::string chan_name, std::vector<std::string> cmd)
{
	start;
	if (!s.chanExists(chan_name))
	{
		out("Chan does not exist")
		return; // NO SUCH NICK ? mais pas specifie
	}
	if (cmd.size() == 2) // just MODE #chan
		return (s.numeric_reply(u, RPL_CHANNELMODEIS, chan_name, printModes(s.chans[chan_name]), NONE)); //

	std::string modes 					= *(cmd.begin() + 2);
	std::vector<std::string> 			mode_params;
	(cmd.size() > 3) ? (mode_params.insert(mode_params.begin(), cmd.begin() + 3, cmd.end())) : (mode_params.push_back("")); // tout le reste n fait


	/* Note : to list info, one can ask for e.g. /mode #chan +b or /mode #chan I, so +/- is not
	alway set. This is not taken into account yet */

	Channel *chan = s.chans[chan_name];
	int a = (modes[0] == '-' || modes[0] == '+') ? 1 : 0;
	bool value = modes[0] == '-' ? false : true; /* Making true even if no + before mode option. */
	/* if we have MODE something, starting at 0; else, starting at 1 to skip the +/- */
	out ("Before loop")

	int paramLocation = 0;
	bool already_set;
	std::string msg = "MODE " + chan_name + " "; /*Le msg n'affiche que ce qui a fonctionne */ 
	msg += modes[0]; //
	std::string workingparams = "";
	std::string res;
	for (size_t i = a; i < modes.length(); i++)
	{
		out ("in loop")
		std::string currParam = "";
		if (takeArg(modes[i]) && i <= mode_params.size() + 1) // i commence a 1; donc arg 1 va avec param 0 etc.
		{
			try 
			{
				currParam = mode_params.at(paramLocation);
				paramLocation++;
			}
			catch (std::exception &e)
			{
				currParam = "";
			}
		}
		out ("SENDING PARAMS << " << currParam << "TO MIDE " << modes[i] << "value " << value);
		value == chan->hasMode(modes[i]) ? already_set = true: already_set = false;
		if (!already_set)
			res = chan->setMode(u, modes[i], value, currParam);
		out ("IS ALREADY SET ?" << already_set)

		/* FOR RPL_BAN LIST, one answer per ban mask */
		if (!already_set && (res == RPL_BANLIST || res == RPL_INVITELIST))// || res == RPL_EXCEPTLIST)
		{
			if (res == RPL_BANLIST)
				rpl_lists(s, u, chan_name, chan->getBannedMasks(), RPL_BANLIST, RPL_ENDOFBANLIST);
			else if (res == RPL_INVITELIST)
				rpl_lists(s, u, chan_name, chan->getInvitedMasks(), RPL_INVITELIST, RPL_ENDOFINVITELIST);
		}
		else if (!already_set && res == ERR_NOSUCHNICK)
			s.numeric_reply(u, res, currParam, NONE, NONE);
		else if (!already_set && res.length() != 0) /* Erreur */
			s.numeric_reply(u, res, chan->_name, NONE, NONE);
		else if (!already_set) /* ca a marche */ 
		{
			workingparams += currParam + " ";
			msg += modes[i]; // on rajoute la lettre
		}
	}
	/* Si une erreur, ne pas envoyer ? */
	msg += " " + workingparams;
	if (workingparams.length() != 0) // meme si vide y a des espaces 
		server_relay(u, tokenize(msg, ' '), chan->getUsers()); // si il est ban faut l'enlever apres... comment faire sans alourdir ?
	chan->displayModes();
}




void Commands::mode(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() == 1)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));
	std::string target = *(cmd.begin() + 1);
	if (target[0] == '+') /* + (unmoderated) chans do not support modes or operators */
		return (s.numeric_reply(u, ERR_NOCHANMODES, target, NONE, NONE));
	if (target[0] == '#') // ou & ....
		handleChannelModes(s, u, target, cmd);
	else
		handleUserModes(s, u, target, cmd);
}
