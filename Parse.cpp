#include "User.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Commands.hpp"




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


/*
**  
*/
void parse_cmd(User &user, Server &s) //envoyer users[i]
{
    std::string buff(s.buffer);
    std::vector<std::string> res = split(buff);

    typedef void (*Cmd)(Server &s, User &user, std::vector<std::string> arg);

    std::map<std::string, Cmd> cmd_map;
    cmd_map.insert(std::make_pair("CAP", &nick));
    cmd_map.insert(std::make_pair("NICK", &nick));
    cmd_map.insert(std::make_pair("/exit", &quit_s));
    
    if (cmd_map.find(*res.begin()) != cmd_map.end())
    {
        Cmd a = cmd_map.at(*res.begin());
        (*a)(s, user, res); // on envoie le deuxieme arg
    } // pour les messages slt  ; page accueil on peut que faire des cmd !!! 
}