#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include "Debug.hpp"









/*
**  choose_msg
** iam the boss 
*/
std::string choose_msg(Server &s, int code, User *u, void *arg)
{
    if (s.cmds.server_replies.count(code) != 1)
    {
        out ("==> Unfound server_replies");
        return ("(no reply found)");
    }
    return (*(s.cmds.server_replies.find(code)->second))(u, arg); // second = la function
}

void numeric_reply(Server &s, User *u, std::string code, void *arg) // rajouter autre chose pour le channel par ex ? //numeric reply 
{
    std::string txt;
    char *ptr;
    txt.append(":");
    txt.append("localhost "); // remplacer par le define
    txt.append(code);
    txt.append(" ");
    txt.append(u->nickname); // lui qui va servir commenickname
    txt.append(" ");
    txt.append(choose_msg(s, std::strtol(code.c_str(), &ptr, 10), u, arg));
    txt.append("\r\n");
    
    out(FG2("Server Reply to be sent:") << code);
    out(txt.c_str());
    if (send(u->socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
    {
        perror("SEND FAILED");
    }
}