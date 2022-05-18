



#include "Server.hpp"



void nick(Server &s, User &u, std::vector<std::string> arg)
{
    out ("NICK CMD with nick = " << *(arg.begin() + 1));
    u.setNickName(*(arg.begin() + 1));

    if (u.registered == 0)
    {
        send(u.socket_descriptor, ":localhost 001 louveet :Welcome to the HackerzVoice IRC Network louveet!louveet@127.0.0.1\n", 91, 0);
        send(u.socket_descriptor, ":localhost 002 louveet :Your host is irc.hackerzvoice.net, running version InspIRCd-2.0\n", 89, 0);
        send(u.socket_descriptor, ":localhost 003 louveet :This server was created 19:52:09 Aug 12 2013\n", 70, 0);
        send(u.socket_descriptor, ":localhost 004 louveet irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv\n", 118, 0);
        u.registered = 1;
            out ("Answer sent to " << u.socket_descriptor);

    }

}

void setUser(Server &s, User &u, std::vector<std::string> arg)
{
    out ("Setting name to : " << *(arg.begin() + 1));
    u.setName(*(arg.begin() + 1));
  
}


void quit_s(Server &s, User &u, std::vector<std::string> arg) // exit ou quit
{
    out ("QUIT CMD" << *arg.begin())
    s.quit_server(u);
}

void join(Server &s, User &u, std::vector<std::string> arg) // exit ou quit
{

    out ("JOIN THIS CHANN CMD" << *(arg.begin() + 1))
    std::string chan_name = *(arg.begin() + 1);
    std::map<std::string, Channel>::const_iterator	it = s.chans.find(chan_name);
    if ( it == s.chans.end())
    {    
        Channel chan(chan_name, u);
        s.chans.insert(std::pair<std::string, Channel>(chan_name, chan));
    }
    else
    {
        std::cout << "adding_user " << u.getName() << std::endl;
        s.chans[chan_name].add_user(chan_name, u);    
    }
    std::map<std::string, Channel>::const_iterator titi;
    // for (titi = s.chans.begin(); titi != s.chans.end(); titi++)
    // {
    //     std::cout << titi->first << std::endl;
    //     for (std::map<std::string, User>::const_iterator it = s.chans[titi->second].get_users()
    // }

}
