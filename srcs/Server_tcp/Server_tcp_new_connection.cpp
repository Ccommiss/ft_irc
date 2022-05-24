/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp_new_connection.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:02:09 by csejault          #+#    #+#             */
/*   Updated: 2022/05/24 16:37:11 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

void Server::new_connection( void )
{
	socklen_t addrlen = sizeof (struct sockaddr_storage);
	int new_sd;
	User* new_user = NULL;
	if (0 > (new_sd = accept (_listener, (struct sockaddr *) &_client_saddr, &addrlen)))
		throw std::runtime_error("accept error");

	new_user = create_user(new_sd);
	debug(SV, new_user  , NOCR);
	debug(SV, "(", NOCR);

	// print IP address of the new client
	if (_client_saddr.ss_family == AF_INET)
	{
		debug(SV, get_ip(), NOCR);
	}
	else if (_client_saddr.ss_family == AF_INET6)
		debug(SV, " ipv6 used(cannot convert)");
	else
		std::cerr << "Address family is neither AF_INET nor AF_INET6\n" << std::endl;
	debug(SV, " joined the chat on socket ", NOCR);
	debug(SV, new_sd);
	// add new_sd to epoll for monitoring
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = new_sd;
	if (0 > epoll_ctl (_efd, EPOLL_CTL_ADD, new_sd, &ev))
		throw std::runtime_error("epoll_ctl socket add failed");
}
