#include "Server.hpp"



void Commands::join(Server &s, User *u, std::vector<std::string> arg) // exit ou quit
{
	start;
	std::string chan_name = *(arg.begin() + 1);
	std::map<std::string, Channel *>::const_iterator it = s.chans.find(chan_name);

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
	}
   
	/* Server informing all chan users */
	std::map<std::string *, User *> chan_users = s.chans.find(chan_name)->second->getUsers();
	server_relay(u, arg, chan_users);
	/* RPL 331 */
	
	numeric_reply(s, u, "353", s.chans[chan_name]);
	numeric_reply(s, u, "366", s.chans[chan_name]);
	if (s.chans[chan_name]->isTopicSet() == true)
		numeric_reply(s, u, "332",  s.chans[chan_name]);
}