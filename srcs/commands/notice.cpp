/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:51:36 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 14:51:38 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**       Command: NOTICE
**    Parameters: <msgtarget> <text>
**
**    The NOTICE command is used similarly to PRIVMSG.  The difference
**    between NOTICE and PRIVMSG is that automatic replies MUST NEVER be
**    sent in response to a NOTICE message.  This rule applies to servers
**
**    too - they MUST NOT send any error reply back to the client on
**    receipt of a notice.  The object of this rule is to avoid loops
**    between clients automatically sending something in response to
**    something it received.
**
**    This command is available to services as well as users.
**
**    This is typically used by services, and automatons (clients with
**    either an AI or other interactive program controlling their actions).
**
**    See PRIVMSG for more details on replies and examples.
*/

void Commands::notice			(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() < 3)
		return ;
	priv_msg(s, u, cmd);
}
