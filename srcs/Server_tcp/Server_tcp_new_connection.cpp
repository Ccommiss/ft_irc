/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp_new_connection.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:02:09 by csejault          #+#    #+#             */
/*   Updated: 2022/05/20 17:56:02 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

User*	Server::create_user( int sd )
{
	User *new_user = new User(sd);
	users.insert(std::pair<int, User*>(sd,new_user));
	server_users.insert(std::pair<std::string *, User *>(&new_user->nickname, new_user));
	out ("Adding " << server_users.begin()->first << " with nick " << server_users.begin()->second->nickname <<" to database");
	return(new_user);
}

void Server::new_connection( void )
{
	socklen_t addrlen = sizeof (struct sockaddr_storage);
	int new_sd;
	User* new_user = NULL;
	if (0 > (new_sd = accept (_listener, (struct sockaddr *) &_client_saddr, &addrlen)))
		throw std::runtime_error("accept error");

	new_user = create_user(new_sd);
	debug(new_user  , NOCR);
	debug("(", NOCR);

	// print IP address of the new client
	if (_client_saddr.ss_family == AF_INET)
	{
		debug(get_ip(), NOCR);
	}
	else if (_client_saddr.ss_family == AF_INET6)
		debug(" ipv6 used(cannot convert)");
	else
		std::cerr << "Address family is neither AF_INET nor AF_INET6\n" << std::endl;
	debug(" joined the chat on socket ", NOCR);
	debug(new_sd);
	// add new_sd to epoll for monitoring
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = new_sd;
	if (0 > epoll_ctl (_efd, EPOLL_CTL_ADD, new_sd, &ev))
		throw std::runtime_error("epoll_ctl socket add failed");
}
