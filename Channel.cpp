/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:07 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/17 13:28:28 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <algorithm>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

// Channel::Channel()
// {
	
// }


Channel::Channel(std::string name, User &creator): _name(name), _owner(creator) 
{
	_users.push_back(_owner);
	_operators.push_back(_owner);
}

// Channel& Channel::Channel( const Channel & src )
// {
// 	(void)src;
// 	//if ( this != &src )
// 	//{
// 		//this->_value = src.getValue();
// 	//}
// 	return (*this);
// }


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

std::ostream &			operator<<( std::ostream & o, Channel const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}




/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/*
** --------------------------------- OTHERS ----------------------------------
*/
void Channel::ban(User &kicked)
{
	_banned.push_back(kicked);
	std::vector<User &>::iterator kick;
	kick = std::find(_users.begin(), _users.end(), kicked);
	if (kick != _users.end())
		_users.erase(kick);
	else
		std::cout << "this users doesn't exist" << std::endl;
}

//add a new_user, what happends if the name already exists ?
void Channel::add_user(User &new_user)
{
	std::vector<User &>::iterator add;
	add = std::find(_users.begin(), _users.end(), add);
	if (add != _users.end())
		_users.push_back(new_user);
	else
		std::cout << "this user already exist" << std::endl;	
	
}

void Channel::add_operator(User &admin)
{
	std::vector<User &>::iterator add;
	add = std::find(_operators.begin(), _operators.end(), admin);
	if (add != _operators.end())
		_operators.push_back(admin);
	else
		std::cout << "this operator already exist" << std::endl;	
}

void	Channel::me()
{
	std::vector<User &>::iterator it;
	for (it = _users.begin(); it < _users.end(); it++)
		std::cout << *it << std::endl;
}

void	Channel::set_topic(std::string topic)
{
	this->_topic = topic;
}
//Channel::invite 
//Channel::names ==> list connected users 

/* ************************************************************************** */