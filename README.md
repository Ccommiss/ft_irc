

# ft_irc 

_Make your own Internet Relay Chat_ 

- [ft_irc](#ft_irc)
    - [Introduction](#introduction)
      - [General architecture of IRC protocol : described as a "network of networks" base on client server model.](#general-architecture-of-irc-protocol--described-as-a-network-of-networks-base-on-client-server-model)
        - [Server](#server)
        - [Client](#client)
      - [TCP protocol and socket programming](#tcp-protocol-and-socket-programming)
        - [What is a socket ?](#what-is-a-socket-)
        - [Netcat tool](#netcat-tool)
      - [IRC Commands and grammar :](#irc-commands-and-grammar-)
  - [Building the server](#building-the-server)


### Introduction

- IRC : Internet Relay Chat
- Creation : 1988 
- Initial documentation : [RFC 1459](https://www.rfcreader.com/#rfc1459)


#### General architecture of IRC protocol : described as a "network of networks" base on client server model. 


- Main principle : client-server model. 
  

##### Server

Schema from RFC 1459:


```


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



##### Client 

- Definition : anything connected to server which is not a server. Defined by :
  - a unique nick name of 9 char
  - Hostname
  - Server on which client is connected 


``` 


                          1--\
                              A        D---4
                          2--/ \      /
                                B----C
                               /      \
                              3        E

   Servers: A, B, C, D, E         Clients: 1, 2, 3, 4

                    [ Fig. 2. Sample small IRC network ]
``` 


#### TCP protocol and socket programming 

http://www.lsv.fr/~rodrigue/teach/npp/2012/tp1.pdf 


##### What is a socket ?

##### Netcat tool

Definition : tool establishing connections using TCP/UDP tranor protocol. Copies ata coming through STDOUT and wrtites in STDIN. 

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
https://oramind.com/tutorial-how-to-make-an-irc-server-connection/ 

#### IRC Commands and grammar : 

- Always formatted as ``` /command ```.



- See more examples : [wiki](https://fr.wikipedia.org/wiki/Aide:IRC/commandes)

```
      Client               Server
    ┌─────────┐         ┌─────────┐
    │socket() │         │socket() │
    └───┬─────┘         ├─────────┤
        │               ├────▼────┤
        │               │ bind()  │
        │               ├─────────┤
        │               ├────▼────┤
        │               │ listen()│
        │               ├─────────┤
        │               ├────▼────┤
        │               │ accept()│
   ┌────▼────┐          └────┬────┘
   │connect()│               │
   ├─────────┤               │
   ├────▼────┤          ┌────▼────┐
┌─►│ write() ├─────────►│ read()  │◄─┐
│  ├─────────┤          ├─────────┤  │
│  ├────▼────┤          ├────▼────┤  │
└──┤ read()  │◄─────────┤ write() ├──┘
   ├─────────┤          ├────┬────┘
   ├────▼────┼──────────┼┼┼┤►│
   │ close() │          ├────▼────┐
   └─────────┤          │         │
        ◄────┴──────────┴─────────┘
```



connection closure

accept()
listen()
read()
write(
connect()
write()
read()
close()
socket()
close()
Client Server
3-way handshaking
data
data
connection closure
bind()
accept()
listen()
read()
write()

```

## Building the server 

The server will accept connections at a given port. We need to:
1. First, create a socket with the **socket** system call.
2. We then **bind** the socket to an address and port.
3. Finally we **listen** on the new socket














Project steps 

https://celeo.github.io/2021/06/18/Implementing-an-IRC-server-from-scratch-part-1/ 


- 