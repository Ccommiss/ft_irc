#include "Server.hpp"

void Commands::join(Server &s, User *u, std::vector<std::string> arg) // exit ou quit
{
    start;
    std::string chan_name = *(arg.begin() + 1);
    std::map<std::string, Channel *>::const_iterator it = s.chans.find(chan_name);
    std::string txt = set_prefix(u, arg); // preparing server reply

    if (it == s.chans.end())
    {
        out("Creating new channel");
        Channel *chan = new Channel(chan_name, u);
        s.chans.insert(std::pair<std::string, Channel *>(chan_name, chan));
        send(u->socket_descriptor, txt.c_str(), txt.length(), 0);
    }
    else
    {
        std::cout << "adding_user " << u->getName() << std::endl;
        s.chans[chan_name]->add_user(u);
    }
   
    /* Server informing all chan users */
    std::map<std::string *, User *> chan_users = s.chans.find(chan_name)->second->getUsers();
    for (std::map<std::string *, User *>::iterator ite = chan_users.begin(); ite != chan_users.end(); ite++)
        send(ite->second->socket_descriptor, txt.c_str(), txt.length(), 0); // send to all 
    /* RPL 331 */
    
    server_reply(s, u, "353", s.chans[chan_name]);
    server_reply(s, u, "366", s.chans[chan_name]);
    if (s.chans[chan_name]->isTopicSet() == true)
        server_reply(s, u, "332", &chan_name);
}