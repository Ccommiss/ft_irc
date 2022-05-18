/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:50:03 by csejault          #+#    #+#             */
/*   Updated: 2022/05/18 16:59:06 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//Class_Name = Server_tcp

//define{
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

//Max client nbr
# define MAX_EVENTS                10
//timeout for epoll wait in ms
//-1 for infinity
# define TIMEOUT                -1

//socket's queue size after what ECONNREFUSED ist return
# define BACKLOG                   10

#include <sys/epoll.h>


#include <stdexcept>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>

//for inet_top
#include <arpa/inet.h>
#include "cs_utils.hpp"
//define - END}

class	Server_tcp {

	public:
		//pub_constructor{
		Server_tcp( const char * port, const char *pass);
		Server_tcp( Server_tcp const & src );
		~Server_tcp( void );
		//pub_constructor - END}

		//pub_operator{
		Server_tcp &	operator=( Server_tcp const & rhs );
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
		//pub_fct - END}

		//pub_var{
		//pub_var - END}

	private:
		//priv_debug{
		//priv_debug - END}
		
		//priv_constructor{
		Server_tcp( void );
		//priv_constructor - END}

		//priv_static{
		//priv_static - END}

		//priv_var{
		int			_port;
		std::string	_pass;
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