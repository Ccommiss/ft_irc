/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:51:42 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 14:51:59 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"

/*
**   Command: OPER
**    Parameters: <name> <password>
**
**    A normal user uses the OPER command to obtain operator privileges.
**    The combination of <name> and <password> are REQUIRED to gain
**    Operator privileges.  Upon success, the user will receive a MODE
**    message (see section 3.1.5) indicating the new user modes.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              RPL_YOUREOPER
**            ERR_NOOPERHOST                  ERR_PASSWDMISMATCH
**
**    Example:
**
**    OPER foo bar                    ; Attempt to register as an operator
**                                    using a username of "foo" and "bar"
**                                    as the password.
*/

void Commands::oper			(Server &s, User *u, std::vector<std::string> cmd)
{
	if (cmd.size() < 3)
		return (s.numeric_reply(u, ERR_NEEDMOREPARAMS, *cmd.begin(), NONE, NONE));

	std::string name = *(cmd.begin() + 1);
	std::string pass = *(cmd.begin() + 2);

	if (!s.oper_pass_check(pass))
		return (s.numeric_reply(u, ERR_PASSWDMISMATCH, pass, NONE, NONE));

	u->setOneKeyMode('O', true);
	return (s.numeric_reply(u, RPL_YOUREOPER, NONE, NONE, NONE));
}
