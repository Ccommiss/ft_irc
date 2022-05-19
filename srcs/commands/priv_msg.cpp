#include "Server.hpp"


/*
**  Command: PRIVMSG
**  @param arg : <msgtarget> <text to be sent>
**  Triggered by /msg (login)
** or talking in a chan 
*/
void            Commands::priv_msg(Server &s, User &u, std::vector<std::string> arg)
{
    start;
    std::string arg_1 = *(arg.begin() + 1);
    out ("Sending priv msg to " << arg_1)
    // Arg : soit personne, soit channe ?
    if (arg_1.compare(0, 1, "#", 0 , 1) == 0)
    {
        out ("Sending to channel" << arg_1)
        for (std::map<std::string, User>::iterator it = s.chans[arg_1].get_users().begin(); it != s.chans[arg_1].get_users().begin(); it++)
        {
            out ("USERS" << it->first);
        }
    }
    else 
    {
        out ("Sending to people " << arg_1);
        std::map<const std::string &, const User &>::iterator it = s.server_users.begin();
         out ("USERS " << it->first);
        while (it != s.server_users.end())
        {
            if (arg_1 == it->second.nickname)
            {
                //out ("found user !" << s.server_users.at(arg_1).socket_descriptor);
                std::string txt = set_prefix(&u, arg);
                send (it->second.socket_descriptor, txt.c_str(), txt.length(), 0);
                return ;
            }
            it++;
        }
        
        out ("unfound user" << arg_1)
    }
}