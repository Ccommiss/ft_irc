#include "Server.hpp"
#include "Answers.hpp"




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
**    Numeric Replies:
** 
**            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
**            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
**            ERR_CHANNELISFULL               ERR_BADCHANMASK
**            ERR_NOSUCHCHANNEL OK               ERR_TOOMANYCHANNELS
**            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
**            RPL_TOPIC
*/

void Commands::join(Server &s, User *u, std::vector<std::string> arg) // exit ou quit
{
	start;
	std::string chan_name = *(arg.begin() + 1);
	std::map<std::string, Channel *>::const_iterator it = s.chans.find(chan_name);

	// gestion err
	if (chan_name[0] != '#')
	{
		s.numeric_reply(u, "403", &chan_name);
		return ; 
	} 

	if (it == s.chans.end())
	{
		out("Creating new channel");
		Channel *chan = new Channel(chan_name, u);
		s.chans.insert(std::pair<std::string, Channel *>(chan_name, chan));
		server_relay(u, arg, u);
	}
	else
	{
		std::cout << "adding_user " << u->getName() << std::endl;
		s.chans[chan_name]->add_user(u);
		// u.joined_chans.push_back(s.chans[chan_name]); a faire dans adduser, creer vecteur pour specifier chans joints par le user
	}
   
	/* Server informing all chan users */
	std::map<std::string *, User *> chan_users = s.chans.find(chan_name)->second->getUsers();
	server_relay(u, arg, chan_users);
	/* RPL 331 */
	
	s.numeric_reply(u, "353", s.chans[chan_name]);
	s.numeric_reply(u, "366", s.chans[chan_name]);
	if (s.chans[chan_name]->isTopicSet() == true)
		s.numeric_reply(u, "332",  s.chans[chan_name]);
}