
#include "Server.hpp"


/*
**   Command: INVITE
 **  Parameters: <nickname> <channel>
**  Chan exists : only members can invite
**  Chan does not exist: ok for all  
**  Invite only : only channel oeprators can say yes 
*/
void Commands::invite(Server &s, User *u, std::vector<std::string> arg)
{
    start;
    std::string chan_name = (*(arg.begin() + 2));
    out ("Chan name :" << chan_name)

    if (s.chans.count(chan_name) == 1) // ca existe
    {
        out ("existing channel")

        std::map<const std::string *, const User *>::iterator it = s.server_users.begin();
         out ("USERS " << it->first);
        while (it != s.server_users.end())
        {
            if (*(arg.begin() + 1) == it->second->nickname)
            {
                out ("found user !");
                std::string txt = set_prefix(u, arg);
                User *to_add = const_cast<User *>(s.server_users[&(it->second->nickname)]); // car mapped type est const 
                s.chans[chan_name]->add_user(to_add); // checker si la eprsonne exist 
                send (it->second->socket_descriptor, txt.c_str(), txt.length(), 0);
                server_reply(s, u, "341", &chan_name);
                return ;
            }
            it++;
        }
            
    }
    else 
        out ("Unfound channel")
}