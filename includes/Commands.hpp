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
		void leaveAllChans(Server &s, User *u);

/*
** in map 
*/

		void quit_s			(Server &s, User *u, std::vector<std::string> nick); // exit ou quit
		void setUser		(Server &s, User *u, std::vector<std::string> arg);
		void join			(Server &s, User *u, std::vector<std::string> arg);
		void priv_msg		(Server &s, User *u, std::vector<std::string> arg);
		void nick			(Server &s, User *u, std::vector<std::string> arg);
		void invite			(Server &s, User *u, std::vector<std::string> arg);
		void part			(Server &s, User *u, std::vector<std::string> arg) ; // par d'un chan 
		void topic			(Server &s, User *u, std::vector<std::string> arg);
		void mode			(Server &s, User *u, std::vector<std::string> arg);


		typedef void (Commands::*Cmd)(Server &s, User *user, std::vector<std::string> arg);
		std::map<std::string, Cmd> 		cmd_map;

		typedef std::string (*Rep)(User *user, void *arg);
		std::map<int, Rep> 	server_replies;
};


/*
**  Utils
*/
std::string trim(const std::string &s);
std::string ltrim(const std::string &s);
void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);





#endif