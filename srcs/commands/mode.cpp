
#include "Server.hpp"
#include "Answers.hpp"

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
*/
// MODE #TRUC -/+[options] [mode params]

/*
**    The various modes available for channels are as follows:
**
**         O - give "channel creator" status;               // VECTOR LIST
**         o - give/take channel operator privilege;        // VECTOR LIST
**         v - give/take the voice privilege;               // VECTOR LIST
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







void handleUserModes()
{

}


void handleChannelModes(Server &s, User *u, std::vector<std::string> cmd)
{
	std::string chan_name 				= *(cmd.begin() + 1);
	if (!s.chanExists(chan_name))
	{
		out("Chan does not exist") 
		return; // NO SUCH NICK ? mais pas specifie
	}
	if (cmd.size() == 2) // just MODE #chan 
		return (s.numeric_reply(u, RPL_CHANNELMODEIS, chan_name, printModes(s.chans[chan_name]), NONE)); //
	
	std::string modes 					= *(cmd.begin() + 2);
	std::vector<std::string> mode_params;
	(cmd.size() > 3) ? (mode_params.insert(mode_params.begin(), cmd.begin() + 3, cmd.end())) : (mode_params.push_back("")); // tout le reste n fait
		

	/* Note : to list info, one can ask for e.g. /mode #chan +b or /mode #chan I, so +/- is not
	alway set. This is not taken into account yet */
	Channel *chan = s.chans[chan_name];
	bool value = modes[0] == '+' ? true : false;
	for (size_t i = 1; i < modes.length(); i++)
	{
		std::string res = chan->setMode(u, modes[i], value, mode_params);
		/* FOR RPL_BAN LIST, one answer per ban mask */
		if (res == RPL_BANLIST || res == RPL_INVITELIST)// || res == RPL_EXCEPTLIST)
		{
			if (res == RPL_BANLIST)
			{
				for (size_t i = 0; i < chan->getBannedMasks().size(); i++)
					s.numeric_reply(u, RPL_BANLIST, chan->_name, chan->getBannedMasks().at(i), NONE);
				s.numeric_reply(u, RPL_ENDOFBANLIST, chan->_name, to_str(chan->getBannedMasks().size()), NONE);
			}
			else if (res == RPL_INVITELIST)
			{
				for (size_t i = 0; i < chan->getInvitedMasks().size(); i++)
					s.numeric_reply(u, RPL_INVITELIST, chan->_name, chan->getInvitedMasks().at(i), NONE);
				s.numeric_reply(u, RPL_ENDOFINVITELIST, chan->_name, NONE, NONE);
			}
		}
		else if (res.length() != 0)
			s.numeric_reply(u, res, chan->_name, NONE, NONE);
		else
		{
			std::string params = mode_params.size() > 0 ? vecToString(mode_params) : "No params";
			s.numeric_reply(u, RPL_CHANNELMODEIS, chan->_name, to_str(modes[i]), params); //
			
		}
	}
	server_relay(u, cmd, chan->getUsers());
	chan->displayModes();

}

void Commands::mode(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() == 1)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	std::string target = *(cmd.begin() + 1);

	/* Channel Modes */
	if (target[0] == '+') // ne supportent pas les chans modes
		return (s.numeric_reply(u, ERR_NOCHANMODES, target, NONE, NONE));
	if (target[0] == '#') // ou & ....
	{
		handleChannelModes(s, u, cmd);
	}
	/* User Modes a factoriser */
	else
	{
		std::string empty = " lol";
		std::string nickname_asked = cmd.size() > 1 ? *(cmd.begin() + 1) : ""; // #truc
		std::string modes = cmd.size() > 2 ? *(cmd.begin() + 2) : "";		   // +=....
		std::vector<std::string> mode_params;
		(cmd.size() > 3) ? (mode_params.insert(mode_params.begin(), cmd.begin() + 3, cmd.end())) : (mode_params.push_back("")); // tout le reste n fait

		if (nickname_asked != u->nickname)
			return s.numeric_reply(u, ERR_USERSDONTMATCH, u->nickname, NONE, NONE); // pas le droit de demander mode pour les autres

		bool value = modes[0] == '+' ? true : false;
		for (size_t i = 1; i < modes.length(); i++)
		{
			/* A voir. Mode query pour limit par ex (flag l doit etre possible 4.2.9 rfc 2811) */
			/* hypothese : si pas de valeur on voit genre MODE e, a tester */
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
}
