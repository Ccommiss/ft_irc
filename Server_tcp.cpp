/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:30:35 by csejault          #+#    #+#             */
/*   Updated: 2022/05/18 17:06:35 by csejault         ###   ########.fr       */
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
Server_tcp::Server_tcp( const char * port, const char * pass ) : _port(strtol(port, NULL, 10)), _pass(pass)
{
	if (_port < 1024 || _port > 65535)
		throw std::runtime_error("port not correct");
	//long int strtol (const char* str, char** endptr, int base);

	struct message
	{
		std::string data;
	} recv_message;
	//L'argument hints pointe sur une structure addrinfo qui spécifie les critères de sélection des structures d'adresses de sockets renvoyée dans la liste pointé par res. Si hints n'est pas NULL, il doit pointer sur une structure addrinfo dont les membres ai_family, ai_socktype, et ai_protocol indiquent les critères limitant l'ensemble d'adresses de sockets renvoyées par getaddrinfo(), de la façon suivante 
	//ai_family
	//Ce champ indique la famille d'adresse désirée des adresses renvoyées. Les valeurs valides de ce champ inclus AF_INET et AF_INET6. La valeur AF_UNSPEC indique que getaddrinfo() doit renvoyer les adresses de socket de n'importe quelle famille d'adresses (par exemple, IPv4 ou IPv6) pouvant être utilisées avec node et service.
	//ai_socktype
	//Ce champ indique le type préféré de socket, par exemple SOCK_STREAM ou SOCK_DGRAM. Mettre 0 dans ce champ indique que getaddrinfo() peut renvoyer n'importe quel type d'adresses de socket.
	//ai_protocol
	//Ce champ indique le protocole des adresses de socket renvoyées. Mettre 0 dans ce champ indique que getaddrinfo() peut renvoyer des adresses de socket de n'importe quel type.
	//ai_flags
	//Ce champ indique des options supplémentaires, décrites plus loin. Divers attributs sont regroupés par un OU binaire.

	//http://manpagesfr.free.fr/man/man3/getaddrinfo.3.html
	struct addrinfo hints;
	memset(&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Stream socket */
	hints.ai_flags = AI_PASSIVE;    /* for wildcard IP address */

	struct addrinfo *result;
	//getaddrinfo recupere une structure contenant les info d'une adress et d'un port et les tocks dans results
	//utilise les criteres de selection defini dans hints.
	//La fonction getaddrinfo() alloue et initialise une liste chaînée de structures addrinfo, une pour chaque adresse réseau correspondant à node et service, soumise aux restrictions imposées par l'argument hints, et renvoie dans res un pointeur sur le début de la liste. Les éléments de la liste chaînée sont chaînés par le champ ai_next. Il y a plusieurs raisons pour lesquelles la liste chaînée peut avoir plus d'une structure addrinfo : l'hôte réseau est « multi-homed » ; le même service est disponible à partir de plusieurs protocoles de socket (par exemple, un est d'adresse SOCK_STREAM et l'autre d'adresse SOCK_DGRAM).
	//La fonction freeaddrinfo() libère la mémoire qui a été allouée dynamiquement pour la liste chaînée res.   
	int ret = getaddrinfo (NULL, (to_str(_port)).c_str(), &hints, &result);
	if (ret)
		throw std::runtime_error("getaddr info failed");


	/* Scan through the list of address structures returned by
	   getaddrinfo. Stop when the the socket and bind calls are successful. */

	//https://www.tala-informatique.fr/wiki/index.php/C_socket
	int listener = -1;
	int  optval = 1;
	struct addrinfo *rptr;
	for (rptr = result; rptr != NULL; rptr = rptr->ai_next) {
		//create object socket
		listener = socket (rptr->ai_family, rptr->ai_socktype, rptr->ai_protocol);
		if (listener == -1)
			continue;
		// configure socket
		else if (setsockopt (listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int)) == -1)
			throw std::runtime_error("Setsockopt failed");
		//if (0 > ioctl(listen_sd, FIONBIO, (char*)&on))
		//{
		//	close(listen_sd);
		//	throw ("ioctl() failed");
		//}
		// bind the socket to an host::port
		else if (!bind (listener, rptr->ai_addr, rptr->ai_addrlen))  // Success
			break;
		else if (close (listener) == -1)
			throw std::runtime_error("Closing listener failed");
	}
	if (!rptr)
		throw std::runtime_error("Binding failed");

	//TODO: Put this in a try catch if before fct failed
	freeaddrinfo (result);

	//Put the socker in a listening mod. Ready to reveive. 
	//BACKLOG = socket's queue size after what ECONNREFUSED ist return
	if (listen (listener, BACKLOG) == -1)
		throw std::runtime_error("Listen failed");

	//epoll_create creates a new epoll instance.
	//we can put flags instead of 0. Does it worth it?
	int efd = 0;
	if ( 0 > (efd = epoll_create1 (0)))
		throw std::runtime_error("epoll_create1 failed");

	//add listener to efd. Watch the event Epollin
	struct epoll_event ev;
	struct epoll_event ep_event[MAX_EVENTS];
	ev.events = EPOLLIN;
	ev.data.fd = listener;
	if (0 > epoll_ctl (efd, EPOLL_CTL_ADD, listener, &ev))
		throw std::runtime_error("epoll_ctl listener add failed");


	//nombre d evendement
	int nfds = 0;
	socklen_t addrlen;
	struct sockaddr_storage client_saddr;
	char *ip;
	//struct tnode *root = NULL;

	while (1)
	{
		ip = NULL;
		// monitor readfds for readiness for reading. if TIMEOUT = -1 == infinity
		// fill ep_event ???
		// return nb of evenements
		if (0 > (nfds = epoll_wait (efd, ep_event, MAX_EVENTS,  TIMEOUT)))
			throw std::runtime_error("epoll_wait failed");
		for (int i = 0; i < nfds; i++)
		{
			if 	((ep_event[i].events & EPOLLIN) == EPOLLIN) // mask EPOLLIN event
			{
				if (ep_event [i].data.fd == listener) {  // request for new connection
					addrlen = sizeof (struct sockaddr_storage);
					int fd_new;
					if (0 > (fd_new = accept (listener, (struct sockaddr *) &client_saddr, &addrlen)))
						throw std::runtime_error("accept error");
					else
						debug("New connection accepted : ", NOCR);
					// add fd_new to epoll for monitoring
					ev.events = EPOLLIN;
					ev.data.fd = fd_new;
					if (0 > epoll_ctl (efd, EPOLL_CTL_ADD, fd_new, &ev))
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
				else  // data from an existing connection, receive it
				{
					memset (&recv_message, '\0', sizeof (struct message));
					ssize_t numbytes = recv (ep_event[i].data.fd, &recv_message, sizeof (struct message), 0);

					if (numbytes == -1)
						throw std::runtime_error("Recv Failed");
					else if (numbytes == 0)
					{
						// connection closed by client
						debug("socket ", false);
						debug(ep_event[i].data.fd, false);
						debug(" closed by client");

						// delete fd from epoll
						if (epoll_ctl (efd, EPOLL_CTL_DEL, ep_event [i].data.fd, &ev) == -1)
							throw std::runtime_error("epoll_ctl socket del failed");
						if (0 > close (ep_event [i].data.fd))
							throw std::runtime_error("Close socket failed");
					}
					else
					{
						debug("receved data to process");
					}
				}
			}
		}

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
