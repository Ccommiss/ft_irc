#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <list>
#include "User.hpp"
#include "Debug.hpp"


class Server;

class Commands
{

	public:
		Commands();
		~Commands();

		void parse_cmd		(User *user, Server &s);
		void leaveAllChans(User *u);

/*
** in map
*/

		void quit_s			(Server &s, User *u, std::vector<std::string> nick);
		void setUser		(Server &s, User *u, std::vector<std::string> cmd);
		void join			(Server &s, User *u, std::vector<std::string> cmd);
		void priv_msg		(Server &s, User *u, std::vector<std::string> cmd);
		void nick			(Server &s, User *u, std::vector<std::string> cmd);
		void invite			(Server &s, User *u, std::vector<std::string> cmd);
		void part			(Server &s, User *u, std::vector<std::string> cmd);
		void pass			(Server &s, User *u, std::vector<std::string> cmd);
		void topic			(Server &s, User *u, std::vector<std::string> cmd);
		void mode			(Server &s, User *u, std::vector<std::string> cmd);
		void kick			(Server &s, User *u, std::vector<std::string> cmd);
		void whois			(Server &s, User *u, std::vector<std::string> cmd);
		void list			(Server &s, User *u, std::vector<std::string> cmd);
		void names			(Server &s, User *u, std::vector<std::string> cmd);
		void oper			(Server &s, User *u, std::vector<std::string> cmd);
		void notice			(Server &s, User *u, std::vector<std::string> cmd);
		void ping			(Server &s, User *u, std::vector<std::string> cmd);
		void away			(Server &s, User *u, std::vector<std::string> cmd);
		void kill			(Server &s, User *u, std::vector<std::string> cmd);



		typedef void (Commands::*Cmd)(Server &s, User *user, std::vector<std::string> cmd);
		std::map<std::string, Cmd> 		cmd_map;

		typedef std::string (*Rep)(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3);
		std::map<int, Rep> 	server_replies;

		void			rpl_lists			(Server &s, User *u, std::string chan_name, std::vector<std::string> list, std::string rpl_name, std::string rpl_end_name);
		bool			takeArg				(char mode);
		bool 			isSet				(Channel *chan, char mode);
		void			handleChannelModes	(Server &s, User *u, std::string chan_name, std::vector<std::string> cmd);
		void			handleUserModes		(Server &s, User *u, std::string nickname_asked, std::vector<std::string> cmd);
		std::string		makeModeString		(User *u);

		void 			simpleAdd(Server &s, Channel *chan, User *u, bool *joined, std::vector<std::string> *pass, size_t i);
		void 			createChan(Server &s, std::string chan_name, User *u, bool *joined);

};


/*
**  Utils
*/

bool						pattern_match (std::string str, std::string pattern);
std::string					trim(const std::string &s);
std::string					ltrim(const std::string &s);
std::vector<std::string> 	tokenize(std::string const &str, const char delim);
std::list<std::string> 		tokenize_list(std::string const &str, const char delim);
std::string					vecToString(std::vector<std::string> input);
std::string					implodeMessage(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
std::string					toLower(std::string str);

#endif
