#include "Server.hpp"
#include "Answers.hpp"


/*
**  Command: NAMES
**    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**
**    By using the NAMES command, a user can list all nicknames that are
**    visible to him. For more details on what is visible and what is not,
**    see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
**    <channel> parameter specifies which channel(s) to return information
**    about.  There is no error reply for bad channel names.
**
**    If no <channel> parameter is given, a list of all channels and their
**    occupants is returned.  At the end of this list, a list of users who
**    are visible but either not on any channel or not on a visible channel
**    are listed as being on `channel' "*".
**
**    If the <target> parameter is specified, the request is forwarded to
**    that server which will generate the reply.
**
**    Wildcards are allowed in the <target> parameter.
**
**    Numerics:
**
**            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**            RPL_NAMREPLY                    RPL_ENDOFNAMES
**
**    Examples:
**
**    NAMES #twilight_zone,#42        ; Command to list visible users on
**                                    #twilight_zone and #42
**
**    NAMES                           ; Command to list all visible
**                                    channels and users
**
*/
void Commands::names			(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() == 1) // tous les channel et tous users
	{
		//printNames
	}
	else
	{
		std::vector<std::string> chans  = tokenize(*(cmd.begin() + 1), ',');
		for (size_t i = 0; i < chans.size(); i++)
		{
			out ("nb chans : " << s.chans.size());
			out ("i " << chans[i]);
			if (s.chanExists(chans[i]) &&  (!((s.chans[chans[i]]->hasMode('s') || s.chans[chans[i]]->hasMode('p')) && !s.chans[chans[i]]->isInChan(u)))) // a tester
			{
				s.numeric_reply(u, RPL_NAMREPLY, chans[i], NONE, NONE);
				s.numeric_reply(u, RPL_ENDOFNAMES ,chans[i], NONE, NONE);
			}
		}


	}

}
