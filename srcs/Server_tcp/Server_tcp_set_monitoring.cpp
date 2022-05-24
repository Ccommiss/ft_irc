/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp_set_monitoring.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:42:25 by csejault          #+#    #+#             */
/*   Updated: 2022/05/24 19:10:48 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
void Server::set_monitoring( void )
{
	//epoll_create creates a new epoll instance.
	//we can put flags instead of 0. Does it worth it?
	if ( 0 > (_efd = epoll_create1 (0)))
		throw std::runtime_error("epoll_create1 failed");

	debug(SV, "EFD = ", NOCR);
	debug(SV, _efd);
	//add listener to efd. Watch the event Epollin
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = _listener;
	if (0 > epoll_ctl (_efd, EPOLL_CTL_ADD, _listener, &ev))
		throw std::runtime_error("epoll_ctl listener add failed");
}
