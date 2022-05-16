



#include "Server.hpp"
#include "User.hpp"


void nick(Server &s, User &u, std::vector<std::string> arg)
{
    out ("NICK CMD" << *arg.begin())
    u.setNickName(*(arg.begin() + 1));

    send(u.socket_descriptor, ":irc.hackerzvoice.net 001 claire :Welcome to the HackerzVoice IRC Network claire!c@62.210.34.48", 96, 0);
    send(u.socket_descriptor, ":irc.hackerzvoice.net 002 claire :Your host is irc.hackerzvoice.net, running version InspIRCd-2.0", 98, 0);
    send(u.socket_descriptor, ":irc.hackerzvoice.net 003 claire :This server was created 19:52:09 Aug 12 2013", 79, 0);
    send(u.socket_descriptor, ":irc.hackerzvoice.net 004 claire irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv", 100, 0);
}

void quit_s(Server &s, User &u, std::vector<std::string> arg) // exit ou quit
{
    out ("QUIT CMD" << *arg.begin())
    s.quit_server(u);
}