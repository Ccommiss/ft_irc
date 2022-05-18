#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "Server.hpp"
# include "User.hpp"

class Server;

/*
**  Utils  
*/
std::string     trim(const std::string &s);
std::string     ltrim(const std::string &s);
void            nick(Server &s, User &u, std::vector<std::string> arg);


/*
**  Parsing  
*/

void            parse_cmd(User &user, Server &s); 


/*
**  Commands  
*/
void            quit_s(Server &s, User &u, std::vector<std::string> nick); // exit ou quit
void            setUser(Server &s, User &u, std::vector<std::string> arg);
void            join(Server &s, User &u, std::vector<std::string> arg);
void            priv_msg(Server &s, User &u, std::vector<std::string> arg);


/*
**  Answers  
*/
void            server_reply(User *u, std::string code);
std::string     set_prefix(User *u, std::vector<std::string> cmd);


#endif