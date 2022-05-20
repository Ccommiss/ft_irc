/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_tcp_get_addr.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:07:57 by csejault          #+#    #+#             */
/*   Updated: 2022/05/20 16:21:43 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
void Server::get_addr( void )
{
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

	//getaddrinfo recupere une structure contenant les info d'une adress et d'un port et les tocks dans results
	//utilise les criteres de selection defini dans hints.
	//La fonction getaddrinfo() alloue et initialise une liste chaînée de structures addrinfo, une pour chaque adresse réseau correspondant à node et service, soumise aux restrictions imposées par l'argument hints, et renvoie dans res un pointeur sur le début de la liste. Les éléments de la liste chaînée sont chaînés par le champ ai_next. Il y a plusieurs raisons pour lesquelles la liste chaînée peut avoir plus d'une structure addrinfo : l'hôte réseau est « multi-homed » ; le même service est disponible à partir de plusieurs protocoles de socket (par exemple, un est d'adresse SOCK_STREAM et l'autre d'adresse SOCK_DGRAM).
	//La fonction freeaddrinfo() libère la mémoire qui a été allouée dynamiquement pour la liste chaînée res.   
	int ret = getaddrinfo (NULL, (to_str(_port)).c_str(), &hints, &_addrs);
	if (ret)
		throw std::runtime_error("getaddr info failed");
}
