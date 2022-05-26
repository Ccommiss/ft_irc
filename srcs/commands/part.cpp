
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

// un seul channel

void Commands::part(Server &s, User *u, std::vector<std::string> cmd)
{
	start;

	if (cmd.size() == 1) // un seul mot dans le vec donc juste la cmd sans cmd
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, &(*cmd.begin())));

	std::vector<std::string> args(cmd.begin() + 1, cmd.end());
	std::string new_args = vecToString(args); // only args
	std::vector<std::string> out = tokenize(new_args, ',');


	for (std::vector<std::string>::iterator nb_chans_it = out.begin(); nb_chans_it != out.end(); nb_chans_it++)
	{
		out ("CURR FOUND" << *nb_chans_it)
		std::string chan_name 									= trim(*nb_chans_it); 
		std::map<std::string, Channel *>::const_iterator it 	= s.chans.find(chan_name);
		out ("FOUND :" << it->first)
		s.printChans();
		if (it == s.chans.end())
			return (s.numeric_reply(u, ERR_NOSUCHCHANNEL, &(chan_name)));
		if (it != s.chans.end())
		{
			std::map<std::string *, User *> chan_users = s.chans[chan_name]->getUsers();
			std::cout << "removing user " << u->getName() << std::endl;
			s.chans[chan_name]->remove_user(u);

			
			std::vector<std::string> part_chan_msg;
			part_chan_msg.push_back(*(cmd.begin())); // "PART "
			part_chan_msg.push_back(chan_name);
			server_relay(u, part_chan_msg, chan_users);
		}
	}
}
