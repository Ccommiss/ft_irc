#include "Server.hpp"




bool chanExists(Server &s, std::string chan_name)
{
    if (s.chans.count(chan_name) == 1)
        return (true);
    return (false);
}


//faire protection si chan existe pas ; faire function channel exist pour server 

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
        std::string txt = set_prefix(u, arg);

        std::map<std::string *, User *> chan_users = s.chans.find(chan_name)->second->getUsers();
        for (std::map<std::string *, User *>::iterator ite = chan_users.begin(); ite != chan_users.end(); ite++)
            send(ite->second->socket_descriptor, txt.c_str(), txt.length(), 0);
        chan->set_topic(*(arg.begin() + 2));
    }
    if (chan->isTopicSet() == false) // si ni topic set renvoyer ca 
        server_reply(s, u, "331", &chan_name);
    else
        server_reply(s, u, "332", &chan_name);
}
