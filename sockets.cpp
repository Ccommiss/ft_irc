


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

# define out(x) std::cout << x << std::endl; 


int main(int argc, char* argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    // create a socket
    // socket(int domain, int type, int protocol)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        std::cout << ("ERROR opening socket");
    // socket qui va ecouter; 
    portno = 6667;
    out("SOCKET CREATED " << sockfd)


        /* setup the host_addr structure for use in bind call */
        // server byte order
    serv_addr.sin_family = AF_INET;

    // automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // convert short integer value for port must be converted into network byte order
    serv_addr.sin_port = htons(portno);


    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        std::cout << ("ERROR on binding");

        out("BIND OK ")
 
    // This listen() call tells the socket to listen to the incoming connections.
    // The listen() function places all incoming connection into a backlog queue
    // until accept() call accepts the connection.
    // Here, we set the maximum size for the backlog queue to 5.
    listen(sockfd, 5);

    out("Listening...")
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd < 0)
        std::cout << ("ERROR on accept");

    out("Acepted new connections...")
    std::cout << ("server: got connection from "); //<< (void)(cli_addr.sin_addr) << " PORT " << ntohs(cli_addr.sin_port));

    while (1)
    {
        
        read(1, buffer, 255);
        send(newsockfd, buffer, strlen(buffer), 0);
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            out("ERROR reading from socket");
        out("User : " << buffer);
        bzero(buffer, 256);
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
