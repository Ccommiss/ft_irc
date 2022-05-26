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

#define NONE		""
#define MSG_001		":Welcome to the Internet Relay Network of Clement and Claire " + user->nickname + "!" + user->name + "@" + "localhost"
#define MSG_002		":Your host is localhost, version 1.0   8-)"
#define MSG_003		":This server was created not so long time ago."
#define MSG_004		":You are very welcome. Enjoy !"
#define MSG_324 	":" + arg1 + "<mode> <mode_params>" 	/* RPL_CHANNELMODEIS */
#define MSG_331		 arg1 + " :No topic is set."
#define MSG_332		 arg1 + " :" + arg2 	/* RPL_TOPIC */
#define MSG_341		 ":" + arg1 + " " + user->nickname
#define MSG_353		 "= " + arg1 + " :" + printNames(s.chans[arg1])  // il faut le serveur ou le chan a minima                    //CHANGER EN FO Status" 
#define MSG_366		 	arg1 + " :End of NAMES list"  
#define ERR_403		  arg1 + " :No such channel" 							/* ERR_NOSUCHCHANNEL */
#define ERR_443		  arg1 + " " + arg2 + " :User already on channel"
#define ERR_461		  arg1 + " :Not enough parameters" 					 	/* ERR_NEEDMOREPARAMS */
#define ERR_462		  ":Unauthorized command (already registered)"  
#define ERR_463		  ":Your host isn't among the privileged"  												/* ERR_NOPERMFORHOST */
#define ERR_464		  ":Password incorrect" 																/* ERR_PASSWDMISMATCH */ 
#define ERR_465		  ":You are banned from this server"
#define ERR_466		  "" //ERR_YOUWILLBEBANNED  , no msg 
#define ERR_467		  arg1 + " :Channel key already set"					/* ERR_KEYSET */ 
#define ERR_471		  arg1 + " :Cannot join channel (+l)" 					/* ERR_CHANNELISFULL */
#define ERR_472		  arg1 + " :is unknown mode char to me for "  + arg2		/* ERR_UNKNOWNMODE */ 
#define ERR_473		  arg1 + " :Cannot join channel (+i) (You must be invited)" 					/* ERR_INVITEONLYCHAN */ 
#define ERR_474		  arg1 + " :Cannot join channel (+b)"  					/* ERR_BANNEDFROMCHAN */    
#define ERR_475		  arg1 + " :Cannot join channel (+k)" 					/* ERR_BADCHANNELKEY */
#define ERR_476		  arg1 + " :Bad Channel Mask" 							/* ERR_BADCHANMASK */
#define ERR_477		  arg1 + " :Channel doesn't support modes" 				/* ERR_NOCHANMODES */
#define ERR_478		  arg1 + " :Channel list is full" 				       /* ERR_BANLISTFULL */
#define ERR_482		  arg1 + " :You're not channel operator"				/* ERR_CHANOPRIVSNEEDED */

/*
**      Numeric Replies : 
**      Functions pointed in server_replies returning content of define messages 
*/

inline std::string		RPL_001 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)arg1; (void)arg2; (void)arg3; return (MSG_001); }
inline std::string		RPL_002 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_002); }
inline std::string		RPL_003 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_003); }
inline std::string		RPL_004 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_004); }
inline std::string		RPL_324 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_324); }   //RPL INVITING 
inline std::string		RPL_331 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_331); }   //RPL INVITING 
inline std::string		RPL_332 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_332); }   //RPL INVITING 
inline std::string		RPL_341 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_341); }   //RPL INVITING 
inline std::string		RPL_353 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_353); }   /* RPL_NAMREPLY */
inline std::string		RPL_366 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_366); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_403 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_403); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_443 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_443); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_461 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_461); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_462 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_462); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_463 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_463); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_464 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_464); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_465 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_465); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_466 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_466); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_467 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_467); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_471 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_471); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_472 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_472); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_473 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_473); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_474 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_474); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_475 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_475); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_476 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_476); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_477 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_477); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_478 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_478); }   /* RPL_ENDNAME  */ 
inline std::string		RPL_482 (Server &s, User *user, std::string arg1, std::string arg2, std::string arg3) { (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_482); }   /* RPL_ENDNAME  */ 





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


inline std::string     Server::choose_msg(int code, User *u, std::string arg1, std::string arg2, std::string arg3)
{
	start;
	out ("anwer code " << code)
	if (cmds.server_replies.count(code) != 1)
	{
		out ("==> Unfound server_replies");
		return ("(no reply found)");
	}
	return (*(cmds.server_replies.find(code)->second))(*this, u, arg1, arg2, arg3); // second = la function
}


inline void            Server::numeric_reply(User *u, std::string code, std::string arg1, std::string arg2, std::string arg3) // rajouter autre chose pour le channel par ex ? //numeric reply 
{
	start;
	std::string txt;
	char *ptr;
	txt.append(":");
	txt.append("localhost "); // remplacer par le define
	txt.append(code);
	txt.append(" ");
	txt.append(u->nickname); // lui qui va servir commenickname
	txt.append(" ");
	txt.append(choose_msg(std::strtol(code.c_str(), &ptr, 10), u, arg1, arg2, arg3));
	txt.append("\r\n");
	
	out(FG2("Server Reply to be sent:") << code);
	out(txt.c_str());
	if (send(u->socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
	{
		perror("SEND FAILED");
	}
}

#endif 