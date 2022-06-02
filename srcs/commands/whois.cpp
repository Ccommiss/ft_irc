#include "Server.hpp"
#include "Answers.hpp"

/*
**    Command: WHOIS
**    Parameters: [ <target> ] <mask> *( "," <mask> )
**
**    This command is used to query information about particular user.
**    The server will answer this command with several numeric messages
**    indicating different statuses of each user which matches the mask (if
**    you are entitled to see them).  If no wildcard is present in the
**    <mask>, any information about that nick which you are allowed to see
**    is presented.
**
**    If the <target> parameter is specified, it sends the query to a
**    specific server.  It is useful if you want to know how long the user
**    in question has been idle as only local server (i.e., the server the
**    user is directly connected to) knows that information, while
**    everything else is globally known.
**
**    Wildcards are allowed in the <target> parameter.
**
**    Numeric Replies:
**
**            ERR_NOSUCHSERVER              ERR_NONICKNAMEGIVEN
**            RPL_WHOISUSER                 RPL_WHOISCHANNELS
**            RPL_WHOISCHANNELS             RPL_WHOISSERVER
**            RPL_AWAY                      RPL_WHOISOPERATOR
**            RPL_WHOISIDLE                 ERR_NOSUCHNICK
**            RPL_ENDOFWHOIS
**
**    Examples:
**
**    WHOIS wiz                       ; return available user information
**                                    about nick WiZ
**
**    WHOIS eff.org trillian          ; ask server eff.org for user
**                                    information  about trillian
**
*/


/*
** From 2811, 4.2.6 Private and Secret Channels
**
**
**    The channel flag 'p' is used to mark a channel "private" and the
**    channel flag 's' to mark a channel "secret".  Both properties are
**    similar and conceal the existence of the channel from other users.
**
**    This means that there is no way of getting this channel's name from
**    the server without being a member.  In other words, these channels
**    MUST be omitted from replies to queries like the WHOIS command
*/

void Commands::whois(Server &s, User *u, std::vector<std::string> cmd)
{
    std::string target = *(cmd.begin() + 1);

    User *info = NULL;
    if (s.findByName(target, &info) == true)
    {
        s.numeric_reply(u, RPL_WHOISUSER, info->getNickName(), info->getName(), info->getRealname());
        out (info->getRealname())
        s.numeric_reply(u, RPL_WHOISSERVER, s.hostname, s.hostname, "A custom server");
        //s.numeric_reply(u, RPL_WHOISOPERATOR, info->getNickName(), NONE, NONE);
        s.numeric_reply(u, RPL_WHOISIDLE, info->getNickName(), "8 seconds", NONE); // faire un compteur de second de connexion
        s.numeric_reply(u, RPL_WHOISCHANNELS, info->getNickName(), info->whoIsChannels(u), NONE);
        if (info->hasMode('a'))
            s.numeric_reply(u, RPL_AWAY, info->nickname, info->getAwayMsg(), NONE);
        s.numeric_reply(u, RPL_ENDOFWHOIS, info->getNickName(), NONE, NONE);
       
    }

}
