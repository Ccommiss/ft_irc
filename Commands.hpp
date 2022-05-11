#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "Server.hpp"
# include "User.hpp"

std::string trim(const std::string &s);
void quit_s(Server &s, User &u, std::string nick); // exit ou quit
std::string ltrim(const std::string &s);


#endif