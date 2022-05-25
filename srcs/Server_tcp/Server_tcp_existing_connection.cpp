
#include "Server.hpp"

void Server::existing_connection( int sd )
{

	memset (&buffer, '\0', sizeof (buffer));
	ssize_t numbytes = recv (sd, &buffer, sizeof (buffer), 0);

	if (numbytes == -1) //failed
		throw std::runtime_error("Recv Failed");
	else if (numbytes == 0) // connection closed by client
		delete_user(users[sd]);
	else //do_action
	{
		debug(SV, users[sd]->nickname,NOCR);
		debug(SV, " - BUFF_MAX_SIZE = ", NOCR);
		debug(SV, sizeof(buffer), NOCR);
		debug(SV, " - BYTES = ",NOCR);
		debug(SV, numbytes,NOCR);
		debug(SV, " - LEN = ",NOCR);
		debug(SV, strlen(buffer), NOCR);
		debug(SV, " - MESSAGE = ", NOCR);
		debug(SV, buffer);
		cmds.parse_cmd(users[sd], *this);
	}
}
