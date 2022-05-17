#include "Server.hpp"
#include "User.hpp"

#define MSG_001 "Welcome to the HackerzVoice IRC Network louveet!louveet@127.0.0.1\n"
#define MSG_002 "Your host is irc.hackerzvoice.net, running version InspIRCd-2.0\n"
#define MSG_003 "This server was created 19:52:09 Aug 12 2013\n"
#define MSG_004 "irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv\n"
// #define MSG_005
// #define MSG_006

std::string choose_msg(int code)
{

    std::map<int, std::string> lol;
    lol.insert(std::make_pair(1, MSG_001));
    lol.insert(std::make_pair(2, MSG_002));
    lol.insert(std::make_pair(3, MSG_003));
    lol.insert(std::make_pair(4, MSG_004));
    out(lol.find(code)->second);
    return (lol.find(code)->second);
}

void  server_reply(User *u, std::string code)
{
    std::string txt;
    char *ptr;
    txt.append(":");
    txt.append("localhost "); // remplacer par le define
    txt.append(code);
    txt.append(" ");
    txt.append(u->nickname); // lui qui va servir commenickname 
    txt.append(" :");
    txt.append(choose_msg(std::strtol(code.c_str(), &ptr, 10)));
   out (txt);

    send(u->socket_descriptor, txt.c_str(), txt.length(), 0);
    // send(dest, ":localhost 001 louveet :Welcome to the HackerzVoice IRC Network louveet!louveet@127.0.0.1\n", 91, 0);
    //  send(u.socket_descriptor, ":localhost 002 louveet :Your host is irc.hackerzvoice.net, running version InspIRCd-2.0\n", 89, 0);
    // send(u.socket_descriptor, ":localhost 003 louveet :This server was created 19:52:09 Aug 12 2013\n", 70, 0);
    // send(u.socket_descriptor, ":localhost 004 louveet irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv\n", 118, 0);
}