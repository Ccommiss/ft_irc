
#include "Commands.hpp"
#include "Debug.hpp"
#include "Channel.hpp"


std::string        printNames(Channel *chan)
{
     std::string names;
    for (std::map<std::string *, User *>::iterator it = chan->getUsers().begin() ; it != chan->getUsers().end(); it++)
    {
        //if is op... @, sinon +
        names.append("@");
        names.append(*it->first);
        names.append(" ");
    }
    return names;
}

#define MSG_001 ":Welcome to the Internet Relay Network " + user->nickname + "!" + user->name + "@" + "localhost"
#define MSG_002 ":DOS Your host is irc.hackerzvoice.net, running version InspIRCd-2.0"
#define MSG_003 ":TRES This server was created 19:52:09 Aug 12 2013"
#define MSG_004 ":FINALMENTE irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv"
#define MSG_331  *(static_cast<std::string*>(arg)) + " :No topic is set."
#define MSG_332  (static_cast<Channel *>(arg))->_name + " :" + (static_cast<Channel *>(arg))->_topic // // +  // TOPIC a deriver de arg qui est sera instance du channel
#define MSG_341  ":" + *(static_cast<std::string*>(arg)) + " " + user->nickname
#define MSG_353  "= " + (static_cast<Channel *>(arg))->_name + " :" + printNames((static_cast<Channel *>(arg)))                      /* RPL_NAMREPLY */ //CHANGER EN FO Status" 
#define MSG_366  (static_cast<Channel *>(arg))->_name + " :End of NAMES list"                             /* RPL_ENDNAME */ 

// 353    RPL_NAMREPLY
//               "( "=" / "*" / "@" ) <channel>
//                :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )
//          - "@" is used for secret channels, "*" for private
//            channels, and "=" for others (public channels).

// #define MSG_006


std::string    RPL_001(User *user, void *arg) { (void)arg; return (MSG_001); }
std::string    RPL_002(User *user, void *arg) { (void)user; (void)arg; return (MSG_002); }
std::string    RPL_003(User *user, void *arg) { (void)user; (void)arg; return (MSG_003); }
std::string    RPL_004(User *user, void *arg) { (void)user; (void)arg; return (MSG_004); }
std::string    RPL_331 (User *user, void *arg) { (void)user; (void)arg; return (MSG_331); }   //RPL INVITING 
std::string    RPL_332 (User *user, void *arg) { (void)user; (void)arg; return (MSG_332); }   //RPL INVITING 
std::string    RPL_341 (User *user, void *arg) { (void)user; (void)arg; return (MSG_341); }   //RPL INVITING 
std::string    RPL_353 (User *user, void *arg) { (void)user; (void)arg; return (MSG_353); }   //RPL INVITING 
std::string    RPL_366 (User *user, void *arg) { (void)user; (void)arg; return (MSG_366); }   //RPL INVITING 


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
    cmd_map.insert(std::make_pair("PART",  &Commands::part));
    cmd_map.insert(std::make_pair("TOPIC",  &Commands::topic));
    



    // Now storing replies ; idee, ptr sur func genre Answer::&RPL_001   avec RPL 001 qui prendra un user
    server_replies.insert(std::make_pair(1, &RPL_001));
    server_replies.insert(std::make_pair(2, &RPL_002));
    server_replies.insert(std::make_pair(3, &RPL_003));
    server_replies.insert(std::make_pair(4, &RPL_004));
    server_replies.insert(std::make_pair(331, &RPL_331)); // RPL TOPIC
    server_replies.insert(std::make_pair(332, &RPL_332)); // RPL TOPIC
    server_replies.insert(std::make_pair(341, &RPL_341));
    server_replies.insert(std::make_pair(353, &RPL_353));
    server_replies.insert(std::make_pair(366, &RPL_366));
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Commands::~Commands()
{

}


