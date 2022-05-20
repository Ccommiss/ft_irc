#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#define SERVER_PORT  6667

#define TRUE             1
#define FALSE            0

#include "Commands.hpp"
#include "Server.hpp"
#include "User.hpp"



/*
**	All credits to : 
**	https://www.ibm.com/docs/en/i/7.1?topic=designs-example-nonblocking-io-select  
*/
int    main()
{

	Server     	s;
	std::map<int, User *>     	users;


	while (s.end_server == 0)
	{
		bzero(s.buffer, 80);
		memcpy(&s.working_set, &s.master_set, sizeof(s.master_set));
		int rc = select(s.max_sd + 1, &s.working_set, NULL, NULL, &s.timeout);
		out ("Waiting")
		if (rc < 0)
		{
			perror("select() failed");
			break;
		}
		if (rc == 0) // timeout 
		{
			printf("select() timed out. End program.\n");
			break;
		}
		s.desc_ready = rc; // descriptor ready 
		// we have to see step by step, 
		// after return socme sockets are ready
		out ("RC" << s.desc_ready)
		for (int i = 0; i <= s.max_sd && s.desc_ready > 0; ++i)
		{
			if (FD_ISSET(i, &s.working_set))
			{
				s.desc_ready -= 1;
				// means it is a connection request 
				if (i == s.listen_sd)
				{
					int new_sd = 0;
					out ("before accept");

					new_sd = accept(s.listen_sd, NULL, NULL);
					// accetpted 
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  accept() failed");
							s.end_server = TRUE;
						}
					}
					// See Server
					User *new_user = new User(new_sd);
					users.insert(std::pair<int, User*>(new_sd,new_user));
					s.welcome_user(new_sd, new_user);
				}
				else // we are receiving 
				{
					out ("receiving data");
					s.close_conn = FALSE;
					rc = recv(i, s.buffer, 80, 0);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("recv() failed");
							s.close_conn = TRUE;
						}
						break;
					}
					if (rc == 0) // 0 bytes, it closed 
					{
						printf("Connection closed\n");
						s.close_conn = TRUE;
						out (i);
						out (s.listen_sd)
						out (s.end_server);
						if (FD_ISSET(i, &s.master_set))
							close(i);
						if (i == s.max_sd)
							s.max_sd -= 1;
						//break;
					}
					else 
					{
						out ("there");
					//std::string res = users[i].nickname << " says : " << s.buffer;
					std::cout << users[i]->nickname << " says : " << s.buffer;
					//echo back 
					s.cmds.parse_cmd(users[i], s);
					bzero(s.buffer, 80);
					}
	
			
				} /* End of existing connection is readable */
			} /* End of if (FD_ISSET(i, &working_set)) */
		} /* End of loop through selectable descriptors */
	}
	for (int i = 0; i <= s.max_sd; ++i)
	{
		if (FD_ISSET(i, &s.master_set))
			close(i);
	}
}