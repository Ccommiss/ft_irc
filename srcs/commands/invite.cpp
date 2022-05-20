
#include "Server.hpp"


/*
**  Chan exists : only members can invite
**  Chan does not exist: ok for all  
**  Invite only : only channel oeprators can say yes 
*/
void Commands::invite(Server &s, User *u, std::vector<std::string> arg)
{
    std::string chan_name = *(arg.begin() + 1);
    if (s.chans.count(chan_name) == 1) // ca existe
    {
        if (s.server_users.find(*(arg.begin()+2))
            s.chans[chan_name].add_users(arg.begin() + 2) // checker si la eprsonne exist 
    }

}