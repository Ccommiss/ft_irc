/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:07 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/17 18:34:03 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel()
{
	
}


Channel::Channel(std::string name, User &creator): _name(name), _owner(creator) 
{
	
	_users.insert(std::pair<std::string, User&>(_name, _owner));
	_operators.push_back(_owner);
	std::cout << *this << std::endl;
}

Channel::Channel( const Channel & src ): _owner(src._owner), _name(src._name)
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
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Channel& i )
{
	o << "VChan = " << i.get_name() << std::endl;
	std::map<std::string, User>::const_iterator it;
	for (it = i.get_users().begin(); it  != i.get_users().end(); it++)
		o << "Users " << i << it->first << std::endl; 
	return o;
}



/*
** --------------------------------- ACCESSOR ---------------------------------
*/
std::string const & Channel::get_name()
{
	return this->_name;
	
}
std::map<std::string, User> const & Channel::get_users()
{
	return this->_users;
	
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

//add a new_user, what happends if the name already exists ?
void Channel::add_user(std::string name, User &new_user)
{
	std::cout << name << std::endl;
	_users.insert(std::make_pair(name, new_user));
	std::cout << "ok on est la !!!!!!!!!!!!!!!!!!!!!!" << std::endl;
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

// void	Channel::set_topic(std::string topic)
// {
// 	this->_topic = topic;
// }
// //Channel::invite 
// //Channel::names ==> list connected users 

// /* ************************************************************************** */