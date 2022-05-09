


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

# define out(x) std::cout << x << std::endl; 


int main(int argc, char* argv[])
{
    int listen_sd, newsockfd, portno, nready;
    int rc, on = 1;
       struct timeval       timeout;
    fd_set        master_set, working_set;


    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    // create a socket
    // 

    /*
    **  Creates the listening socket.
    **  AF INET for ipv4
    **  socket(int domain, int type, int protocol)
    */
    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sd < 0)
    {
        out("ERROR opening socket");
        exit(1);
    }
    // socket qui va ecouter; 
    portno = 6667;
    out("SOCKET CREATED " << listen_sd)


        /*************************************************************/
        /* Allow socket descriptor to be reuseable                   */
        /*************************************************************/
        rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    if (rc < 0)
    {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }

    /*************************************************************/
    /* Set socket to be nonblocking. All of the sockets for      */
    /* the incoming connections will also be nonblocking since   */
    /* they will inherit that state from the listening socket.   */
    /*************************************************************/
    // rc = ioctl(listen_sd, FIONBIO, (char*)&on);
    // if (rc < 0)
    // {
    //     perror("ioctl() failed");
    //     close(listen_sd);
    //     exit(-1);
    // }


    /* setup the host_addr structure for use in bind call */
    // server byte order
    serv_addr.sin_family = AF_INET;

    // automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // convert short integer value for port must be converted into network byte order
    serv_addr.sin_port = htons(portno);


    if (bind(listen_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }

    out("BIND OK ");

    /*
    **  This listen() call tells the socket to listen to the incoming connections.
    **  The listen() function places all incoming connection into a backlog queue
    **  until accept() call accepts the connection.
    **  Here, we set the maximum size for the backlog queue to 5.
    */
    rc = listen(listen_sd, 5);

    out("Listening...");
    clilen = sizeof(cli_addr);


    FD_ZERO(&master_set);
   int max_sd = listen_sd;
   FD_SET(listen_sd, &master_set);

      /*************************************************************/
   /* Initialize the timeval struct to 3 minutes.  If no        */
   /* activity after 3 minutes this program will end.           */
   /*************************************************************/
   timeout.tv_sec  = 3 * 60;
   timeout.tv_usec = 0;


    newsockfd = accept(listen_sd, (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd < 0)
        std::cout << ("ERROR on accept");

    out("Acepted new connections...")
        std::cout << ("server: got connection from "); //<< (void)(cli_addr.sin_addr) << " PORT " << ntohs(cli_addr.sin_port));

    while (1)
    {



    }

}