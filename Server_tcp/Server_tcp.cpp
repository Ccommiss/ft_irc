/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:30:35 by csejault          #+#    #+#             */
/*   Updated: 2022/05/19 16:40:39 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//Class_Name = Server_tcp

#include "Server_tcp.hpp"

//debug{
//priv_debug{
//priv_debug - END}

//pub_debug{
//pub_debug - END}
//debug - END}

//pub_constructor{
Server_tcp::Server_tcp( const char * port, const char * pass ) : _port(strtol(port, NULL, 10)), _pass(pass), _addrs(NULL), _listener(-1), _ip(NULL), _nb_ev(0)
{
	if (_port < 1024 || _port > 65535)
		throw std::runtime_error("port not correct");
	//long int strtol (const char* str, char** endptr, int base);

	try
	{
		this->get_addr();
		this->start_listening();
		this->set_monitoring();
		while (1)
		{
			_ip = NULL;
			// monitor readfds for readiness for reading. if TIMEOUT = -1 == infinity
			// fill ep_event ???
			// return nb of evenements
			if (0 > (_nb_ev = epoll_wait (_efd, ep_event, MAX_EVENTS,  TIMEOUT)))
				throw std::runtime_error("epoll_wait failed");
			for (int i = 0; i < _nb_ev; i++)
			{
				if 	((ep_event[i].events & EPOLLIN) == EPOLLIN) // mask EPOLLIN event
				{
					if (ep_event [i].data.fd == _listener)
						this->new_connection();
					else
						this->existing_connection(ep_event[i]);
				}
			}

		}
	}
	catch ( std::exception &e )
	{
		if (this->_addrs)
			freeaddrinfo (_addrs);
		if (_listener >= 0 )
			close_fd(_listener, NO_THROW);
		for (int i = 0; i < _nb_ev; i++)
			close_fd((ep_event[i].data.fd), NO_THROW);
		throw e;
	}

}

Server_tcp::~Server_tcp( void ) {
}

Server_tcp::Server_tcp( Server_tcp const & src ) {
	*this = src;
}
//pub_constructor - END}

//pub_operator{
Server_tcp &	Server_tcp::operator=( Server_tcp const & rhs ) {
	if ( this != &rhs )
	{
		//this->VAR_TO_COPY = rhs.getVAR_TO_COPY();
	}
	return *this;
}
//pub_operator - END}

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

//priv_constructor{
//priv_constructor - END}

//priv_static{
//priv_static - END}

//priv_var{
//priv_var - END}


//out_class{
//out_class - END}