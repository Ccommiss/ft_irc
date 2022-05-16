#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "Server.hpp"
# include "User.hpp"

std::string trim(const std::string &s);
void nick(Server &s, User &u, std::vector<std::string> arg);

void quit_s(Server &s, User &u, std::vector<std::string> nick); // exit ou quit
std::string ltrim(const std::string &s);
void parse_cmd(User &user, Server &s);



#endif