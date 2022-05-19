/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp_new_connection.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:02:09 by csejault          #+#    #+#             */
/*   Updated: 2022/05/19 12:15:22 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server_tcp.hpp"

void Server_tcp::new_connection( void )
{
	socklen_t addrlen = sizeof (struct sockaddr_storage);
	int fd_new;
	if (0 > (fd_new = accept (_listener, (struct sockaddr *) &client_saddr, &addrlen)))
		throw std::runtime_error("accept error");
	debug("New connection accepted : ", NOCR);
	// add fd_new to epoll for monitoring
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd_new;
	if (0 > epoll_ctl (_efd, EPOLL_CTL_ADD, fd_new, &ev))
		throw std::runtime_error("epoll_ctl socket add failed");

	// print IP address of the new client
	if (client_saddr.ss_family == AF_INET)
	{
		debug(inet_ntoa(((struct sockaddr_in *) &client_saddr)->sin_addr), NOCR);
		debug(" connected");
	}
	//TODO: find a way to print ipv6
	else if (client_saddr.ss_family == AF_INET6)
		debug(" ipv6 used(cannot convert)");
	else
		std::cerr << "Address family is neither AF_INET nor AF_INET6\n" << std::endl;
}
