
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define SERVER_PORT  12345

#define out(x) std::cout << x << std::endl;

class Server {

    public:
    int    i, len, rc, on = 1;
    int    listen_sd;
    int    max_sd; //va compter le nb de SD 
    int    desc_ready, end_server = 0;
    int    close_conn;
    char   buffer[80];
    struct sockaddr_in6   addr;
    struct timeval       timeout;
    fd_set        master_set, working_set;



    Server() : max_sd(0)
    {
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

        int rc = ioctl(listen_sd, FIONBIO, (char*)&on);
        if (rc < 0)
        {
            perror("ioctl() failed");
            close(listen_sd);
            exit(-1);
        }
        out("Part 1 ok");


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

        FD_ZERO(&master_set); // initilize FD set 
        max_sd = listen_sd;
        FD_SET(listen_sd, &master_set);

        timeout.tv_sec = 10 * 60;
        timeout.tv_usec = 0;
    }

    ~Server() {}
};