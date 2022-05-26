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
#include <algorithm>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel() : _owner(0)
{
	
}


Channel::Channel(std::string name, User *creator):  _name(name), _topic(""), _password("")
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
	out ("Creator :" << _owner->nickname)
	add_user(creator);
	_operators.push_back(_owner);
	out("A new chan " << *this << " has been created");
}

Channel::Channel( const Channel & src ): _name(src._name), _owner(src._owner)
{
	(void)src;
	//if ( this != &src )
	//{
		//this->_value = src.getValue();
	//}
	//return (*this);
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

Channel &				Channel::operator=( Channel const & rhs )
{
	(void)rhs;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Channel& i )
{
	o << i.getName() << std::endl;
	return o;
}



/*
** --------------------------------- ACCESSOR ---------------------------------
*/
std::string& 				Channel::getName() //const 
{
	return _name;
	
}
std::map<std::string *, User *>& 	Channel::getUsers() //const 
{
	start;
	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		out ("USERS : " << *it->first);
	return _users;
}

/*
**	Prints the chan _users map (std::map<std::string *, User *>).  
*/
void	Channel::printUsers() //const 
{
	start;
	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		out ("USERS : " << *it->first); //show the nick name 
}

/*
** --------------------------------- OTHERS ----------------------------------
*/
// void Channel::ban(User kicked)
// {
// 	_banned.push_back(kicked);
// 	std::vector<User>::iterator kick;
// 	kick = std::find(_users.begin(), _users.end(), kicked);
// 	if (kick != _users.end())
// 		_users.erase(kick);
// 	else
// 		std::cout << "this users doesn't exist" << std::endl;
// }

bool Channel::isTopicSet()
{
	out (" TOPIC IS " << _topic << "-->" << _topic.length())
	if (_topic.length() != 0)
	{
		out ("TOPIC IS SET")
		return true;
	}
	return false;
}

bool Channel::isInChan(User *u)
{
	if (_users.count(&u->nickname) == 1)
		return true;
	return false;
}

bool								Channel::hasKey()
{
	return (_modes['k']);
} //si le flag K est actif pour rentrer 


bool Channel::isBanned(User *u)
{
	std::vector<User *>::iterator it = std::find(_banned.begin(), _banned.end(), u);
	if (it != _banned.end())
		return true;
	return false;
}

bool								Channel::isOperator(User *u)
{
	std::vector<User *>::iterator it = std::find(_banned.begin(), _banned.end(), u);
	if (it != _banned.end())
		return true;
	return false;
}

bool 								Channel::isOwner(User *u)
{
	if (_owner == u)
		return true;
	return false;
}

void Channel::add_user(User *new_user)
{
	start;
	_users.insert(std::pair<std::string *, User *>(&new_user->nickname, new_user));
	out ("[" << _name << "] " << "New user added :" << new_user->getNickName());
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

// void Channel::add_operator(User admin)
// {
// 	std::vector<User>::iterator add;
// 	add = std::find(_operators.begin(), _operators.end(), admin);
// 	if (add != _operators.end())
// 		_operators.push_back(admin);
// 	else
// 		std::cout << "this operator already exist" << std::endl;	
// }

// void	Channel::me()
// {
// 	// std::vector<User>::iterator it;
// 	// for (it = _users.begin(); it < _users.end(); it++)
// 	// 	std::cout << *it << std::endl;
// }

std::string 	Channel::setMode(char mode, bool value, std::vector<std::string > params) // on va renvoyer le code erreur ou bien  0 
{	
	if (!_modes.count(mode)) // c un bon caractere
		return ERR_UNKNOWNMODE;
	
	switch ( mode )
	{
		case 'k':
			if (trim(params[0]).length() == 0)
				return ERR_NEEDMOREPARAMS; // faudra renvoyer erreur 
			if (value == true && _modes['k'] == true) // on veut changer alors que deja existant 
				return ERR_KEYSET;
			else if (value == true)
				_password = trim(params[0]);
			else if (value == false && trim(params[0]) != _password) // on essaie d'enever le pass mais mavais
				return ERR_KEYSET; // mauvais password enleve PAS ECRIT SUR LADOC QUELLE ERREUR ?

	} 
	_modes[mode] = value;
	return "";
}


void	Channel::setTopic(std::string topic)
{
	//_topic.clear();
	_topic = topic;
}

std::string&	Channel::getTopic()
{
	return _topic;
}
// //Channel::invite 
// //Channel::names ==> list connected users 

// /* ************************************************************************** */


void			Channel::displayModes()
{
	out ("Channel " << _name << " has modes : ")
	for (std::map<char, bool>::iterator it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->second == true)
			out (it->first << " is active");
	}
	out ("Password is : " << _password);
}


std::map<char, bool>&			Channel::getModes()
{
		return _modes;
}
bool 						Channel::isCorrectPass(std::string candidate)
{
	out ("candidate pass : " << candidate)
	if (candidate == _password)
		return true; 
	return false;
}

std::string        printNames(Channel *chan)
{
	 std::string names;
	for (std::map<std::string *, User *>::iterator it = chan->getUsers().begin() ; it != chan->getUsers().end(); it++)
	{
		//if is op... @, sinon +
		names.append("@");
		names.append(*it->first);
		names.append(" ");
	}
	return names;
}
