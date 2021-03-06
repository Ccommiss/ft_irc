/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:50:03 by csejault          #+#    #+#             */
/*   Updated: 2022/06/06 13:16:29 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//Class_Name = Server
////define{
#ifndef SERVER_TCP_HPP
# define SERVER_TCP_HPP

#include <sys/epoll.h>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <arpa/inet.h>

#include "define.hpp"
#include "cs_utils.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include "Channel.hpp"
#include "Debug.hpp"
//define - END}

class User;

class	Server {

	public:
		//pub_constructor{
		Server( const char * port, const char *pass);
		~Server( void );
		//pub_constructor - END}

		//pub_fct{
		void			shutdown(bool does_throw);
		void			run( void );
		bool			pass_check( std::string to_check) const;
		bool			oper_pass_check( std::string to_check) const;

		void			printUsers();
		bool 			chanExists(std::string chan_name);
		bool 			findByName(std::string nick, User **u);
		bool 			nicknameExists(std::string nick);
		std::string     choose_msg(int code, User *u, std::string arg1, std::string arg2, std::string arg3);
		void 			numeric_reply(User *u, std::string code, std::string arg1, std::string arg2, std::string arg3);
		void										delete_user(User * to_del);
		//pub_fct - END}

		//pub_var{
		std::map<const std::string *, User *>		server_users; 
		std::map<std::string, Channel *>			chans;
		Commands                                	cmds; 
		char        								hostname[HOSTNAME_SIZE];
		//pub_var - END}

	private:

		//priv_constructor{
		Server( Server const & src );
		Server &	operator=( Server const & rhs );
		//priv_constructor - END }
		
		//priv_fct{
		//out_loop
		void 		get_infos( void );
		void 		start_listening( void );
		void 		set_monitoring( void );

		//in_loop
		char	*	get_ip( void ) const;
		void 		existing_connection( int sd );
		User 	*	create_user( void );
		//priv_fct - END}

		//priv_constructor{
		Server( void );
		//priv_constructor - END}

		//priv_var{
		int							_port;
		std::string					_pass;
		std::string					_oper_pass;
		struct addrinfo			*	_addrs;
		int 						_listener;
		int							_efd;
		struct epoll_event 			_ep_event[MAX_EVENTS];
		int							_nb_ev;
		struct sockaddr_storage 	_client_saddr;
		std::map<int, User *>     					users;
		char          								buffer[RECV_BUFF_SIZE];
		//priv_var - END}
};
#endif
