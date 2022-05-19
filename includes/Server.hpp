
#include "User.hpp"
#include "Commands.hpp"
#include "Channel.hpp"
#include "Debug.hpp"




#ifndef SERVER_HPP
# define SERVER_HPP 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <numeric>



#define SERVER_PORT 6667


#define out(x) std::cout << x << std::endl;

class Channel;

class Server {

    public:
    int           on;
    int           listen_sd;
    int           max_sd; //va compter le nb de SD
    int           desc_ready, end_server; 
    int           close_conn;
    char          buffer[80];
    struct        sockaddr_in6   addr;
    struct        timeval       timeout;
    fd_set        master_set, working_set;

    std::map<std::string, Channel *>                          chans;
    std::map<const std::string *, const User *>           server_users; // sd et ref
    Commands                                cmds; 

    Server();
    Server &	operator=(Server const & rhs);

    void welcome_user(int sd, User &u);
    void quit_server(User &u);
    ~Server();
};

#endif