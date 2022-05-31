/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:50:03 by csejault          #+#    #+#             */
/*   Updated: 2022/05/31 15:39:21 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ //Class_Name = Server //define{
#ifndef SERVER_TCP_HPP
# define SERVER_TCP_HPP

# ifndef COL_GREEN
#  define COL_GREEN 		"\033[0;32m"
# endif
# ifndef COL_RED
#  define COL_RED		"\033[0;31m"
# endif
# ifndef COL_YELLOW
#  define COL_YELLOW		"\033[0;33m"
# endif
# ifndef COL_NORMAL
#  define COL_NORMAL		"\033[0m"
# endif

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
#include <string>

//for inet_top
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
		Server( Server const & src );
		~Server( void );
		//pub_constructor - END}

		//pub_operator{
		Server &	operator=( Server const & rhs );
		//pub_operator - END}

		//pub_debug{
		//pub_debug - END}

		//pub_static{
		//pub_static - END}

		//pub_getter{
		//pub_getter - END}

		//pub_setter{
		//pub_setter - END}

		//pub_exception{
		//pub_exception - END}

		//pub_fct{
		void	shutdown(bool does_throw);
		void	run( void );
		bool	pass_check( std::string to_check);

		void	printChans();
		void	printUsers();


		std::string     choose_msg(int code, User *u, std::string arg1, std::string arg2, std::string arg3);

		void 			numeric_reply(User *u, std::string code, std::string arg1, std::string arg2, std::string arg3);
		//pub_fct - END}

		//pub_var{
		std::map<int, User *>     					users;
		std::map<const std::string *, User *>	server_users; 
		std::map<std::string, Channel *>			chans;
		Commands                                	cmds; 

		char          				buffer[RECV_BUFF_SIZE];
		char        				hostname[HOSTNAME_SIZE];
		void						delete_user(User * to_del);

		bool 				chanExists(std::string chan_name);
		bool 				findByName(std::string nick, User **u);
		bool 				nicknameExists(std::string nick);



		//pub_var - END}

	private:
		//priv_debug{
		//priv_debug - END}

		//priv_fct{
		//out_loop
		void 	get_infos( void );
		void 	start_listening( void );
		void 	set_monitoring( void );

		//in_loop
		char	*	get_ip( void );
		void 		existing_connection( int sd );
		User 	*	create_user( void );


		//priv_fct - END}

		//priv_constructor{
		Server( void );
		//priv_constructor - END}

		//priv_static{
		//priv_static - END}

		//priv_var{
		int							_port;
		std::string					_pass;
		struct addrinfo			*	_addrs;
		int 						_listener;
		int							_efd;
		struct epoll_event 			_ep_event[MAX_EVENTS];
		int							_nb_ev;
		struct sockaddr_storage 	_client_saddr;
		//priv_var - END}
};

//out_class{
//std::ostream &	operator<<(std::ostream &os, Server_tcp &to_print);
//out_class - END}

#endif

//Color{
//The codes for foreground and background colours are:
//
//         foreground background
//black        30         40
//red          31         41
//green        32         42
//yellow       33         43
//blue         34         44
//magenta      35         45
//cyan         36         46
//white        37         47
//Color - END}
