/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:07 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/06/03 18:15:55 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"
#include "Channel.hpp"
#include <algorithm>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/


Channel::Channel(std::string name, User *creator) : _name(name), _topic(""), _password(""), _limit(0)
{
	_modes.insert(std::pair<char, bool>('O', false));
	_modes.insert(std::pair<char, bool>('o', false));
	_modes.insert(std::pair<char, bool>('v', false));
	_modes.insert(std::pair<char, bool>('a', false));
	_modes.insert(std::pair<char, bool>('i', false));
	_modes.insert(std::pair<char, bool>('m', false));
	_modes.insert(std::pair<char, bool>('n', true)); /* Forbid messages from outside, usually set to true */
	_modes.insert(std::pair<char, bool>('q', false));
	_modes.insert(std::pair<char, bool>('p', false));
	_modes.insert(std::pair<char, bool>('s', false));
	_modes.insert(std::pair<char, bool>('r', false));
	_modes.insert(std::pair<char, bool>('t', false));
	_modes.insert(std::pair<char, bool>('k', false));
	_modes.insert(std::pair<char, bool>('l', false));
	_modes.insert(std::pair<char, bool>('b', false));
	_modes.insert(std::pair<char, bool>('e', false));
	_modes.insert(std::pair<char, bool>('I', false));

	_owner = creator;
	_creator = creator;
	add_user(creator);
	if (name[0] != '+') /* in + aka unmoderated channels, no operators are allowed */ 
		_operators.push_back(_owner);
	out("A new chan " << *this << " has been created");
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel(){
	out("deleting channel")}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel &Channel::operator=(Channel const &rhs)
{
	(void)rhs;
	return *this;
}

std::ostream &operator<<(std::ostream &o, Channel &i)
{
	o << i.getName() << std::endl;
	return o;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string &Channel::getName()
{
	return _name;
}

std::map<std::string *, User *> &Channel::getUsers()
{
	return _users;
}

std::string &Channel::getTopic()
{
	return _topic;
}

std::map<char, bool> &Channel::getModes()
{
	return _modes;
}

std::vector<std::string> &Channel::getBannedMasks()
{
	return _bannedMasks;
}

std::vector<std::string> &Channel::getInvitedMasks()
{
	return _invitedMasks;
}

std::vector<std::string> &Channel::getExceptMasks()
{
	return _exceptMasks;
}

void Channel::setTopic(std::string topic)
{
	_topic.clear();
	_topic = topic;
}

bool Channel::isTopicSet()
{
	return false;
}

bool Channel::isInChan(User *u)
{
	if (_users.count(&u->nickname) == 1)
		return true;
	return false;
}

bool Channel::isInvited(User *user)
{
	if (std::find(_invited.begin(), _invited.end(), user) != _invited.end())
		return true;
	return false;
}

bool Channel::findByName(std::string nick, User **u)
{
	std::map<std::string *, User *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (*(it->first) == nick)
		{
			*u = (it->second);
			return true;
		}
	}
	return false;
}

bool Channel::isPrivateForUser(User *u)
{
	if ((hasMode('s') || hasMode('p')) && !isInChan(u))
		return true;
	return false;
}

bool Channel::hasKey()
{
	return (_modes['k']);
}

bool Channel::hasMode(char mode)
{
	if (_modes.count(mode) == 0)
		return false;
	return (_modes[mode]);
}

bool Channel::isBanned(User *u)
{
	std::list<User *>::iterator it = std::find(_banned.begin(), _banned.end(), u);
	if (it != _banned.end())
		return true;
	return false;
}

bool Channel::isOperator(User *u)
{
	std::vector<User *>::iterator it = std::find(_operators.begin(), _operators.end(), u);
	if (it != _operators.end())
		return true;
	return false;
}

bool Channel::isVoiced(User *u)
{
	std::vector<User *>::iterator it = std::find(_voiced.begin(), _voiced.end(), u);
	if (it != _voiced.end())
		return true;
	return false;
}

bool Channel::isOwner(User *u)
{
	if (_owner == u)
		return true;
	return false;
}

bool Channel::isCorrectPass(std::string candidate)
{
	out("candidate pass : " << candidate) if (candidate == _password) return true;
	return false;
}

bool Channel::matchInviteMask(User *u)
{
	for (std::vector<std::string>::iterator it = _invitedMasks.begin(); it != _invitedMasks.end(); it++)
		if (pattern_match(u->fullID(), *it))
			return true;
	return false;
}

bool Channel::matchBannedMask(User *u)
{
	if (_bannedMasks.size() == 0 || matchExceptMask(u))
		return false;
	for (std::vector<std::string>::iterator it = _bannedMasks.begin(); it != _bannedMasks.end(); it++)
	{
		if (pattern_match(u->fullID(), *it) || pattern_match(u->nickname, *it))
			return true;
	}
	return false;
}

bool Channel::matchExceptMask(User *u)
{
	if (_exceptMasks.size() == 0)
		return false;
	for (std::vector<std::string>::iterator it = _exceptMasks.begin(); it != _exceptMasks.end(); it++)
	{
		if (pattern_match(u->fullID(), *it) || pattern_match(u->nickname, *it))
			return true;
	}
	return false;
}

size_t Channel::getLimit()
{
	return _limit;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
**	@brief add user to the channel
**	@param User* user to be added
*/
void Channel::add_user(User *new_user)
{
	if (!isInChan(new_user))
		_users.insert(std::pair<std::string *, User *>(&new_user->nickname, new_user));
}

/*
**	@brief remove user to the channel
**	@param user* user to be removed
*/
void Channel::remove_user(User *toDel)
{
	if (isInChan(toDel))
		_users.erase(&toDel->nickname);
	if (isOperator(toDel))
		removeOperator(toDel);
}

/*
**	@brief add user to inviteList
**	@param User* user to be added
*/
void Channel::addToInviteList(User *to_add)
{
	if (!isInvited(to_add))
		_invited.push_back(to_add);
}

/*
**	@brief remove user from inviteList
**	@param user* user to be removed
*/
void Channel::removeFromInviteList(User *to_del)
{
	if (isInvited(to_del))
		_invited.erase(std::find(_invited.begin(), _invited.end(), to_del));
}

/*
**	@brief add user to operators
**	@param User* user to be added
*/
void Channel::addOperator(User *to_add)
{
	if (!isOperator(to_add))
		_operators.push_back(to_add);
}

/*
**	@brief remove user from operators
**	@param user* user to be removed
*/
void Channel::removeOperator(User *to_del)
{
	if (isOperator(to_del))
		_operators.erase(std::find(_operators.begin(), _operators.end(), to_del));
}

/*
**	@brief add user to voiced
**	@param User* user to be added
*/
void Channel::addVoiced(User *to_add)
{
	if (!isVoiced(to_add))
		_voiced.push_back(to_add);
}

/*
**	@brief remove user from voiced
**	@param user* user to be removed
*/
void Channel::removeVoiced(User *to_del)
{
	if (isVoiced(to_del))
		_voiced.erase(std::find(_voiced.begin(), _voiced.end(), to_del));
}

/*
**	@brief add user to banned
**	@param User* user to be added
*/
void Channel::addBanned(User *to_add)
{
	if (!isBanned(to_add))
		_banned.push_back(to_add);
}

/*
**	@brief remove user from banned
**	@param user* user to be removed
*/
void Channel::removeBanned(User *to_del)
{
	if (isBanned(to_del))
		_banned.erase(std::find(_banned.begin(), _banned.end(), to_del));
}

/*
**	@brief debug function to display modes
*/
void Channel::displayModes()
{
	out("Channel " << _name << " has modes : ") for (std::map<char, bool>::iterator it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->second == true)
			out(it->first << " is active");
	}
	out("Password is : " << _password);
}

std::string printModes(Channel *chan)
{
	std::string modes("[+");
	for (std::map<char, bool>::iterator it = chan->getModes().begin(); it != chan->getModes().end(); it++)
	{
		if (it->second == true)
			modes.push_back(it->first);
	}
	modes.append("]");
	return modes;
}

void Channel::seeBannedmasks()
{
	out("Banned masks are :") for (size_t i = 0; i < _bannedMasks.size(); i++)
		out(" - " << _bannedMasks[i]);
	out("");
}

void Channel::printUsers()
{
	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		out("USERS : " << *it->first);
}

void Channel::printBanned()
{
	out("Banned :");
	for (std::list<User *>::iterator it = _banned.begin(); it != _banned.end(); it++)
		out("- : " << (*it)->fullID());
	out("");
}

/*
** --------------------------------- MODES METHODS ----------------------------------
*/

std::string Channel::setMode(User *u, char mode, bool value, std::string param)
{
	(void)u;
	if (_modes.count(mode) == 0) /* Checking if mode exists */
		return ERR_UNKNOWNMODE;
	/* Future target user for O, o and v options*/
	User *user = NULL;
	switch (mode)
	{
	case 'a': /* Only for & et ! RFC 4.2.1 2811 */
	{
		if (_name[0] != '!' && _name[0] != '&')
			return (ERR_NOCHANMODES);
		break;
	}
	case 'b': /* Ban a mask */
	{
		if (value == true && trim(param).length() == 0)
			return RPL_BANLIST;
		if (value == false && trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u))
			return ERR_CHANOPRIVSNEEDED;
		if (value == true)
		{
			_bannedMasks.push_back(trim(param));
			for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if (matchBannedMask(it->second) && !matchExceptMask(it->second))
					addBanned(it->second);
			}
		}
		else if (value == false)
		{
			if (std::find(_bannedMasks.begin(), _bannedMasks.end(), trim(param)) != _bannedMasks.end())
				_bannedMasks.erase(std::find(_bannedMasks.begin(), _bannedMasks.end(), trim(param)));
			for (std::list<User *>::iterator it = _banned.begin(); it != _banned.end();)
			{
				std::list<User *>::iterator tmp = it;
				it++;
				if (!matchBannedMask(*tmp))
					removeBanned(*tmp);
			}
		}
		break;
	}
	case 'e': /* Overwrite ban mask */ 
	{
		if (value == true && trim(param).length() == 0)
			return RPL_EXCEPTLIST;
		if (value == false && trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u))
			return ERR_CHANOPRIVSNEEDED;
		if (value == true) /* Adding an exception ; thus ppl who have a nickname are now unbanned */
		{
			_exceptMasks.push_back(trim(param));
			for (std::list<User *>::iterator it = _banned.begin(); it != _banned.end();)
			{
				std::list<User *>::iterator tmp = it;
				it++;
				if (matchExceptMask(*tmp))
					removeBanned(*tmp);
			}
		}
		else if (value == false) /* Removing an exception ; thus ppl who fall through bann are now banned */
		{
			if (std::find(_exceptMasks.begin(), _exceptMasks.end(), trim(param)) != _exceptMasks.end())
				_exceptMasks.erase(std::find(_exceptMasks.begin(), _exceptMasks.end(), trim(param)));
			for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if (!matchExceptMask(it->second) && matchBannedMask(it->second))
					addBanned(it->second);
			}
		}
		break;
	}
	case 'k': /* Add a key pass */ 
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (value == true && _modes['k'] == true)
			return ERR_KEYSET;
		else if (value == true)
			_password = trim(param);
		else if (value == false && trim(param) != _password)
			return ERR_KEYSET;
		break;
	}
	case 'o': /* Channel operator */
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u))
			return ERR_CHANOPRIVSNEEDED;
		if (findByName(trim(param), &user) == true)
			value == true ? addOperator(user) : removeOperator(user);
		else
			return ERR_NOSUCHNICK;
		break;
	}
	case 'O': /* give "channel creator" status; see Safe Channels with ! */
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u))
			return ERR_CHANOPRIVSNEEDED;
		if (findByName(trim(param), &user) == true)
			value == true ? _creator = user : _creator = NULL;
		break;
	}
	case 'v': /* Voice privilege */
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u))
			return ERR_CHANOPRIVSNEEDED;
		if (findByName(trim(param), &user) == true)
			value == true ? addVoiced(user) : removeVoiced(user);
		else
			return ERR_NOSUCHNICK;
		break;
	}
	case 'i': /* Making invite only */
	{
		break;
	}
	case 'I': /* Overrides invite only by setting masks ; can be form MODE +b *.*@fsjkf.com OR MODE +b username */
	{
		if (value == true && trim(param).length() == 0)
			return RPL_INVITELIST;
		if (!isOperator(u))
			return ERR_CHANOPRIVSNEEDED;
		/* Just push back invite masks ; then, join has to do the check */
		if (value == true)
			_invitedMasks.push_back(trim(param));
		else if (value == false)
		{
			if (std::find(_invitedMasks.begin(), _invitedMasks.end(), trim(param)) != _invitedMasks.end())
				_invitedMasks.erase(std::find(_invitedMasks.begin(), _invitedMasks.end(), trim(param)));
		}
		break;
	}
	case 'p': /* Private or secret flag -> chan ignored in TOPIC, LIST, NAMES, WHOIS  */
	{
		break;
	}
	case 's': /* Same as p */
	{
		break;
	}
	case 'm': /* Moderated chan */
	{
		break;
	}
	case 'l': /* User limits to channel. ex +l 10 to 10 as limit or -l to remove */
	{
		if (value == true && trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (param[0] == '-')
			return IGNORE;
		value == true ? _limit = strtol(trim(param).c_str(), NULL, 10) : _limit = 0;
		break;
	}
	}
	if (mode != 'b' && mode != 'I' && mode != 'e')
		_modes[mode] = value;
	return "";
}

/*
** --------------------------------- NON MEMBER FUNCTIONS ----------------------------------
*/

/*
**	@brief function used for RPL_NAMREPLY. Displays current visible users of a channel
**	@param Channel *chan
**	@param
*/
std::string printNames(Channel *chan, User *u)
{
	std::string names;
	for (std::map<std::string *, User *>::iterator it = chan->getUsers().begin(); it != chan->getUsers().end(); it++)
	{
		/* if User is invisble, cannot be displayed for requesting user if not in chan */ 
		if (!(it->second->hasMode('i') && !chan->isInChan(u)))
		{
			if (chan->isOperator(it->second))
				names.append("@");
			else
				names.append("");
			names.append(*it->first);
			names.append(" ");
		}
	}
	return names;
}