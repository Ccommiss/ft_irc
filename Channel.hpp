/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:04 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/18 16:16:59 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Server.hpp"

class Channel
{

	public:

		Channel();
		Channel(std::string name, User & creator);
		Channel( Channel const & src );
		~Channel();
		Channel &		operator=( Channel const & src );

		void								ban(User kicked);
		void								add_user(User &new_user);
		void								add_operator(User ope);
		void 								set_topic(std::string topic);
		void								me();
		std::string &						get_name(); 
		std::map<std::string*, User> &		get_users(); 
		
		
	private:
		std::map<std::string*, User> 		_users;
		std::string							_name;
		std::vector<User>					_operators;
		std::vector<User> 					_banned;
		User								_owner;
		std::string							_topic;
		//std::vector<User &>				_invite;
		//std::vector<User &>				_voice;

};

std::ostream &			operator<<( std::ostream & o, Channel & i );

#endif /* ********************************************************* CHANNEL_H */