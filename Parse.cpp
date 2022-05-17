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

std::vector<std::string> split(std::string x)
{
    char delim = ' ';
    x += delim; // includes a delimiter at the end so last word is also read
    std::vector<std::string> splitted;
    std::string temp = "";
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == delim || x[i] == '\n')
        {
            splitted.push_back(trim(temp)); // store words in "splitted" vector
            temp = "";
            if (x[i] == '\n')
            {
                //out("hey " << x[i])
                splitted.push_back("\n");
            }
            i++;
        }
        temp += x[i];
    }
    return splitted;
}

/*
**
*/
void parse_cmd(User &user, Server &s) // envoyer users[i]
{
    std::string buff(s.buffer);
	out ("RECEIVED BUFFER = " << buff)

    typedef void (*Cmd)(Server & s, User & user, std::vector<std::string> arg);

    std::map<std::string, Cmd> cmd_map;

    cmd_map.insert(std::make_pair("NICK", &nick));
	cmd_map.insert(std::make_pair("CAP", &nick));
   // cmd_map.insert(std::make_pair("USER", &setUser));
    cmd_map.insert(std::make_pair("JOIN", &join));
    cmd_map.insert(std::make_pair("EXIT", &quit_s));

    std::vector<std::string> res = split(buff);
    std::vector<std::string>::iterator it = res.begin(); // on garde les /n

    while (it != res.end())
    {
        while (*it == "\n")
		{
            it++;
       	 	if (it == res.end())
			{
				//out ("end parse");
				return ;
			}
		}
		if (cmd_map.find(*it) != cmd_map.end())
        {
            Cmd a = cmd_map.at(*it);
			std::vector<std::string> new_res(res.begin() + std::distance(res.begin(), it), res.end());
            (*a)(s, user, new_res); // on envoie le deuxieme arg
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