



#include "Server.hpp"
#include "User.hpp"


void nick(Server &s, User &u, std::string nick)
{
    out ("NICK CMD" << nick)
    u.setNickName(nick);
}

void quit_s(Server &s, User &u, std::string nick) // exit ou quit
{
    out ("QUIT CMD" << nick)
    s.quit_server(u);
}
