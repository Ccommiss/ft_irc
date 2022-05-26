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

// a penser : remove User ... + irc root me does not work with this

void Commands::leaveAllChans(User *u) // comment faire ca sur irssi ???????
{
	for (std::vector<Channel *>::const_iterator chans = u->getJoinedChannels().begin(); chans != u->getJoinedChannels().end(); chans++)
	{
		u->leaveChan(*chans); // il leave le chan, il eprforme le delete user aussi via channel
		std::string msg[] = {"PART", (*chans)->_name};
		std::vector<std::string> part_msg(msg, msg + 2);
		server_relay(u, part_msg, u);
	}
}

void createChan(Server &s, std::string chan_name, User *u, bool *joined)
{
	Channel *chan = new Channel(chan_name, u);
	s.chans.insert(std::pair<std::string, Channel *>(chan_name, chan)); // a mettre dans serveur
	*joined = true;
}

void simpleAdd(Server &s, Channel *chan, User *u, bool *joined, std::vector<std::string> *pass, size_t i)
{
	if (chan->isInChan(u))
		return;																			  // do nothing but maybe a specific error ?
	else if (chan->hasKey() && ((pass->size() < i) || !chan->isCorrectPass(pass->at(i)))) // throw une ex
		s.numeric_reply(u, ERR_BADCHANNELKEY, chan->_name, NONE, NONE);
	else if (chan->isBanned(u))
		s.numeric_reply(u, ERR_BANNEDFROMCHAN, chan->_name, NONE, NONE);
	else
	{
		u->joinChan(chan);
		chan->add_user(u);
		*joined = true;
	}
}

void Commands::join(Server &s, User *u, std::vector<std::string> cmd) // exit ou quit
{
	start;
	if (cmd.size() == 1) // un seul mot dans le vec donc juste la cmd sans cmd
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	size_t i = 0;
	bool joined = false;
	std::vector<std::string> chans = tokenize(*(cmd.begin() + 1), ',');
	std::vector<std::string> pass;

	if (cmd.size() >= 3)
		pass = tokenize(*(cmd.begin() + 2), ',');

	for (std::vector<std::string>::iterator nb_chans_it = chans.begin(); nb_chans_it != chans.end(); nb_chans_it++)
	{
		std::string chan_name = trim(chans[i]);
		joined = false;

		/* Case 0 : Channel name is not well fomatted */
		if (chan_name[0] != '#')
			s.numeric_reply(u, ERR_NOSUCHCHANNEL, chan_name, NONE, NONE);
		/* Case 1 : JOIN 0 -> leaving all chans */
		else if (*nb_chans_it == "0")
			return (leaveAllChans(u)); // return ou non  ?
		/* Case 2 : Channel does not exist */
		else if (!s.chanExists(chan_name))
			createChan(s, chan_name, u, &joined);
		/* Case 3 : Channel does exist */
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
				s.numeric_reply(u, RPL_TOPIC, chan_name, NONE, NONE);
		}
		i++;
	}
}