/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:04 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/17 18:18:04 by ldes-cou         ###   ########.fr       */
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

		void	ban(User kicked);
		void	add_user(std::string name, User &new_user);
		void	add_operator(User ope);
		void 	set_topic(std::string topic);
		void	me();
		std::string const &					get_name();
		std::map<std::string, User> const &	get_users();
		
		
	private:
		std::vector<User>				_operators;
		std::map<std::string, User> 	_users;
		//std::vector<User &>			_invite;
		//std::vector<User &>			_voice;
		std::vector<User> 				_banned;
		User							_owner;
		std::string						_name;
		std::string						_topic;

};

std::ostream &			operator<<( std::ostream & o, Channel & i );

#endif /* ********************************************************* CHANNEL_H */