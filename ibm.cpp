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
#define SERVER_PORT  12345

#define TRUE             1
#define FALSE            0

#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp"

void parse_cmd(User &user, Server &s);

void check_connection(fd_set master_set, int listen_sd, int max_sd)
{
	for (int x = listen_sd; x <= max_sd + 1; x++)
	{
		if (FD_ISSET(x, &master_set) == 1 && x == listen_sd) // new_sd > max_sd))
			printf("Listening socket : %d is connected\n", x);
		else if (FD_ISSET(x, &master_set) == 1)
			printf("SD %d is connected\n", x);
		else
			std::cout << "SD " << x << "not set" << std::endl;
	}
}



int    main(int argc, char* argv[])
{

	Server     	s;
	User     	users[10]; // 10 user 

	while (s.end_server == 0)
	{
		memcpy(&s.working_set, &s.master_set, sizeof(s.master_set));
		int rc = select(s.max_sd + 1, &s.working_set, NULL, NULL, &s.timeout);
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
		for (int i = 0; i <= s.max_sd && s.desc_ready > 0; ++i)
		{
			if (FD_ISSET(i, &s.working_set))
			{
				s.desc_ready -= 1;
				if (i == s.listen_sd)
				{
					int new_sd = 0;
					new_sd = accept(s.listen_sd, NULL, NULL);
					if (new_sd < 0)
					{
							if (errno != EWOULDBLOCK)// ca c gere par le non blocking
							{
								perror("  accept() failed");
								s.end_server = TRUE;
							}
					}
					s.welcome_user(new_sd, users[new_sd]);
				}
				else
				{
					s.close_conn = FALSE;
					rc = recv(i, s.buffer, sizeof(s.buffer), 0);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("recv() failed");
							s.close_conn = TRUE;
						}
						break;
					}
					if (rc == 0)
					{
						printf("  Connection closed\n");
						s.close_conn = TRUE;
						break;
					}
					std::cout << users[i].nickname << " says : " << s.buffer;
					parse_cmd(users[i], s);
					bzero(s.buffer, 80);
					if (FD_ISSET(i, &s.master_set))
						rc = send(i, "Message recu !", 15, 0);
					if (rc < 0)
					{
						perror("  send() failed");
						s.close_conn = TRUE;
						break;
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