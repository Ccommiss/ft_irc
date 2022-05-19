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

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel()
{
	
}


Channel::Channel(std::string name, User &creator):  _name(name), _owner(creator)
{
	_owner = creator;
	out ("Creator :" << _owner.nickname)
	out ("Creator :" << creator.nickname)
	_users.insert(std::make_pair(&creator.nickname, &creator));
	for (std::map<std::string *, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		out ("USERS : " << it->first);
	_operators.push_back(_owner);
	std::cout << "a new chan " << *this << " has been created" << std::endl;
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
	o << i.get_name() << std::endl;
	return o;
}



/*
** --------------------------------- ACCESSOR ---------------------------------
*/
std::string& 				Channel::get_name() //const 
{
	return this->_name;
	
}
std::map<std::string *, User *>& 	Channel::get_users() //const 
{
	start;
	out (*this->_users.begin()->first)
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
	start;
	std::cout << name << std::endl;
	_users.insert(std::make_pair(&name, &new_user));
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