
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
		std::string	st = buffer;
		//debug(SV, "ASCII - CODE");
		//for (size_t i = 0; i < st.size(); i++)
		//{
		//	int a = st[i];
		//	std::cout << st[i] << "[" << a << "]" << std::endl;
		//}
		size_t old_pos;
		for (size_t pos = 0; users.count(sd) && pos < st.size();)
		{
			old_pos = pos;
			pos = st.find("\r\n", old_pos);
			if (pos == std::string::npos)
			{
				users[sd]->buffer.append(st.substr(old_pos));
				break;
			}
			else
			{
				users[sd]->buffer.append(st.substr(old_pos, pos - old_pos));
				cmds.parse_cmd(users[sd], *this);
				if (users.count(sd))
					users[sd]->buffer.clear();
				pos += 2;
			}
		}
		if (users.count(sd) && users[sd]->buffer.find("\r\n") != std::string::npos)
		{
			cmds.parse_cmd(users[sd], *this);
			if (users.count(sd))
				users[sd]->buffer.clear();
		}

		//debug(SV, users[sd]->nickname,NOCR);
		//debug(SV, " - BUFF_MAX_SIZE = ", NOCR);
		//debug(SV, sizeof(buffer), NOCR);
		//debug(SV, " - BYTES = ",NOCR);
		//debug(SV, numbytes,NOCR);
		//debug(SV, " - LEN = ",NOCR);
		//debug(SV, strlen(buffer), NOCR);
		//debug(SV, " - MESSAGE = ", NOCR);
		//debug(SV, buffer);
		//out (users[sd]->presentation()); 
	}
	out ("end existing conn waiting")
}
