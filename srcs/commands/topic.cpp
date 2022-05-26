#include "Server.hpp"
#include "Answers.hpp"



void Commands::topic(Server &s, User *u, std::vector<std::string> cmd)
{
	start;
	std::string chan_name = *(cmd.begin() + 1);
	if (!s.chanExists(chan_name)) // une erreur 
		return ;
	Channel     *chan = (s.chans.find(chan_name)->second); //on recp l'instance

	if ((cmd.begin() + 2) != cmd.end())  // si on demande suejt
	{
	   std::map<std::string *, User *> chan_users = s.chans.find(chan_name)->second->getUsers();
	   server_relay(u, cmd, chan_users);
		chan->setTopic( (*(cmd.begin() + 2)).substr(1, (*(cmd.begin() + 2)).length()));
	}

	if (chan->isTopicSet() == false) // si ni topic set renvoyer ca 
		s.numeric_reply(u, "331", chan);
	else
		s.numeric_reply(u, "332", chan);
}
