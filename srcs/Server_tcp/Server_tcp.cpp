/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:30:35 by csejault          #+#    #+#             */
/*   Updated: 2022/06/06 13:25:20 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

Server::Server( const char * port, const char * pass ) : _port(strtol(port, NULL, 10)), _pass(pass), _oper_pass(OPER_PASSWORD), _addrs(NULL), _listener(-1), _nb_ev(0)
{
	if (_port < 1024 || _port > 65535)
		throw std::runtime_error("port not correct");
	try
	{
		this->get_infos();
		this->start_listening();
		this->set_monitoring();
	}
	catch (std::exception &e)
	{
		std::cerr << "[SERVER] - Exception catched : " << e.what() << std::endl;
		shutdown(NO_THROW);
		throw e;
	}
	std::cout << "Server constructed with success" << std::endl;
	std::cout << std::left << std::setw(15) <<"Hostname : " << hostname << std::endl;
	std::cout << std::left << std::setw(15) <<"port : " << _port << std::endl;
}

Server::~Server( void ) {
	std::cout << "Server destroyed with success" << std::endl;
}

