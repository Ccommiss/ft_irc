#include "Server.hpp"




bool chanExists(Server &s, std::string chan_name) // a mettre ailleurs 
{
	if (s.chans.count(chan_name) == 1)
		return (true);
	return (false);
}


void Commands::topic(Server &s, User *u, std::vector<std::string> arg)
{
	(void)arg;
	start;
	std::string chan_name = *(arg.begin() + 1);
	if (!chanExists(s, chan_name))
		return ;
	Channel     *chan = (s.chans.find(chan_name)->second); //on recp l'instance 
	if ((arg.begin() + 2) != arg.end())  // si on demande suejt
	{
	   std::map<std::string *, User *> chan_users = s.chans.find(chan_name)->second->getUsers();
	   server_relay(u, arg, chan_users);
		chan->setTopic( (*(arg.begin() + 2)).substr(1, (*(arg.begin() + 2)).length()));
	}

	if (chan->isTopicSet() == false) // si ni topic set renvoyer ca 
		numeric_reply(s, u, "331", chan);
	else
		numeric_reply(s, u, "332", chan);
}
