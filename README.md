
<style>
t { color: Black; font-family:courier; font-style:bold; text-decoration: underline; }
st {
    color: #303030; font-family:Futara; font-style:bold; text-decoration: underline;
}
r { color: Red }
o { color: Orange }
g { color: Green }
def { font-family:courier;  background-color: #9999ff; font-style: bold }
</style>

<h1> ft_irc </h1>

_Make your own Internet Relay Chat_

- [<t> I. Introduction </t>](#t-i-introduction-t)
  - [&emsp; <st> A. IRC : history, definition </st>](#-st-a-irc--history-definition-st)
  - [&emsp; <st> B. General architecture of IRC protocol : described as a "network of networks" base on client server model </st>](#-st-b-general-architecture-of-irc-protocol--described-as-a-network-of-networks-base-on-client-server-model-st)
    - [&emsp;&emsp;a) Server](#a-server)
    - [&emsp;&emsp;b) Client](#b-client)
- [<t> II. TCP protocol and socket programming </t>](#t-ii-tcp-protocol-and-socket-programming-t)
  - [&emsp; <st> A. What is a socket ? </st>](#-st-a-what-is-a-socket--st)
    - [AF_INET](#af_inet)
  - [&emsp; <st> B. Netcat tool </st>](#-st-b-netcat-tool-st)
- [<t> III. IRC Commands and grammar </t>](#t-iii-irc-commands-and-grammar-t)

## <t> I. Introduction </t>

### &emsp; <st> A. IRC : history, definition </st>

- IRC : Internet Relay Chat
- Creation : 1988
- Initial documentation : [RFC 1459](https://www.rfcreader.com/#rfc1459)

### &emsp; <st> B. General architecture of IRC protocol : described as a "network of networks" base on client server model </st>

- Main principle :  client-server model.

[doc](https://www.bogotobogo.com/cplusplus/sockets_server_client.php)
    A client app send a request to a server app.
    The server app returns a reply.
    Some of the basic data communications between client and server are:
        File transfer - sends name and gets a file.
        Web page - sends url and gets a page.
        Echo - sends a message and gets it back.

#### &emsp;&emsp;a) Server

Schema from RFC 1459:

``` txt


                           [ Server 15 ]  [ Server 13 ] [ Server 14]
                                 /                \         /
                                /                  \       /
        [ Server 11 ] ------ [ Server 1 ]       [ Server 12]
                              /        \          /
                             /          \        /
                  [ Server 2 ]          [ Server 3 ]
                    /       \                      \
                   /         \                      \
           [ Server 4 ]    [ Server 5 ]         [ Server 6 ]
            /    |    \                           /
           /     |     \                         /
          /      |      \____                   /
         /       |           \                 /
 [ Server 7 ] [ Server 8 ] [ Server 9 ]   [ Server 10 ]

                                  :
                               [ etc. ]
                                  :

                 [ Fig. 1. Format of IRC server network ]
```

#### &emsp;&emsp;b) Client

- <def>**Definition** </def> : anything connected to server which is not a server. Defined by :
  - a unique nick name of 9 char
  - Hostname
  - Server on which client is connected

``` txt


                          1--\
                              A        D---4
                          2--/ \      /
                                B----C
                               /      \
                              3        E

   Servers: A, B, C, D, E         Clients: 1, 2, 3, 4

                    [ Fig. 2. Sample small IRC network ]
```

## <t> II. TCP protocol and socket programming </t>

<http://www.lsv.fr/~rodrigue/teach/npp/2012/tp1.pdf>

### &emsp; <st> A. What is a socket ? </st>

IBM docs

<def>**Definition** </def>: sort of endpoint in a 2-ways communication channel. Structur and properties are defined by an Application Programming Interface.

Socket are used to create a communication channel, used to send data between two users.

Analogy with a phone :

- Dialing a number = starting a socket call.
  
  When a socket() is needed, sytem returns an integer which is a sd, a socket descriptor. It is similar as file descriptor. But one main difference is : the OS actually binds FD to the file when open() is called, whereas for socket, applications can choose between specify the dest each time they use the socket (if datagrams) OR bind a dest address to the socket.

Unix socket ?

- Local sockets (AF_UNIX) : provide comm between processes on a single system
- Internet Protocol Sockets part og Internet Address Family (AF_INET for ipv4) : provide means of communicating between applications on different system via Transport Control Protocol.

A soket is always defined by

- its family (UNIX or INET)
- its communication mode (datagram or stream, SOCK_DGRAM and SOCK STREAM)
- a protocol (0 :automatic choice)

#### AF_INET

**From [IBM](https://www.ibm.com/docs/en/zos/2.4.0?topic=SSLTBW_2.4.0/com.ibm.zos.v2r4.cbcpx01/adintrn.htm) doc :**

>A socket address in the Internet address family comprises the following fields: the address family (AF_INET), an Internet address, the length of that Internet address, a port, and a character array. The structure of the Internet socket address is defined by the following sockaddr_in structure, which is found in the netinet/in.h include file:

```
 struct in_addr {
     ip_addr_t s_addr;

 struct sockaddr_in {
     unsigned char  sin_len;
     unsigned char  sin_family;
     unsigned short sin_port;
     struct in_addr sin_addr;
     unsigned char  sin_zero[8];
};
```

### &emsp; <st> B. Netcat tool </st>

<def>**Definition** </def> tool establishing connections using TCP/UDP tranor protocol. Copies ata coming through STDOUT and wrtites in STDIN.

Open a connection to the port of host :
``` nc HOST PORT ```

Host : IP address or machine name (resolved as an IP address by DNS)

We can also use netcat as a TCP server listening for connections againt ip address. Syntax becomes :
``` nc -l ADDR PORT ```

Addr = binding address.
In this case : netcat wait for a SINGLE incoming connection.

Example :
nc -l 1234
-> port 1234 on localhost is a server. Returns on terminal a GET request.

BSD scokets
<https://oramind.com/tutorial-how-to-make-an-irc-server-connection/>

- See more examples : [wiki](https://fr.wikipedia.org/wiki/Aide:IRC/commandes)

```
      Client              Server
    ┌─────────┐         ┌─────────┐
    │socket() │         │socket() │ => Initial creation of socket 
    └───┬─────┘         ├─────────┤
        │               ├────▼────┤
        │               │ bind()  │ => bindin to service point (IP + port) where client will connect 
        │               ├─────────┤
        │               ├────▼────┤
        │               │ listen()│ => socket set as listening socket 
        │               ├─────────┤
        │               ├────▼────┤
        │               │ accept()│ => new data socket
   ┌────▼────┐          └────┬────┘
   │connect()│──────────────►│
   ├─────────┤               │
   ├────▼────┤   data   ┌────▼────┐
┌─►│ write() ├─────────►│ read()  │◄─┐
│  ├─────────┤          ├─────────┤  │
│  ├────▼────┤   data   ├────▼────┤  │
└──┤ read()  │◄─────────┤ write() ├──┘
   ├─────────┤          ├────┬────┘
   ├────▼────┼──────────────►│
   │ close() │  conn.   ├────▼────┐
   └─────────┤ closure  │ close() │
        ◄────┴──────────┴─────────┘


Initiation, handling, and termination of a TCP stream 
CC-BY

```

**Useful functions :**

**Socket()** : creation of a socket, have to specify it is a internet protocol (AF_INET) and TCP stream (SOCK_STREAM).

---> Server socket : is listening. Will be use to derive new data socket, which means, no data will be transmitted.

**setsockopt()** : set the socket options.

**Bind()** : binds a name to a socket. After  cause to soecket(),
> assigns the address specified by addr to the socket referred to
> by the file descriptor sockfd.

```Example : bind(listen_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))```
with serv address an instance of ```struct sockaddr_in```

**Accept()** : accepts a connection on a socket. Server waits fo client to executes "connect". Will then generates a new data socket which will be used to transmit data. It will extracts the irst connection  request and returns a fd.
=> The new socket is NOT on listening state, and original sockfd is not affected.

``` int accept(int sockfd, struct sockaddr *restrict addr,  socklen_t*restrict addrlen); ```

```newsockfd = accept(listen_sd, (struct sockaddr*)&cli_addr, &clilen);```
With new sockfd = the new client, listen_sd as listening socket, cli addr (also aan instance of struct sockaddr_in and cli len as size of new cli.

**Connect()** : initiate a connection a socket.

``` int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); ```

**recv()** : The recv() calls are used to receive messages from a socket.  They may be used to receive data on both connectionless and connection-oriented sockets.
```ssize_t recv(int sockfd, void *buf, size_t len, int flags);```

**select()** :  select() allows a program to monitor multiple file descriptors,
waiting until one or more of the file descriptors become "ready"
for some class of I/O operation (e.g., input possible).  A file
descriptor is considered ready if it is possible to perform a
corresponding I/O operation (e.g., read(2), or a sufficiently
small write(2)) without blocking.
Prototype : ```int select(int nfds, fd_set *restrict readfds, fd_set*restrict writefds, fd_set *restrict exceptfds, struct timeval*restrict timeout);```

```rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);```
- rc is an int;
- nfds = max_sd = highest FD. + 1.
- readfds = The file descriptors in this set are watched to see if they are ready for reading.  A file descriptor is ready for reading if a read operation will not block;
- writefds = fd set are watched to see if they are ready for writing. A file descriptor is ready for writing if a write operation will not block.  However, even if a file descriptor indicates as writable, a large write may still block.
- exceptfds = this set are watched for "exceptional conditions".

**What is a set ?**
=> type fd_set : allows caller to wait for three classes of events on specified set of fds (read, write, except).

Contains the following macro features :

- FD_ZERO() : clears (removes all file descriptors from) set. It should be employed as the first step in initializing a file descriptor set
- FD_SET(): adds the file descriptor fd to set.
- FD_CLR() : removes the file descriptor fd from set.
- FD_ISSET() : select() modifies the contents of the sets according to the rules described below.  After calling select(), the FD_ISSET() macro can be used to test if a file descriptor is still present in a set.

- 

## <t> III. IRC Commands and grammar </t>

- Always formatted as ``` /command ```.

Project steps

<https://celeo.github.io/2021/06/18/Implementing-an-IRC-server-from-scratch-part-1/>

-
