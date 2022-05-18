
#include "Debug.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp" 


void nick(Server &s, User &u, std::vector<std::string> arg)
{
    start;
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

void setUser(Server &s, User &u, std::vector<std::string> arg)
{
    out("Setting name to : " << *(arg.begin() + 1));
    u.setName(*(arg.begin() + 1));
    if (u.registered == 0)
    {
        server_reply(&u, "001");
        server_reply(&u, "002");
        server_reply(&u, "003");
        server_reply(&u, "004");
        u.registered = 1;
        out("Answer sent to " << u.socket_descriptor);
    }
}

void quit_s(Server &s, User &u, std::vector<std::string> arg) // exit ou quit
{
    out("QUIT CMD" << *arg.begin())
    s.quit_server(u);
}



void join(Server &s, User &u, std::vector<std::string> arg) // exit ou quit
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

/*
**  Command: PRIVMSG
**  @param arg : <msgtarget> <text to be sent>
**  Triggered by /msg (login)
** or talking in a chan 
*/
void            priv_msg(Server &s, User &u, std::vector<std::string> arg)
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