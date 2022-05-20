#include "Server.hpp"

void send_pm(Server &s, User *u, std::string dest_nick, std::vector<std::string> arg)
{

    out("Sending to people " << dest_nick);
    std::map<const std::string *, const User *>::iterator it = s.server_users.begin();
    while (it != s.server_users.end())
    {
        if (dest_nick == it->second->nickname)
        {
            // out ("found user !" << s.server_users.at(arg_1).socket_descriptor);
            std::string txt = set_prefix(u, arg);
            send(it->second->socket_descriptor, txt.c_str(), txt.length(), 0);
            return;
        }
        it++;
    }
    out("unfound user" << dest_nick);
}

void send_channel(Server &s, User *u, std::string dest_channel, std::vector<std::string> arg)
{
    // regarder se passe quioi si channel non existant
    {
        out("Sending to channel >>> " << dest_channel)
            std::string txt = set_prefix(u, arg);
        s.chans[dest_channel]->printUsers();
        for (std::map<std::string *, User *>::iterator it = s.chans[dest_channel]->getUsers().begin(); it != s.chans[dest_channel]->getUsers().end(); it++)
        {
            if (it->second != u) // snd to other and not current user
                send(it->second->socket_descriptor, txt.c_str(), txt.length(), 0);
        }
    }
}

/*
**  Command: PRIVMSG
**  @param arg : <msgtarget> <text to be sent>
**  Triggered by /msg (login)
** or talking in a chan
*/

void Commands::priv_msg(Server &s, User *u, std::vector<std::string> arg)
{
    start;
    std::string dest = *(arg.begin() + 1);
    out("Sending priv msg to " << dest);
    if (dest.compare(0, 1, "#", 0, 1) == 0)
        send_channel(s, u, dest, arg);
    else
        send_pm(s, u, dest, arg);
}