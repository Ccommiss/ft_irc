#include "Server.hpp"
#include "User.hpp"
#include <sstream>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() : max_sd(0), desc_ready(0), end_server(0), on(1)
{
    int rc = 0;
    listen_sd = socket(AF_INET6, SOCK_STREAM, 0);
    if (listen_sd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }
    if (setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0)
    {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }
    out ("ok")
    // int rc = ioctl(listen_sd, FIONBIO, (char*)&on);
    // if (rc < 0)
    // {
    //     perror("ioctl() failed");
    //     close(listen_sd);
    //     exit(-1);
    // }
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
    addr.sin6_port = htons(SERVER_PORT);
    rc = bind(listen_sd, (struct sockaddr*)&addr, sizeof(addr));
    if (rc < 0)
    {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }
    if (listen(listen_sd, 32) < 0)
    {
        perror("listen() failed");
        close(listen_sd);
        exit(-1);
    }
    out ("ok2")
    FD_ZERO(&master_set); // initilize FD set 
    max_sd = listen_sd;
    FD_SET(listen_sd, &master_set);
    timeout.tv_sec = 10 * 60;
    timeout.tv_usec = 0;
}

// Server::Server( const Server & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
    
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Server &				Server::operator=( Server const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

void                    Server::welcome_user(int new_sd, User &u)
{
    std::stringstream ss;
	ss << new_sd;
	std::string str = ss.str();
    if (u.nickname == "Guest")
	    u.nickname += str;
	u.socket_descriptor = new_sd;
	if (new_sd > max_sd)
		max_sd = new_sd;
    FD_SET(u.socket_descriptor, &master_set);  // add new SD to master set 
	out(u.nickname << " joined the chat !"); 
}


void                    Server::quit_server(User &u)
{
    close_conn = 1;
    out(u.nickname << " has left the chat");
    close(u.socket_descriptor);
    FD_CLR(u.socket_descriptor, &master_set);
    if (u.socket_descriptor == max_sd)
    {
    	while (FD_ISSET(max_sd, &master_set) == 0)
    		max_sd -= 1;
    }
}

//command 

// void                      Server::list(std::string s)
// {

// }


std::ostream &			operator<<( std::ostream & o, Server const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */