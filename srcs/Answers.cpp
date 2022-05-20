#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include "Debug.hpp"






std::string set_prefix(User *u, std::vector<std::string> cmd)
{
    std::string txt;
    txt.append(":");
    txt.append(u->nickname);
    txt.append("!");
    txt.append(u->name); //username
    txt.append("@localhost ");
    for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end() && *it != "\n"; it++)
        txt.append(*it + " "); // on met touts les commandes dans le prefixe 
    txt = trim(txt);
     txt.append("\r\n");
    out(FG2("Server Reply to be sent:"));
    out (txt)
    return ((txt));
}


/*
**  choose_msg
** iam the boss 
*/
std::string choose_msg(Server &s, int code, User *u)
{
    return (*(s.cmds.server_replies.find(code)->second))(u); // second = la function
}

void server_reply(Server &s, User *u, std::string code)
{
    std::string txt;
    char *ptr;
    txt.append(":");
    txt.append("localhost "); // remplacer par le define
    txt.append(code);
    txt.append(" ");
    txt.append(u->nickname); // lui qui va servir commenickname
    txt.append(" :");
    txt.append(choose_msg(s, std::strtol(code.c_str(), &ptr, 10), u));
    txt.append("\r\n");
    
    out(FG2("Server Reply to be sent:") << code);
    out(txt.c_str());
    if (send(u->socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
    {
        perror("SEND FAILED");
    }
}