#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include "User.hpp"
#include "Debug.hpp"


class Server; 

class Commands
{

	public:
		Commands();
		// Commands(std::string name, User & creator);
		// Commands( Commands const & src );
		~Commands();

		void parse_cmd		(User *user, Server &s);
		void leaveAllChans(User *u);

/*
** in map 
*/

		void quit_s			(Server &s, User *u, std::vector<std::string> nick); // exit ou quit
		void setUser		(Server &s, User *u, std::vector<std::string> cmd);
		void join			(Server &s, User *u, std::vector<std::string> cmd);
		void priv_msg		(Server &s, User *u, std::vector<std::string> cmd);
		void nick			(Server &s, User *u, std::vector<std::string> cmd);
		void invite			(Server &s, User *u, std::vector<std::string> cmd);
		void part			(Server &s, User *u, std::vector<std::string> cmd) ; // par d'un chan 
		void topic			(Server &s, User *u, std::vector<std::string> cmd);
		void mode			(Server &s, User *u, std::vector<std::string> cmd);
		void kick			(Server &s, User *u, std::vector<std::string> cmd);

		typedef void (Commands::*Cmd)(Server &s, User *user, std::vector<std::string> cmd);
		std::map<std::string, Cmd> 		cmd_map;

		typedef std::string (*Rep)(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3);
		std::map<int, Rep> 	server_replies;
};


/*
**  Utils
*/
std::string trim(const std::string &s);
std::string ltrim(const std::string &s);
std::vector<std::string> tokenize(std::string const &str, const char delim);
std::string vecToString(std::vector<std::string> input);
std::string  implodeMessage(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);






#endif