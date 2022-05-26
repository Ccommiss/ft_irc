#include "User.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Commands.hpp"

void print(std::vector<std::string> vec)
{

	std::vector<std::string>::iterator it;
	for (it = vec.begin(); it != vec.end(); it++)
		out("PARSE CMD = " << *it)
}

/*
**  split
**  @brief parses the commands as received for example : NICK <newname>
**  @param x the string to be parsed 
**  @returns a vector of string containeing the totality of the given string
*/
std::vector<std::string> split(std::string x)
{
	char delim = ' ';
	x += delim; // includes a delimiter at the end so last word is also read
	std::vector<std::string> splitted;
	std::string temp = "";
	for (unsigned long i = 0; i < x.length(); i++)
	{
		if (x[i] == delim || x[i] == '\n')
		{
			splitted.push_back(trim(temp)); // store words in "splitted" vector
			temp = "";
			if (x[i] == '\n')
			{
				splitted.push_back("\n");
			}
			i++;
		}
		temp += x[i];
	}
	return splitted;
}

/*
**  parse_cmd
**  @brief parses the commands as received for example : NICK <newname>
**  @param user the user (client) that initiated the request
**  @param s the server instance
**  @returns none
*/
void Commands::parse_cmd(User *user, Server &s) // envoyer users[i]
{
	start;
	std::string buff(s.buffer);
	std::vector<std::string> res = split(buff);
	std::vector<std::string>::iterator it = res.begin(); // on garde les /n

	out ("Buffer : " << s.buffer);

	while (it != res.end())
	{
		while (*it == "\n")
		{
			it++;
	   	 	if (it == res.end())
			{
				return ;
			}
		}
		if (cmd_map.find(*it) != cmd_map.end())
		{
			Commands::Cmd a = cmd_map.at(*it); //  a proteger try/catch 
			std::vector<std::string> new_res(res.begin() + std::distance(res.begin(), it), res.end());
			(this->*a)(s, user, new_res); // on envoie le deuxieme cmd
		}                       // pour les messages slt  ; page accueil on peut que faire des cmd !!!
		while (it != res.end())
		{
			if (*it == "\n")
				break;
			it++;
		}
		if (it == res.end())
			return ;
	}
}