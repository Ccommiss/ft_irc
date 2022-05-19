#include "Server.hpp"


void Commands::nick(Server &s, User &u, std::vector<std::string> arg)
{
    start;
    out ("salut");
    out (u.nickname);
    if (u.registered == 0)
        out (BOLD("Setting nickname to ") << *(arg.begin() + 1));
        
    if (u.registered == 1)
    {
        std::string txt = set_prefix(&u, arg); // password for nick
        out (BOLD("Changing nick name from ") << u.nickname << " to " << *(arg.begin() + 1));
        std::map<const std::string &, const User &>::iterator it = s.server_users.begin();
        while (it !=  s.server_users.end())
        {
            if (send(it->second.socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
                 perror ("Fail send");
            it++;
        }
    }
    u.setNickName(*(arg.begin() + 1));
}