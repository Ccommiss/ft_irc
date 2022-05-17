
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
- [<t> III. IRC Specs, commands and grammar </t>](#t-iii-irc-specs-commands-and-grammar-t)
  - [&emsp; <st> A. IRC definitions </st>](#-st-a-irc-definitions-st)
    - [Channels and operators](#channels-and-operators)
    - [Numeric replies[^1]](#numeric-replies1)
  - [&emsp; <st> C. Grammar</st>](#-st-c-grammarst)
    - [&emsp; 1. Study case 1 : User registration](#-1-study-case-1--user-registration)
    - [&emsp; 2. Study case 2 : Failing and server replies](#-2-study-case-2--failing-and-server-replies)

## <t> I. Introduction </t>

---

### &emsp; <st> A. IRC : history, definition </st>

- IRC : Internet Relay Chat
- Creation : 1988
- Initial documentation : [RFC 1459](https://www.rfcreader.com/#rfc1459)
- Current doc : RFC 2810, RFC 2812(client to server), RFC 2813 (server to server).
- Text-based protocol : encoded plain ASCII messgages.
- Message : 512 chars max, ended by CR-LF ("\r\n"), composed of command + command param (max : 15 params).


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

---
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

A socket is always defined by

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

## <t> III. IRC Specs, commands and grammar </t>

---

### &emsp; <st> A. IRC definitions </st>

#### Channels and operators

<def> Channel </def> : group of one or more client, implicitely created when first client joins. "Owned" by a channel operator.

Formatting :
```&chanel or #chanel```

- does not contain white space or comma.

- If there are multiple users on a server in the same
   channel, the message text is sent only once to that server and then
   sent to each client on the channel.

<def> Operators </def> : clients with special powers, eg. bam someone.

``` txt
KICK    - Eject a client from the channel
MODE    - Change the channel's mode
INVITE  - Invite a client to an invite-only channel (mode +i)
TOPIC   - Change the channel topic in a mode +t channel
```

Project steps

<https://celeo.github.io/2021/06/18/Implementing-an-IRC-server-from-scratch-part-1/>

#### Numeric replies[^1]

Server server communication :
:Name COMMAND parameter list

Must be formatted like :
``` :<nickname>@<username>!<hostname> <COMMAND> <arg>\r\n ```

Ex. Someone joins a server : greed him with a welcome message (rpl code n001).[^2]

**Exemple**:
> **Command**: NICK
   **Parameters**:```<nickname>```

=> Sent by client. When a user types in its client, this is how the client will format the request and send it to server. Thus, the server should be able to parse it accordingly.

### &emsp; <st> C. Grammar</st>

```txt
The Augmented BNF representation for this is:

    message    =  [ ":" prefix SPACE ] command [ params ] crlf
    prefix     =  servername / ( nickname [ [ "!" user ] "@" host ] )
    command    =  1*letter / 3digit
    params     =  *14( SPACE middle ) [ SPACE ":" trailing ]
               =/ 14( SPACE middle ) [ SPACE [ ":" ] trailing ]

    nospcrlfcl =  %x01-09 / %x0B-0C / %x0E-1F / %x21-39 / %x3B-FF
                    ; any octet except NUL, CR, LF, " " and ":"
    middle     =  nospcrlfcl *( ":" / nospcrlfcl )
    trailing   =  *( ":" / " " / nospcrlfcl )

    SPACE      =  %x20        ; space character
    crlf       =  %x0D %x0A   ; "carriage return" "linefeed"
```

Please refer to the glossary for further understanding of syntax.[^4]  

**What does it really mean ?**

- When a client (ex: IRSSI) sends the message, it pre-format it in order to be understood for the server. Clients also hide answer from server. This is not the case when simply using a TCP connection via Telnet.

- Thus, for exemple, to register to a server, one should provide at least two command : NICK and USER. These are directly set by client, acccordingly to settings (located in irssi.conf file, for example).
- But manually, we have to set it. Let us see how to connect via ```telnet irc.root-me.org 6667```

#### &emsp; 1. Study case 1 : User registration

<pre>
Trying 51.210.70.121...
Connected to irc.hackerzvoice.net.
Escape character is '^]'.
:irc.hackerzvoice.net NOTICE Auth :***Looking up your hostname...
:irc.hackerzvoice.net NOTICE Auth :*** Could not resolve your hostname: Domain name not found; using your IP address (62.210.34.103) instead.
NICK c
USER guest 0 * :Ronnie Reagan
:irc.hackerzvoice.net NOTICE Auth :Welcome to HackerzVoice!
:irc.hackerzvoice.net 001 c :Welcome to the HackerzVoice IRC Network c!guest@62.210.34.103
:irc.hackerzvoice.net 002 c :Your host is irc.hackerzvoice.net, running version InspIRCd-2.0
:irc.hackerzvoice.net 003 c :This server was created 19:52:09 Aug 12 2013
:irc.hackerzvoice.net 004 c irc.hackerzvoice.net InspIRCd-2.0 BHIRSWcghiorswx FLMNPRSYabcefhijklmnopqrstvz FLYabefhjkloqv
[...]
:c!guest@hzv-9qh.hrv.26em53.IP MODE c +x
</pre>

- Let us decompose step by step :
- **STEP 1 : CLIENT REQUEST** ```NICK c and USER guest 0 * :Ronnie Reagan``` : we complied to RFC for formatting requests to server for command NICK and USER, which are strictly necessary (while PASS command is optional)

- **STEP 2 : SERVER ANSWER** ```:irc.hackerzvoice.net 001 c :``` : this is the answer from the server. Not all commands request replies from server ; but for user registration, our current study case, this is mandatory.[^3] It complies to the BNF requirements seen above. Remember a message is formmated this way:     ```message    =  [ ":" prefix SPACE ] command [ params ] crlf```

  - ```:irc.hackerzvoice.net``` : servername (in macro prefix), tells the origin of a message.
  - `````` : numeric reply code (3 digits, in macro command). Stands for ```RPL WELCOME```.
  - ```c``` : my nick but I genuinely do not know which BNF standard it complies to, sorry.

- **STEP 2 : SERVER COMMAND** ```:c!guest@hzv-9qh.hrv.26em53.IP MODE c +x``` : another way if formatting with

  - ```:c!guest@hzv-9qh.hrv.26em53.IP``` as  ```nickname [ [ "!" user ] "@" host ]``` (prefix). This is the full client identifier ```<nick>!<user>@<host>```.

  - ```MODE``` as command
  - ```c +x``` as param.

#### &emsp; 2. Study case 2 : Failing and server replies

Following the first example, we are now trying to create a user with a nick that will be already in use.

``` txt
NICK amy
:bar.exemple.com 433 * amy :Nickname is already in use 
```

What does it mean ? Let's take a look back step by step.

- ```:bar.exemple.com``` prefix, servername.
- ```433```: numeric reply, code for ```ERR_NICKNAMEINUSE``` returned by NICK as mentionned in [RFC 2812](https://www.rfcreader.com/#rfc2812_line450)
- ```*``` : usually the nick name, but it could not be set, thus it is not written and replaced by a wildcard
- ```"<nick> :Nickname is already in use"``` i the formatted message for error 433 specified in RFC. 

**More info about replies formatting :**
<iframe
  src="http://chi.cs.uchicago.edu/chirc/irc_examples.html"
  style="width:100%; height:400px;"
></iframe>

**Other resources **  
list of commands : https://linux.developpez.com/formation_debian/irc.html

operators' level : https://wiki.mibbit.com/index.php/Channel_operator


[^1]: See <https://ircgod.com/posts/ircserver1/building-an-irc-server-1/>
[^2]: See <https://www.rfcreader.com/#rfc2812_line1943>
[^3]: See "3.1 Connection Registration", _RFC 2812_ , <https://www.rfcreader.com/#rfc2812_line411>
[^4]: Little glossary . Note: / stands for alternative, <   and > are for rul naming, *rule for repetiton, [rule] is optional.

