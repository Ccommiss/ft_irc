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
	_modes.insert(std::make_pair('n', false));
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

void Channel::setTopic(std::string topic)
{
	_topic.clear();
	_topic = trim(topic);
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
	std::vector<User *>::iterator it = std::find(_banned.begin(), _banned.end(), u);
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
		_users.erase(&new_user->nickname);
		std::cout << "Deleted users" << std::endl;
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

void Channel::displayModes()
{
	out("Channel " << _name << " has modes : ") for (std::map<char, bool>::iterator it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->second == true)
			out(it->first << " is active");
	}
	out("Password is : " << _password);
}

std::string printNames(Channel *chan)
{
	std::string names;
	for (std::map<std::string *, User *>::iterator it = chan->getUsers().begin(); it != chan->getUsers().end(); it++)
	{
		// if is op... @, sinon +
		if (chan->isOperator(it->second))
			names.append("@");
		else
			names.append("");
		names.append(*it->first);
		names.append(" ");
	}
	return names;
}

void Channel::printUsers() // const
{
	start;
	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		out("USERS : " << *it->first); // show the nick name
}

/*
** --------------------------------- MODES METHODS ----------------------------------
*/

std::string Channel::setMode(User *u, char mode, bool value, std::vector<std::string> params) // on va renvoyer le code erreur ou bien  0
{
	(void)u;
	if (!_modes.count(mode)) /* Checking if mode exists */
		return ERR_UNKNOWNMODE;
	/* Future target user for O, o and v options*/
	User *user = NULL;
	switch (mode)
	{
	case 'a': // aninymous mode que sur les hannels & et ! RFC 4.2.1 2811
	{
	}
	case 'k':
	{
		if (trim(params[0]).length() == 0)
			return ERR_NEEDMOREPARAMS;			  // faudra renvoyer erreur
		if (value == true && _modes['k'] == true) // on veut changer alors que deja existant
			return ERR_KEYSET;
		else if (value == true)
			_password = trim(params[0]);
		else if (value == false && trim(params[0]) != _password) // on essaie d'enever le pass mais mavais
			return ERR_KEYSET;									 // mauvais password enleve PAS ECRIT SUR LADOC QUELLE ERREUR ?
		break;
	}
	case 'o': // give channel op status
	{
		if (trim(params[0]).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (findByName(trim(params[0]), &user) == true)
			value == true ? addOperator(user) : removeOperator(user); // faut il erreur si ajoute deux fois ?
		else
			out("Voice : unfound user"); // surement un erreur ? laquelle ?
		break;
	}
	case 'v': /* Voice privilege */
	{
		if (trim(params[0]).length() == 0)
			return ERR_NEEDMOREPARAMS;
		if (findByName(trim(params[0]), &user) == true)
			value == true ? addVoiced(user) : removeVoiced(user); // faut il erreur si ajoute deux fois ?
		else
			out("Voice : unfound user"); // surement un erreur ? laquelle ?
		break;
	}
	case 'i': /* Making invite only */
	{
		break;
	}
	case 'p': /* Private or secret flag -> chan ignored in TOPIC, LIST, NAMES, WHOIS  */
	{
		break;
	}
	case 's':
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
		if (value == true && trim(params[0]).length() == 0)
			return ERR_NEEDMOREPARAMS;
		/* peut etre des checks a faire genre si ca commence par - etc. */
		if (params[0][0] == '-')
			break ; // Pas d'erreurs specifiques pour ce cas 
		value == true ? _limit = strtol(trim(params[0]).c_str(), NULL, 10) : _limit = 0;
		value == true ? printf(" added _limit : %lu\n", _limit) : printf(" removed _limit : %lu\n", _limit);
		break; // to do
	}
	}
	/* b, e, I are mask modes */
	_modes[mode] = value;
	return "";
}
