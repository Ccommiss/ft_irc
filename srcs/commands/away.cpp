/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:36:00 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 18:14:07 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**     Command: AWAY
**    Parameters: [ <text> ]
**
**    With the AWAY command, clients can set an automatic reply string for
**    any PRIVMSG commands directed at them (not to a channel they are on).
**    The server sends an automatic reply to the client sending the PRIVMSG
**    command.  The only replying server is the one to which the sending
**    client is connected to.
**
**    The AWAY command is used either with one parameter, to set an AWAY
**    message, or with no parameters, to remove the AWAY message.
**
**    Because of its high cost (memory and bandwidth wise), the AWAY
**    message SHOULD only be used for client-server communication.  A
**    server MAY choose to silently ignore AWAY messages received from
**    other servers.  To update the away status of a client across servers,
**    the user mode 'a' SHOULD be used instead.  (See Section 3.1.5)
**
**    Numeric Replies:
**
**            RPL_UNAWAY                    RPL_NOWAWAY
**
**    Example:
**
**    AWAY :Gone to lunch.  Back in 5 ; Command to set away message to
**                                    "Gone to lunch.  Back in 5".
**
*/

void Commands::away(Server &s, User *u, std::vector<std::string> cmd)
{
    std::string msg;
    if (cmd.size() > 1)
    {
        msg = implodeMessage(cmd.begin() + 1, cmd.end());
        u->setAway(msg);
        s.numeric_reply(u, RPL_NOWAWAY, u->nickname, msg, NONE);
    }
    else
    {
        u->setOneKeyMode('a', false); /* remeber : away cannot be toogled by a in modes */
        s.numeric_reply(u, RPL_UNAWAY, u->nickname, NONE, NONE);
    }
}
