
#include "Commands.hpp"
#include "Debug.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Commands::Commands()
{
    start;
    cmd_map.insert(std::make_pair("NICK", &Commands::nick));
	cmd_map.insert(std::make_pair("CAP",  &Commands::nick));
    cmd_map.insert(std::make_pair("USER",  &Commands::setUser));
    cmd_map.insert(std::make_pair("JOIN",  &Commands::join));
    cmd_map.insert(std::make_pair("PRIVMSG",  &Commands::priv_msg));
    cmd_map.insert(std::make_pair("EXIT",  &Commands::quit_s));
}




/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Commands::~Commands()
{

}


