#include "Server.hpp"
#include "Answers.hpp"

void Commands::topic(Server &s, User *u, std::vector<std::string> cmd)
{
	start;
	std::string chan_name = *(cmd.begin() + 1);
	if (!s.chanExists(chan_name)) // une erreur
		return;
	Channel *chan = (s.chans[chan_name]); // on recp l'instance
	if (!chan->isInChan(u))
		return (s.numeric_reply(u, ERR_NOTONCHANNEL, chan_name, "", ""));
	if ((cmd.begin() + 2) != cmd.end()) // si on demande a changer le sujet
	{
		std::map<std::string *, User *> chan_users = chan->getUsers();
		server_relay(u, cmd, chan_users);
		chan->setTopic(implodeMessage((cmd.begin() + 2), cmd.end()).erase(0,1));
	}
	if (chan->isTopicSet() == false) // si ni topic set renvoyer ca
		s.numeric_reply(u, "331", chan->_name, NONE, NONE);
	else
		s.numeric_reply(u, "332", chan->_name, chan->_topic, NONE);
}
