#include "Server.hpp"



void Commands::join(Server &s, User &u, std::vector<std::string> arg) // exit ou quit
{
    start;
    std::string chan_name = *(arg.begin() + 1);
    std::map<std::string, Channel>::const_iterator	it = s.chans.find(chan_name);
    if ( it == s.chans.end())
    {    
        Channel chan(chan_name, u);
        s.chans.insert(std::pair<std::string, Channel>(chan_name, chan));
    }
    else
    {
        std::cout << "adding_user " << u.getName() << std::endl;
        s.chans[chan_name].add_user(chan_name, u);    
    }
    std::map<std::string, Channel>::const_iterator titi;
    // for (titi = s.chans.begin(); titi != s.chans.end(); titi++)
    // {
    //     std::cout << titi->first << std::endl;
    //     for (std::map<std::string, User>::const_iterator it = s.chans[titi->second].get_users()
    // }

}