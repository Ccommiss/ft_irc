/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:30:35 by csejault          #+#    #+#             */
/*   Updated: 2022/05/24 16:47:25 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//Class_Name = Server

#include "Server.hpp"

//debug{
//priv_debug{
//priv_debug - END}

//pub_debug{
//pub_debug - END}
//debug - END}

//pub_constructor{
Server::Server( const char * port, const char * pass ) : _port(strtol(port, NULL, 10)), _pass(pass), _addrs(NULL), _listener(-1), _nb_ev(0)
{
	if (_port < 1024 || _port > 65535)
		throw std::runtime_error("port not correct");
	//long int strtol (const char* str, char** endptr, int base);

	try
	{
		this->get_addr();
		this->start_listening();
		this->set_monitoring();
	}
	catch (std::exception &e)
	{
		std::cerr << "[SERVER] - Exception catched : " << e.what() << std::endl;
		shutdown(NO_THROW);
		throw e;
	}

}

Server::~Server( void ) {
}

Server::Server( Server const & src ) {
	*this = src;
}
//pub_constructor - END}

//pub_operator{
Server &	Server::operator=( Server const & rhs ) {
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
