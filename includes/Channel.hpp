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


/*
**         INVITE  - Invite a client to an invite-only channel (mode +i) //
**         KICK    - Eject a client from the channel
**         MODE    - Change the channel's mode, as well as
**                   members' privileges
**         PRIVMSG - Sending messages to the channel (mode +n, +m, +v)
**         TOPIC   - Change the channel topic in a mode +t channel
*/

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
		void								add_operator(User *ope);
		void								addToInviteList(User *to_add);
		void								removeFromInviteList(User *to_del);
		bool								isInvited(User *user);
		void 								setTopic(std::string topic);
		std::string  &						getTopic() ;
		void								me();
		std::string  &						getName();
		std::map<std::string *, User *>  &	getUsers();
		std::string							setMode(User *u, char mode, bool value, std::vector<std::string > params);
		void								displayModes();
		bool								isCorrectPass(std::string candidate);
		std::map<char, bool>&				getModes();
		void 								printUsers();
		bool 								isInChan(User *u);
		bool 								findByName(std::string nick, User **u);
		bool 								isTopicSet();
		bool								hasKey(); //si le flag K est actif pour rentrer 
		bool								hasMode(char mode);
		bool 								isBanned(User *u);
		bool								isOperator(User *u);
		bool 								isOwner(User *u);
		std::string							_name; // nom du chan 
		std::string							_topic;

		
		
	private:
		std::map<std::string *, User *> 	_users;
		std::vector<User *>					_operators;
		std::vector<User *> 				_banned;
		User*								_owner;
		std::map<char, bool>				_modes;
		std::string 						_password;
		
		std::vector<User *>					_invited;
		//std::vector<User *>				_voice;

};

std::ostream &			operator<<( std::ostream & o, Channel & i );

std::string        printNames(Channel *chan); // formatte, pour command names etc;

#endif /* ********************************************************* CHANNEL_H */