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
	for (std::vector< Channel *>::const_iterator chans = u->getJoinedChannels().begin(); chans != u->getJoinedChannels().end(); chans++)
	{
		u->leaveChan(*chans); // il leave le chan, il eprforme le delete user aussi via channel
		std::vector<std::string> part_msg;
		part_msg.push_back("PART");
		part_msg.push_back((*chans)->_name);
		server_relay(u, part_msg, u);
	}
}


void Commands::join(Server &s, User *u, std::vector<std::string> arg) // exit ou quit
{
	start;
	if (arg.size() == 1) // un seul mot dans le vec donc juste la cmd sans arg
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, &(*arg.begin())));

	std::vector<std::string> rest(arg.begin() +1, arg.end());
	std::string new_args = vecToString(rest); // faut recupere tout le reste de la string
	for (std::vector<std::string>::iterator d = arg.begin(); d != arg.end(); d++)
			out ("ARGS DE BASE " << *d);
	std::vector<std::string> out; // si plusieurs chans JOIN #lol,#test,#mdr,#flute
	tokenize(new_args, ',', out);

	for (std::vector<std::string>::iterator nb_chans_it = out.begin(); nb_chans_it != out.end(); nb_chans_it++)
	{
		std::vector<std::string> args; 
		tokenize(*nb_chans_it, ' ', args); // onredevise si jamais y a des mdp genre #lol motdepass 

		for (std::vector<std::string>::iterator d = args.begin(); d != args.end(); d++)
			out ("ARGS " << *d);
		std::string chan_name = args[0];
		if (chan_name[0] != '#')
			return (s.numeric_reply(u, ERR_NOSUCHCHANNEL, &chan_name));
		if (*nb_chans_it == "0") // leave all chans que faire si JOIN 0 jakfjskfj derreire ? 
		{
			leaveAllChans(u); // return ou non  ? 
		}
		std::map<std::string, Channel *>::const_iterator it = s.chans.find(chan_name);
		if (it == s.chans.end()) // le chan existe pas 
		{
			Channel *chan = new Channel(chan_name, u);
			s.chans.insert(std::pair<std::string, Channel *>(chan_name, chan)); // a mettre dans serveur
		}
		else // le chan existe 
		{	
			if (s.chans[chan_name]->hasKey() && ( (args.size() < 2) || !s.chans[chan_name]->isCorrectPass(args[1])))
				return (s.numeric_reply(u, ERR_BADCHANNELKEY, s.chans[chan_name]));
			if (s.chans[chan_name]->isBanned(u))
				return (s.numeric_reply(u, ERR_BANNEDFROMCHAN, s.chans[chan_name]));
			s.chans[chan_name]->add_user(u);
		}

		/* Server informing all chan users */
		std::map<std::string *, User *> chan_users = s.chans[chan_name]->getUsers();
		std::vector<std::string> join_chan_msg;
		join_chan_msg.push_back(*(arg.begin())); // "JOIN "
		join_chan_msg.push_back(chan_name);

		server_relay(u, join_chan_msg, chan_users);
		s.numeric_reply(u, RPL_NAMREPLY, s.chans[chan_name]);
		s.numeric_reply(u, RPL_ENDOFNAMES, s.chans[chan_name]);
		if (s.chans[chan_name]->isTopicSet() == true)
			s.numeric_reply(u, RPL_TOPIC, s.chans[chan_name]);
	}
}