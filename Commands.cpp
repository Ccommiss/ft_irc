



#include "Server.hpp"



void nick(Server &s, User &u, std::vector<std::string> arg)
{
    out ("NICK CMD with nick = " << *(arg.begin() + 1));
    u.setNickName(*(arg.begin() + 1));

    if (u.registered == 0)
    {
        send(u.socket_descriptor, ":irc.hackerzvoice.net 001 claire :Welcome to the HackerzVoice IRC Network claire!c@62.210.34.48", 96, 0);
        send(u.socket_descriptor, ":irc.hackerzvoice.net 002 claire :Your host is irc.hackerzvoice.net, running version InspIRCd-2.0", 98, 0);
        send(u.socket_descriptor, ":irc.hackerzvoice.net 003 claire :This server was created 19:52:09 Aug 12 2013", 79, 0);
        send(u.socket_descriptor, ":irc.hackerzvoice.net 004 claire irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv", 100, 0);
        u.registered = 1;
    }

    out ("Answer sent to " << u.socket_descriptor);
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
    std::map<std::string, Channel>::const_iterator	it = s.chans.find(*(arg.begin() + 1));

	if (it != s.chans.end())
	{
		std::make_pair(true, it->second);
        s.chans[*(arg.begin() + 1)].add_user(u);
	}
    else
	{
        std::make_pair(false, nullptr);
        std::cout << "creating channel" << std::endl;
    }
}
