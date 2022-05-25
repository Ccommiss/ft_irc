


/*
**       Command: MODE (channel)
**    Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
** 
**    The MODE command is provided so that users may query and change the
**    characteristics of a channel.  For more details on available modes
**    and their uses, see "Internet Relay Chat: Channel Management" [IRC-
**    CHAN].  Note that there is a maximum limit of three (3) changes per
**    command for modes that take a parameter.
** 
**    Numeric Replies:
** 
**            ERR_NEEDMOREPARAMS              ERR_KEYSET
**            ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
**            ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
**            RPL_CHANNELMODEIS
**            RPL_BANLIST                     RPL_ENDOFBANLIST
**            RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
**            RPL_INVITELIST                  RPL_ENDOFINVITELIST
**            RPL_UNIQOPIS
*/
// MODE #TRUC -/+[options] [mode params]
void    Commands::mode (Server &s, User *u, std::vector<std::string> arg)
{
    if ((*(arg.begin() + 1))[0] == '#') // ou & ....
    {
        std::string chan_name = arg.size() > 1 ? *(arg.begin() + 1) : ""; // #truc
        std::string modes = arg.size() > 2 ? *(arg.begin() + 2) : ""; // +=....
        std::string mode_params = arg.size() > 3 ? *(arg.begin() + 3) : "";//
        // si modes c un +, faut un troisieme arg ssi K par ex

    }
}

