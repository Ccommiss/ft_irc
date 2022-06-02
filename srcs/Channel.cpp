/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:07 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/18 12:07:31 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Answers.hpp"
#include "Channel.hpp"
#include <algorithm>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel() : _owner(0)
{
}

Channel::Channel(std::string name, User *creator) : _name(name), _topic(""), _password(""), _limit(0)
{
	_modes.insert(std::make_pair('O', false));
	_modes.insert(std::make_pair('o', false));
	_modes.insert(std::make_pair('v', false));
	_modes.insert(std::make_pair('a', false));
	_modes.insert(std::make_pair('i', false));
	_modes.insert(std::make_pair('m', false));
	_modes.insert(std::make_pair('n', true)); /* Forbid messages from outside, usually set to true */
	_modes.insert(std::make_pair('q', false));
	_modes.insert(std::make_pair('p', false));
	_modes.insert(std::make_pair('s', false));
	_modes.insert(std::make_pair('r', false));
	_modes.insert(std::make_pair('t', false));
	_modes.insert(std::make_pair('k', false));
	_modes.insert(std::make_pair('l', false));
	_modes.insert(std::make_pair('b', false));
	_modes.insert(std::make_pair('e', false));
	_modes.insert(std::make_pair('I', false));

	_owner = creator;
	_creator = creator;
	out("Creator :" << _owner->nickname)
		add_user(creator);
	if (name[0] != '+')
		_operators.push_back(_owner);
	out("A new chan " << *this << " has been created");
}

Channel::Channel(const Channel &src) : _name(src._name), _owner(src._owner)
{
	(void)src;
	// if ( this != &src )
	//{
	// this->_value = src.getValue();
	//}
	// return (*this);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
	out ("deleting channel")
}

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

std::string &Channel::getName() // const
{
	return _name;
}

std::map<std::string *, User *> &Channel::getUsers() // const
{
	start;
	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		out("USERS : " << *it->first);
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



void Channel::setTopic(std::string topic)
{
	_topic.clear();
	_topic = topic;
}

bool Channel::isTopicSet()
{
	out(" TOPIC IS " << _topic << "-->" << _topic.length()) if (_topic.length() != 0)
	{
		out("TOPIC IS SET") return true;
	}
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
	start;
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

bool	Channel::isPrivateForUser(User *u)
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
	return (_modes[mode]);
}

bool Channel::isBanned(User *u)
{
	std::list<User *>::iterator it = std::find(_banned.begin(), _banned.end(), u);
	if (it != _banned.end())
		return true;
	out ("not banned")
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
	if (_bannedMasks.size() == 0)
		return false;
	for (std::vector<std::string>::iterator it = _bannedMasks.begin(); it != _bannedMasks.end(); it++)
	{
		if (pattern_match(u->fullID(), *it) || pattern_match(u->nickname, *it))
			return true;
	}
	return false;
}

size_t	Channel::getLimit()
{
	return _limit;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Channel::add_user(User *new_user)
{
	start;
	if (!isInChan(new_user))
		_users.insert(std::pair<std::string *, User *>(&new_user->nickname, new_user));
	out("[" << _name << "] "
			<< "New user added :" << new_user->getNickName());
}

void Channel::remove_user(User *new_user)
{
	start;
	if (isInChan(new_user))
	{
		std::cout << "Deleted users : "  << new_user->nickname << std::endl;
		_users.erase(&new_user->nickname);

	}
	else
		out("Unfound user : cannot remove from " << this->_name);
}

void Channel::addToInviteList(User *to_add)
{
	if (!isInvited(to_add))
		_invited.push_back(to_add);
}

void Channel::removeFromInviteList(User *to_del)
{
	if (isInvited(to_del))
		_invited.erase(std::find(_invited.begin(), _invited.end(), to_del));
}

void Channel::addOperator(User *to_add)
{
	if (!isOperator(to_add))
		_operators.push_back(to_add);
}

void Channel::removeOperator(User *to_del)
{
	if (isOperator(to_del))
		_operators.erase(std::find(_operators.begin(), _operators.end(), to_del));
}

void Channel::addVoiced(User *to_add)
{
	if (!isVoiced(to_add))
		_voiced.push_back(to_add);
}

void Channel::removeVoiced(User *to_del)
{
	if (isVoiced(to_del))
		_voiced.erase(std::find(_voiced.begin(), _voiced.end(), to_del));
}

void Channel::addBanned(User *to_add)
{
	if (!isBanned(to_add))
		_banned.push_back(to_add);
}

void Channel::removeBanned(User *to_del)
{
	start;
	if (isBanned(to_del))
	{
			out ("removing from banned list :" << to_del->nickname)
		_banned.erase(std::find(_banned.begin(), _banned.end(), to_del));
	}
}


void Channel::displayModes()
{
	out("Channel " << _name << " has modes : ") for (std::map<char, bool>::iterator it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->second == true)
			out(it->first << " is active");
	}
	out("Password is : " << _password);
}

std::string printNames(Channel *chan, User *u)
{
	std::string names;
	for (std::map<std::string *, User *>::iterator it = chan->getUsers().begin(); it != chan->getUsers().end(); it++)
	{
		// if is op... @, sinon +
		if (!(it->second->hasMode('i') && !chan->isInChan(u))) // invisible 
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

void	Channel::removeBannedFromUsers()
{
	for (std::list<User *>::iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		if (isInChan(*it))
		{
			_users.erase(&(*it)->nickname);
			(*it)->joined_chans.erase(std::find((*it)->joined_chans.begin(), (*it)->joined_chans.end(), this)); //on retire les joined chans
		}
	}
}


std::string printModes(Channel *chan)
{
	std::string modes("[+");
	for (std::map<char, bool >::iterator it = chan->getModes().begin(); it != chan->getModes().end(); it++)
	{
		if (it->second == true)
			modes.push_back(it->first);
	}
	modes.append("]");
	return modes;
}


void	Channel::seeBannedmasks()
{
	out ("Banned masks are :")
	for (size_t i = 0; i < _bannedMasks.size(); i++)
		out (" - " <<  _bannedMasks[i]);
	out ("");
}


void Channel::printUsers() // const
{
	start;
	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		out("USERS : " << *it->first); // show the nick name
}

void Channel::printBanned() // const
{
	start;
	out ("Banned :")
	for (std::list<User *>::iterator it = _banned.begin(); it != _banned.end(); it++)
		out("- : " << (*it)->fullID()); // show the nick name
	out ("");
}

// void Channel::printUsers() // const
// {
// 	start;
// 	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
// 		out("USERS : " << *it->first); // show the nick name
// }

/*
** --------------------------------- MODES METHODS ----------------------------------
*/

std::string Channel::setMode(User *u, char mode, bool value, std::string param) // on va renvoyer le code erreur ou bien  0
{
	start;
	(void)u;
	if (!_modes.count(mode)) /* Checking if mode exists */
		return ERR_UNKNOWNMODE;
	/* Future target user for O, o and v options*/
	User *user = NULL;
	switch (mode)
	{
	case 'a': // aninymous mode que sur les channels & et ! RFC 4.2.1 2811
	{
		if (_name[0] != '!' && _name[0] != '&')
			return (ERR_NOCHANMODES);
		break;
	}
	case 'b': /* Bannir un user/un masque */
	{
		if (value == true && trim(param).length() == 0)
			return RPL_BANLIST;
		if (value == false && trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS; //  a verifier
		if (!isOperator(u)) // Only privileged (eg op and creator) can change modes
			return ERR_CHANOPRIVSNEEDED;
		if (value == true)
		{
			_bannedMasks.push_back(trim(param));

			for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it ++)
			{
				if (matchBannedMask(it->second))
					addBanned(it->second);
			}
		}
		else if (value == false)
		{
			if (std::find(_bannedMasks.begin(), _bannedMasks.end(), trim(param)) != _bannedMasks.end())
				_bannedMasks.erase(std::find(_bannedMasks.begin(), _bannedMasks.end(), trim(param)));
			for (std::list<User *>::iterator it = _banned.begin(); it != _banned.end(); )
			{
				std::list<User *>::iterator tmp = it;
				it++;
				if (!matchBannedMask(*tmp))
					removeBanned(*tmp);
			}
		}
		seeBannedmasks();
		printBanned();
		break;
	}
	case 'e' :
	{
		//Last to do : exception list
	}
	case 'k':
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;			  // faudra renvoyer erreur
		if (value == true && _modes['k'] == true) // on veut changer alors que deja existant
			return ERR_KEYSET;
		else if (value == true)
			_password = trim(param);
		else if (value == false && trim(param) != _password) // on essaie d'enever le pass mais mavais
			return ERR_KEYSET;									 // mauvais password enleve PAS ECRIT SUR LADOC QUELLE ERREUR ?
		break;
	}
	case 'o': // give channel op status
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u)) // Only privileged (eg op and creator) can change modes
			return ERR_CHANOPRIVSNEEDED;
		if (findByName(trim(param), &user) == true)
			value == true ? addOperator(user) : removeOperator(user); // faut il erreur si ajoute deux fois ?
		else
			return ERR_NOSUCHNICK; // surement un erreur ? laquelle ?
		break;
	}
	case 'O': /* give "channel creator" status; see Safe Channels with ! */
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u)) // Only privileged (eg op and creator) can change modes
			return ERR_CHANOPRIVSNEEDED;
		if (findByName(trim(param), &user) == true)
			value == true ? _creator = user : _creator = NULL; // je sais pas trop
		break;
	}
	case 'v': /* Voice privilege */
	{
		if (trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (!isOperator(u)) // Only privileged (eg op and creator) can change modes
			return ERR_CHANOPRIVSNEEDED;
		if (findByName(trim(param), &user) == true)
			value == true ? addVoiced(user) : removeVoiced(user); // faut il erreur si ajoute deux fois ?
		else
			return ERR_NOSUCHNICK; // surement un erreur ? laquelle ?
		break;
	}
	case 'i': /* Making invite only */
	{
		break;
	}
	case 'I': /* Overrides invite only by setting masks ; can be form MODE +b *.*@fsjkf.com OR MODE +b username */
	{
		if (value == true && trim(param).length() == 0)
			return RPL_INVITELIST; // list invite
		if (!isOperator(u)) // Only privileged (eg op and creator) can change modes
			return ERR_CHANOPRIVSNEEDED;
		/* Just push back invite masks ; then, join has to do the check */
		if (value == true)
			_invitedMasks.push_back(trim(param));
		else if (value == false) // enlever le pattern de la list invite
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
		// que se pass t il si set limite inferieure au nb deja en cours ?
		out ("PARMAS SIZE = " << param.size());
		if (value == true && trim(param).length() == 0)
			return ERR_NEEDMOREPARAMS;
		/* peut etre des checks a faire genre si ca commence par - etc. */
		if (param[0] == '-')
			break ; // Pas d'erreurs specifiques pour ce cas, limite -10 par ex
		value == true ? _limit = strtol(trim(param).c_str(), NULL, 10) : _limit = 0;
		value == true ? printf(" added _limit : %lu\n", _limit) : printf(" removed _limit : %lu\n", _limit);
		break; // to do
	}
	}
	if (mode != 'b' && mode != 'I' && mode != 'e')
		_modes[mode] = value;
	return "";
}
