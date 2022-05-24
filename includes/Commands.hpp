#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "User.hpp"
#include "Debug.hpp"

#include <map>

class Server;


class Commands
{

	public:
		Commands();
		// Commands(std::string name, User & creator);
		// Commands( Commands const & src );
		~Commands();

		void parse_cmd		(User *user, Server &s);

		void quit_s			(Server &s, User *u, std::vector<std::string> nick); // exit ou quit
		void setUser		(Server &s, User *u, std::vector<std::string> arg);
		void join			(Server &s, User *u, std::vector<std::string> arg);
		void priv_msg		(Server &s, User *u, std::vector<std::string> arg);
		void nick			(Server &s, User *u, std::vector<std::string> arg);
		void invite			(Server &s, User *u, std::vector<std::string> arg);
		void part			(Server &s, User *u, std::vector<std::string> arg) ; // par d'un chan 
		void topic			(Server &s, User *u, std::vector<std::string> arg);



		typedef void (Commands::*Cmd)(Server &s, User *user, std::vector<std::string> arg);
		std::map<std::string, Cmd> 		cmd_map;

		typedef std::string (*Rep)(User *user, void *arg);
		std::map<int, Rep> 	server_replies;
};
#include "Server.hpp"

/*
**  Utils
*/
std::string trim(const std::string &s);
std::string ltrim(const std::string &s);

/*
**  Answers
*/
void 			numeric_reply(Server &s, User *u, std::string code, void *arg);

// template <typename T>
// std::string 	server_relay(const User *u, std::vector<std::string> cmd, T users_list);
// template <>
// std::string 	server_relay(const User *u, std::vector<std::string> cmd, User *receiver);



template <typename T> // un container 
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


#endif