
#include "Commands.hpp"
#include "Debug.hpp"
#include "Channel.hpp"
#include "Answers.hpp"



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
	cmd_map.insert(std::make_pair("INVITE",  &Commands::invite));
	cmd_map.insert(std::make_pair("PART",  &Commands::part));
	cmd_map.insert(std::make_pair("TOPIC",  &Commands::topic));
	cmd_map.insert(std::make_pair("MODE",  &Commands::mode));
	



	// Now storing replies ; idee, ptr sur func genre Answer::&RPL_001   avec RPL 001 qui prendra un user
	server_replies.insert(std::make_pair(1, &RPL_001));
	server_replies.insert(std::make_pair(2, &RPL_002));
	server_replies.insert(std::make_pair(3, &RPL_003));
	server_replies.insert(std::make_pair(4, &RPL_004));
	server_replies.insert(std::make_pair(331, &RPL_331)); // RPL TOPIC
	server_replies.insert(std::make_pair(332, &RPL_332)); // RPL NOTOPIC
	server_replies.insert(std::make_pair(341, &RPL_341));
	server_replies.insert(std::make_pair(353, &RPL_353));
	server_replies.insert(std::make_pair(366, &RPL_366));

	server_replies.insert(std::make_pair(461, &RPL_461));
	server_replies.insert(std::make_pair(462, &RPL_462));
	server_replies.insert(std::make_pair(463, &RPL_463));
	server_replies.insert(std::make_pair(464, &RPL_464));
	server_replies.insert(std::make_pair(465, &RPL_465));
	server_replies.insert(std::make_pair(466, &RPL_466));
	server_replies.insert(std::make_pair(467, &RPL_467));
	server_replies.insert(std::make_pair(471, &RPL_471));
	server_replies.insert(std::make_pair(472, &RPL_472));
	server_replies.insert(std::make_pair(473, &RPL_473));
	server_replies.insert(std::make_pair(474, &RPL_474));
	server_replies.insert(std::make_pair(475, &RPL_475));
	server_replies.insert(std::make_pair(476, &RPL_476));
	server_replies.insert(std::make_pair(477, &RPL_477));
	server_replies.insert(std::make_pair(478, &RPL_478));

}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Commands::~Commands()
{

}


