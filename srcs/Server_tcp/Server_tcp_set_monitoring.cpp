/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp_set_monitoring.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:42:25 by csejault          #+#    #+#             */
/*   Updated: 2022/06/06 13:23:30 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
void Server::set_monitoring( void )
{
	/* epoll_create creates a new epoll instance. */ 
	if ( 0 > (_efd = epoll_create1 (0)))
		throw std::runtime_error("epoll_create1 failed");

	/* add listener to efd. Watch the event Epollin */
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = _listener;
	if (0 > epoll_ctl (_efd, EPOLL_CTL_ADD, _listener, &ev))
		throw std::runtime_error("epoll_ctl listener add failed");
}
