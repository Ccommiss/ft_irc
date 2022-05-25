#ifndef ANSWERS_HPP
# define ANSWERS_HPP 

/*
**	@file  answers.hpp
**	@brief manage anwers 
*/


#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include "Debug.hpp"



#include "numeric_rpl.hpp"


/*
**  Define messages 
*/

#define MSG_001		":Welcome to the Internet Relay Network of Clement and Claire " + user->nickname + "!" + user->name + "@" + "localhost"
#define MSG_002		":Your host is localhost, version 1.0   8-)"
#define MSG_003		":This server was created not so long time ago."
#define MSG_004		":You are very welcome. Enjoy !"
#define MSG_331		 *(static_cast<std::string*>(arg)) + " :No topic is set."
#define MSG_332		 (static_cast<Channel *>(arg))->_name + " :" + (static_cast<Channel *>(arg))->_topic  	/* RPL_TOPIC */
#define MSG_341		 ":" + *(static_cast<std::string*>(arg)) + " " + user->nickname
#define MSG_353		 "= " + (static_cast<Channel *>(arg))->_name + " :" + printNames((static_cast<Channel *>(arg)))                       //CHANGER EN FO Status" 
#define MSG_366		 (static_cast<Channel *>(arg))->_name + " :End of NAMES list"  
#define ERR_403			*(static_cast<std::string*>(arg)) + " :No such channel" 							/* ERR_NOSUCHCHANNEL */
#define ERR_461		  *(static_cast<std::string*>(arg)) + " :Not enough parameters" 					 	/* ERR_NEEDMOREPARAMS */
#define ERR_462		  ":Unauthorized command (already registered)"  
#define ERR_463		  ":Your host isn't among the privileged"  												/* ERR_NOPERMFORHOST */
#define ERR_464		  ":Password incorrect" 																/* ERR_PASSWDMISMATCH */ 
#define ERR_465		  ":You are banned from this server"
#define ERR_466		  "" //ERR_YOUWILLBEBANNED  , no msg 
#define ERR_467		  (static_cast<Channel *>(arg))->_name + " :Channel key already set"					/* ERR_KEYSET */ 
#define ERR_471		  (static_cast<Channel *>(arg))->_name + " :Cannot join channel (+l)" 					/* ERR_CHANNELISFULL */
#define ERR_472		  "<char> :is unknown mode char to me for <channel>" 									/* ERR_UNKNOWNMODE */ 
#define ERR_473		  (static_cast<Channel *>(arg))->_name + " :Cannot join channel (+i)" 					/* ERR_INVITEONLYCHAN */ 
#define ERR_474		  (static_cast<Channel *>(arg))->_name + " :Cannot join channel (+b)"  					/* ERR_BANNEDFROMCHAN */    
#define ERR_475		  (static_cast<Channel *>(arg))->_name + " :Cannot join channel (+k)" 					/* ERR_BADCHANNELKEY */
#define ERR_476		  (static_cast<Channel *>(arg))->_name + " :Bad Channel Mask" 							/* ERR_BADCHANMASK */
#define ERR_477		  (static_cast<Channel *>(arg))->_name + " :Channel doesn't support modes" 				/* ERR_NOCHANMODES */
#define ERR_478		  (static_cast<Channel *>(arg))->_name + " <char> :Channel list is full" 				/* ERR_BANLISTFULL */
	  
/*
**      Numeric Replies : 
**      Functions pointed in server_replies returning content of define messages 
*/

inline std::string		RPL_001 (User *user, void *arg) { (void)arg; return (MSG_001); }
inline std::string		RPL_002 (User *user, void *arg) { (void)user; (void)arg; return (MSG_002); }
inline std::string		RPL_003 (User *user, void *arg) { (void)user; (void)arg; return (MSG_003); }
inline std::string		RPL_004 (User *user, void *arg) { (void)user; (void)arg; return (MSG_004); }
inline std::string		RPL_331 (User *user, void *arg) { (void)user; (void)arg; return (MSG_331); }   //RPL INVITING 
inline std::string		RPL_332 (User *user, void *arg) { (void)user; (void)arg; return (MSG_332); }   //RPL INVITING 
inline std::string		RPL_341 (User *user, void *arg) { (void)user; (void)arg; return (MSG_341); }   //RPL INVITING 
inline std::string		RPL_353 (User *user, void *arg) { (void)user; (void)arg; return (MSG_353); }   /* RPL_NAMREPLY */
inline std::string		RPL_366 (User *user, void *arg) { (void)user; (void)arg; return (MSG_366); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_403 (User *user, void *arg) { (void)user; (void)arg; return (ERR_403); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_461 (User *user, void *arg) { (void)user; (void)arg; return (ERR_461); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_462 (User *user, void *arg) { (void)user; (void)arg; return (ERR_462); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_463 (User *user, void *arg) { (void)user; (void)arg; return (ERR_463); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_464 (User *user, void *arg) { (void)user; (void)arg; return (ERR_464); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_465 (User *user, void *arg) { (void)user; (void)arg; return (ERR_465); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_466 (User *user, void *arg) { (void)user; (void)arg; return (ERR_466); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_467 (User *user, void *arg) { (void)user; (void)arg; return (ERR_467); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_471 (User *user, void *arg) { (void)user; (void)arg; return (ERR_471); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_472 (User *user, void *arg) { (void)user; (void)arg; return (ERR_472); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_473 (User *user, void *arg) { (void)user; (void)arg; return (ERR_473); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_474 (User *user, void *arg) { (void)user; (void)arg; return (ERR_474); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_475 (User *user, void *arg) { (void)user; (void)arg; return (ERR_475); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_476 (User *user, void *arg) { (void)user; (void)arg; return (ERR_476); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_477 (User *user, void *arg) { (void)user; (void)arg; return (ERR_477); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_478 (User *user, void *arg) { (void)user; (void)arg; return (ERR_478); }   /* RPL_ENDNAME  */ 






/*
**  Server_relay
**  @brief non numeric replies. Just relay in course command to 
**  @tparam T : others users, specified in user_list (corresponding to server_users or just a specific
**  channel users) 
**  OR
**  @tparam <> : total specialization for User *
**  Their shape is : :<nick>!<user>@<host> <cmd> [<param>] :<msg>
*/
template <typename T> 
inline std::string server_relay(const User *u, std::vector<std::string> cmd, T user_list) 
{
	std::string txt;
	txt.append(":");
	txt.append(u->nickname);
	txt.append("!");
	txt.append(u->name); //username
	txt.append("@localhost ");
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end() && *it != "\n"; it++)
		txt.append(*it + " "); // on met touts les commandes dans le prefixe 
	txt = trim(txt);
	 txt.append("\r\n");
	out(FG2("Server Reply to be sent: (server relay)"));
	out (txt)
	for (typename T::iterator ite = user_list.begin(); ite != user_list.end(); ite++)
	   send(ite->second->socket_descriptor, txt.c_str(), txt.length(), 0); // send to all 
	return ((txt));
}

template <> // specialisation si un seul envoi a effectuer
inline std::string server_relay(const User *u, std::vector<std::string> cmd, User *receiver) 
{
	std::string txt;
	txt.append(":");
	txt.append(u->nickname);
	txt.append("!");
	txt.append(u->name); //username
	txt.append("@localhost ");
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end() && *it != "\n"; it++)
		txt.append(*it + " "); // on met touts les commandes dans le prefixe 
	txt = trim(txt);
	 txt.append("\r\n");
	out(FG2("Server Reply to be sent: (server relay)"));
	out (txt)
	send(receiver->socket_descriptor, txt.c_str(), txt.length(), 0);
	return ((txt));
}

/*
**  Numeric Replies 
**  @brief  numeric replies sent back to client after a request
**
**  Their shape is : :<host> <3digits> <nickname> : [...] (depends on the answer)
*/

template <typename T>
std::string     Server::choose_msg(int code, User *u, T *arg)
{
	if (cmds.server_replies.count(code) != 1)
	{
		out ("==> Unfound server_replies");
		return ("(no reply found)");
	}
	return (*(cmds.server_replies.find(code)->second))(u, arg); // second = la function
}

template <typename T>
void            Server::numeric_reply(User *u, std::string code, T *arg) // rajouter autre chose pour le channel par ex ? //numeric reply 
{
	std::string txt;
	char *ptr;
	txt.append(":");
	txt.append("localhost "); // remplacer par le define
	txt.append(code);
	txt.append(" ");
	txt.append(u->nickname); // lui qui va servir commenickname
	txt.append(" ");
	txt.append(choose_msg(std::strtol(code.c_str(), &ptr, 10), u, arg));
	txt.append("\r\n");
	
	out(FG2("Server Reply to be sent:") << code);
	out(txt.c_str());
	if (send(u->socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
	{
		perror("SEND FAILED");
	}
}

#endif 