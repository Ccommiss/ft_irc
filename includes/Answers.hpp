#ifndef ANSWERS_HPP
# define ANSWERS_HPP 

#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include "Debug.hpp"


/*
**	@file  answers.hpp
**	@brief manage anwers 
*/


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