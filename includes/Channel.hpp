/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:04 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/18 12:05:51 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "User.hpp"
#include <map>
#include <vector>
#include <iostream>

class Channel
{

	public:

		Channel();
		Channel(std::string name, User * creator);
		Channel( Channel const & src );
		~Channel();
		Channel &		operator=( Channel const & src );

		void								ban(User kicked);
		void								add_user( User *new_user);
		void								remove_user( User *new_user);
		void								add_operator(User ope);
		void 								setTopic(std::string topic);
		std::string  &						getTopic() ;
		void								me();
		std::string  &						getName() ;
		std::map<std::string *, User *>  &	getUsers()  ;
		void 								printUsers();
		bool 								isInChan(User *u);
		bool 								isTopicSet();
		bool 								isBanned(User *u);
		std::string							_name; // nom du chan 
		std::string							_topic;
		
		
	private:
		std::map<std::string *, User *> 	_users;
		std::vector<User *>					_operators;
		std::vector<User *> 				_banned;
		User*								_owner;
		char								_mode;
		
		//std::vector<User &>				_invite;
		//std::vector<User &>				_voice;

};

std::ostream &			operator<<( std::ostream & o, Channel & i );

std::string        printNames(Channel *chan); // formatte, pour command names etc;

#endif /* ********************************************************* CHANNEL_H */