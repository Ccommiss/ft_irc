
#include "Commands.hpp"
#include "Debug.hpp"


#define MSG_001 "Welcome to the Internet Relay Network " + user->nickname + "!" + user->name + "@" + "localhost"
#define MSG_002 "DOS Your host is irc.hackerzvoice.net, running version InspIRCd-2.0"
#define MSG_003 "TRES This server was created 19:52:09 Aug 12 2013"
#define MSG_004 "FINALMENTE irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv"
// #define MSG_005
// #define MSG_006


std::string    RPL_001(User *user) { return (MSG_001); }
std::string    RPL_002(User *user) { (void)user; return (MSG_002); }
std::string    RPL_003(User *user) { (void)user; return (MSG_003); }
std::string    RPL_004(User *user) { (void)user; return (MSG_004); }


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Commands::Commands()
{
    start;
    cmd_map.insert(std::make_pair("NICK", &Commands::nick));
	cmd_map.insert(std::make_pair("CAP",  &Commands::nick));
    cmd_map.insert(std::make_pair("USER",  &Commands::setUser));
    cmd_map.insert(std::make_pair("JOIN",  &Commands::join));
    cmd_map.insert(std::make_pair("PRIVMSG",  &Commands::priv_msg));
    cmd_map.insert(std::make_pair("EXIT",  &Commands::quit_s));
    cmd_map.insert(std::make_pair("INVITE",  &Commands::invite));


    // Now storing replies ; idee, ptr sur func genre Answer::&RPL_001   avec RPL 001 qui prendra un user
    server_replies.insert(std::make_pair(1, &RPL_001));
    server_replies.insert(std::make_pair(2, &RPL_002));
    server_replies.insert(std::make_pair(3, &RPL_003));
    server_replies.insert(std::make_pair(4, &RPL_004));
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Commands::~Commands()
{

}


