/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp_start_listening.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:21:55 by csejault          #+#    #+#             */
/*   Updated: 2022/06/06 13:21:28 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::start_listening( void )
{
	/* Scan through the list of address structures returned by
	   getaddrinfo. Stop when the the socket and bind calls are successful. */
	   
	int  optval = 1;
	struct addrinfo *rptr;
	for (rptr = _addrs; rptr != NULL; rptr = rptr->ai_next) {
		/* create object socket */ 
		_listener = socket (rptr->ai_family, rptr->ai_socktype, rptr->ai_protocol);
		if (_listener == -1)
			continue;
		/* configure socket */
		else if (setsockopt (_listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int)) == -1)
			throw std::runtime_error("Setsockopt failed");
		/* bind the socket to an host::port */ 
		else if (!bind (_listener, rptr->ai_addr, rptr->ai_addrlen))  // Success
			break;
		else
			close_fd(_listener, THROW);
	}
	if (!rptr)
		throw std::runtime_error("Binding failed");


	/* Put the socker in a listening mod. Ready to reveive. 
		BACKLOG = socket's queue size after what ECONNREFUSED ist return */
	if (listen (_listener, BACKLOG) == -1)
		throw std::runtime_error("Listen failed");

}
