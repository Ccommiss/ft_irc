#include "Server.hpp"

void Commands::setUser(Server &s, User &u, std::vector<std::string> arg)
{
    (void)s;
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