
#include "Debug.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp" 


void nick(Server &s, User &u, std::vector<std::string> arg)
{
    if (u.registered == 0)
        out (BOLD("Setting nickname to ") << *(arg.begin() + 1));



    if (u.registered == 1)
    {
        std::string txt = set_prefix(&u, arg); // password for nick
        out (BOLD("Changing nick name from ") << u.nickname << " to " << *(arg.begin() + 1));
        if (send(u.socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
        perror ("Fail send");
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
    out("JOIN THSI CHANN CMD" << *(arg.begin() + 1))
    // try (s.chans[arg.begin() + 1])
    // {
    //     s.chans[arg.begin() + 1].join(u); // simple join
    // }
    // catch
    // {
    //     s.chans.push_back(arg.begin() + 1);
    //     s.chans[arg.begin() + 1].join(u); //lemettre en admin car nb user de ce chan == 0
    // }
}