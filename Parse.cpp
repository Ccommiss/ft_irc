#include "User.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Commands.hpp"

void nick(Server &s, User &u, std::string nick);



std::vector<std::string> split(std::string x)
{
    char delim = ' ';
    x += delim; //includes a delimiter at the end so last word is also read
    std::vector<std::string> splitted;
    std::string temp = "";
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == delim)
        {
            splitted.push_back(trim(temp)); //store words in "splitted" vector
            temp = "";
            i++;
        }
        temp += x[i];
    }
    return splitted;
}

void parse_cmd(User &user, Server &s) //envoyer users[i]
{
    std::string buff(s.buffer);
    std::vector<std::string> res = split(buff);
    for (std::vector<std::string>::iterator it = res.begin(); it != res.end(); it++)
        out ("CMD = " << *it);

    typedef void (*Cmd)(Server &s, User &user, std::string arg);
    std::map<std::string, Cmd> cmd_map;
    cmd_map.insert(std::make_pair("/nick", &nick));
    cmd_map.insert(std::make_pair("/exit", &quit_s));
    
    if (cmd_map.find(*res.begin()) != cmd_map.end())
    {
        out ("found")
        Cmd a = cmd_map.at(*res.begin());
        (*a)(s, user, *(res.begin() + 1)); // on envoie le deuxieme arg
    }

	

    
}