



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
