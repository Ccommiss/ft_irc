#ifndef ANSWERS_HPP
#define ANSWERS_HPP

/*
**	@file  answers.hpp
**	@brief manage anwers
*/

#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include "Debug.hpp"

#include "numeric_rpl.hpp"

/*
**  Define messages
*/

#define NONE ""
#define MSG_001 ":Welcome to the Internet Relay Network of Clement and Claire " + user->nickname + "!" + user->name + "@" + s.hostname
#define MSG_002 ":Your host is localhost, version 1.0   8-)"
#define MSG_003 ":This server was created not so long time ago."
#define MSG_004 ":You are very welcome. Enjoy !"
#define MSG_005 ":Try server <server_name>, port <port_number> Sent by the server to a user to suggest an alternative server, sometimes used " 																								 /* RPL_BOUNCE */
#define MSG_200 "Link <version>[.<debug_level>] <destination> <next_server> [V<protocol_version> <link_uptime_in_seconds> <backstream_sendq> <upstream_sendq>] See RFC"																	  /* RPL_TRACELINK */
#define MSG_201 "Try. <class> <server> See RFC"																																															  /* RPL_TRACECONNECTING */
#define MSG_202 "H.S. <class> <server> See RFC"																																															  /* RPL_TRACEHANDSHAKE */
#define MSG_203 "???? <class> [<connection_address>] See RFC"																																											  /* RPL_TRACEUNKNOWN */
#define MSG_204 "Oper <class> <nick> See RFC"																																															  /* RPL_TRACEOPERATOR */
#define MSG_205 "User <class> <nick> See RFC"																																															  /* RPL_TRACEUSER */
#define MSG_206 "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> [V<protocol_version>] See RFC"																														  /* RPL_TRACESERVER */
#define MSG_207 "Service <class> <name> <type> <active_type> See RFC"																																									  /* RPL_TRACESERVICE */
#define MSG_208 "<newtype> 0 <client_name> See RFC"																																														  /* RPL_TRACENEWTYPE */
#define MSG_209 "Class <class> <count> See RFC"																																															  /* RPL_TRACECLASS */
#define MSG_210 ""																																																						  /* RPL_TRACERECONNECT */
#define MSG_211 "<linkname> <sendq> <sent_msgs> <sent_bytes> <recvd_msgs> <rcvd_bytes> <time_open> Reply to STATS (See RFC)"																											  /* RPL_STATSLINKINFO */
#define MSG_212 "<command> <count> [<byte_count> <remote_count>] Reply to STATS (See RFC)"																																				  /* RPL_STATSCOMMANDS */
#define MSG_213 "C <host> * <name> <port> <class> Reply to STATS (See RFC)"																																								  /* RPL_STATSCLINE */
#define MSG_214 "N <host> * <name> <port> <class> Reply to STATS (See RFC), Also known as RPL_STATSOLDNLINE (ircu, Unreal)"																												  /* RPL_STATSNLINE */
#define MSG_215 "I <host> * <host> <port> <class> Reply to STATS (See RFC)"																																								  /* RPL_STATSILINE */
#define MSG_216 "K <host> * <username> <port> <class> Reply to STATS (See RFC)"																																							  /* RPL_STATSKLINE */
#define MSG_217 ""																																																						  /* RPL_STATSQLINE */
#define MSG_218 "Y <class> <ping_freq> <connect_freq> <max_sendq> Reply to STATS (See RFC)"																																				  /* RPL_STATSYLINE */
#define MSG_219 "<query> :<info> End of RPL_STATS* list."																																												  /* RPL_ENDOFSTATS */
#define MSG_221 "<user_modes> [<user_mode_params>] Information about a user's own modes."																																				  /* RPL_UMODEIS */
#define MSG_231 ""																																																						  /* RPL_SERVICEINFO */
#define MSG_232 ""																																																						  /* RPL_ENDOFSERVICES */
#define MSG_233 ""																																																						  /* RPL_SERVICE */
#define MSG_234 "<name> <server> <mask> <type> <hopcount> <info> A service entry in the service list"																																	  /* RPL_SERVLIST */
#define MSG_235 "<mask> <type> :<info> Termination of an RPL_SERVLIST list"																																								  /* RPL_SERVLISTEND */
#define MSG_240 ""																																																						  /* RPL_STATSVLINE */
#define MSG_241 "L <hostmask> * <servername> <maxdepth> Reply to STATS (See RFC)"																																						  /* RPL_STATSLLINE */
#define MSG_242 ":Server Up <days> days <hours>:<minutes>:<seconds> Reply to STATS (See RFC)"																																			  /* RPL_STATSUPTIME */
#define MSG_243 "O <hostmask> * <nick> [:<info>] Reply to STATS (See RFC); The info field is an extension found in some IRC daemons, "																									  /* RPL_STATSOLINE */
#define MSG_244 "H <hostmask> * <servername> Reply to STATS (See RFC)"																																									  /* RPL_STATSHLINE */
#define MSG_246 ""																																																						  /* RPL_STATSPING */
#define MSG_247 ""																																																						  /* RPL_STATSBLINE */
#define MSG_249 "to RFC1459?"																																																			  /* RPL_STATSULINE */
#define MSG_250 ""																																																						  /* RPL_STATSDLINE */
#define MSG_251 ":There are <int> users and <int> invisible on <int> servers Reply to LUSERS command, other versions exist (eg. RFC2812); Text may vary."																				  /* RPL_LUSERCLIENT */
#define MSG_252 "<int> :<info> Reply to LUSERS command - Number of IRC operators online"																																				  /* RPL_LUSEROP */
#define MSG_253 "<int> :<info> Reply to LUSERS command - Number of unknown/unregistered connections"																																	  /* RPL_LUSERUNKNOWN */
#define MSG_254 "<int> :<info> Reply to LUSERS command - Number of channels formed"																																						  /* RPL_LUSERCHANNELS */
#define MSG_255 ":I have <int> clients and <int> servers Reply to LUSERS command - Information about local connections; Text may vary."																									  /* RPL_LUSERME */
#define MSG_256 "<server> :<info> Start of an RPL_ADMIN* reply"																																											  /* RPL_ADMINME */
#define MSG_257 ":<admin_location> Reply to ADMIN command (Location, first line)"																																						  /* RPL_ADMINLOC1 */
#define MSG_258 ":<admin_location> Reply to ADMIN command (Location, second line)"																																						  /* RPL_ADMINLOC2 */
#define MSG_259 ":<email_address> Reply to ADMIN command (E-mail address of administrator)"																																				  /* RPL_ADMINEMAIL */
#define MSG_261 "File <logfile> <debug_level> See RFC"																																													  /* RPL_TRACELOG */
#define MSG_262 "<server_name> <version>[.<debug_level>] :<info> Used to terminate a list of RPL_TRACE* replies"																														  /* RPL_TRACEEND */
#define MSG_263 "<command> :<info> When a server drops a command without processing it, it MUST use this reply."																														  /* RPL_TRYAGAIN */
#define MSG_300 "Dummy reply, supposedly only used for debugging/testing new features, however has appeared in production daemons."																										  /* RPL_NONE */
#define MSG_301 arg1 + " :" + arg2 //Used in reply to a command directed at a user who is marked as away"																																	  /* RPL_AWAY */
#define MSG_302 ":*1<reply> *( ' ' <reply> ) Reply used by USERHOST (see RFC)"																																							  /* RPL_USERHOST */
#define MSG_303 ":*1<nick> *( ' ' <nick> ) Reply to the ISON command (see RFC)"																																							  /* RPL_ISON */
#define MSG_305 ": You are no longer marked as AWAY :)" 																																								  /* RPL_UNAWAY */
#define MSG_306 ": You are marked as AWAY zZzZ" 																																											  /* RPL_NOWAWAY */
#define MSG_311 arg1 + " " + arg2 + " " + s.hostname + " * " + arg3// Reply to WHOIS - Information about the user"																																		  /* RPL_WHOISUSER */
#define MSG_312 arg1 + " " + arg2																																				  /* RPL_WHOISSERVER */
#define MSG_313 arg1 + " :is an IRC operator" //Reply to WHOIS - User has IRC Operator privileges"																																				  /* RPL_WHOISOPERATOR */
#define MSG_314 arg1+ " " + "<user> <host> * :<real_name> Reply to WHOWAS - Information about the user"																																		  /* RPL_WHOWASUSER */
#define MSG_315 "<name> :<info> Used to terminate a list of RPL_WHOREPLY replies"																																						  /* RPL_ENDOFWHO */
#define MSG_316 ""																																																						  /* RPL_WHOISCHANOP */
#define MSG_317 arg1 + " " + arg2 + " :seconds idle" //Reply to WHOIS - Idle information"																																						  /* RPL_WHOISIDLE */
#define MSG_318 arg1 + " " + " :End of WHOIS list"																																										  /* RPL_ENDOFWHOIS */
#define MSG_319 arg1 + " :" + arg2 // " :*( ( '@' / '+' ) <channel> ' ' ) Reply to WHOIS - Channel list for user (See RFC)"																																  /* RPL_WHOISCHANNELS */
#define MSG_322 arg1 + " " + printModes(s.chans[arg1]) + " :" + arg3 // Channel list - A channel"																																								  /* RPL_LIST */
#define MSG_323 ": End of channel list."																																													  /* RPL_LISTEND */
#define MSG_324 arg1 + " " + arg2 + " " + arg3 																																														  /* RPL_CHANNELMODEIS */
#define MSG_325 "<channel> <nickname>"																																																	  /* RPL_UNIQOPIS */
#define MSG_331 arg1 + " :No topic is set."																																																  /* RPL_NOPIC */
#define MSG_332 arg1 + " :" + arg2																																																		  /* RPL_TOPIC */
#define MSG_341 arg1 + " " + arg2 // "<channel> <nick>" 																																														  /* RPL_INVITING */
#define MSG_342 "<user> :<info> Returned by a server answering a SUMMON message to indicate that it is summoning that user"																												  /* RPL_SUMMONING */
#define MSG_346 arg1 + " " + arg2 // <invitemask> An invite mask for the invite mask list"																																						  /* RPL_INVITELIST */
#define MSG_347 arg1 + " :End of invite list ! :) "// Termination of an RPL_INVITELIST list"																																								  /* RPL_ENDOFINVITELIST */
#define MSG_348 "<channel> <exceptionmask> An exception mask for the exception mask list. Also known as RPL_EXLIST (Unreal, Ultimate)"																									  /* RPL_EXCEPTLIST */
#define MSG_349 "<channel> :<info> Termination of an RPL_EXCEPTLIST list. Also known as RPL_ENDOFEXLIST (Unreal, Ultimate)"																												  /* RPL_ENDOFEXCEPTLIST */
#define MSG_351 "<version>[.<debuglevel>] <server> :<comments> Reply by the server showing its version details, however this format is not often adhered to"																			  /* RPL_VERSION */
#define MSG_352 "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real_name> Reply to vanilla WHO (See RFC)."																											  /* RPL_WHOREPLY */
#define MSG_353 "= " + arg1 + " :" + printNames(s.chans[arg1], user)																																											  // il faut le serveur ou le chan a minima                    //CHANGER EN FO Status"
#define MSG_354 "Reply to WHO, however it is a 'special' reply because it is returned using a non-standard "																															  /* RPL_WHOSPCRPL */
#define MSG_361 ""																																																						  /* RPL_KILLDONE */
#define MSG_362 ""																																																						  /* RPL_CLOSING */
#define MSG_363 ""																																																						  /* RPL_CLOSEEND */
#define MSG_364 "<mask> <server> :<hopcount> <server_info> Reply to the LINKS command"																																					  /* RPL_LINKS */
#define MSG_365 "<mask> :<info> Termination of an RPL_LINKS list"																																										  /* RPL_ENDOFLINKS */
#define MSG_366 arg1 + " :End of NAMES list"																																															  /* RPL_ENDOFNAMES */
#define MSG_367 arg1 + " " + arg2// [<time_left> :<reason>] A ban-list item (See RFC); <time left> and <reason> are additions used by KineIRCd"																							  /* RPL_BANLIST */
#define MSG_368 arg1 + " :End of ban list (" + arg2 + " masks set)" //:<info> Termination of an RPL_BANLIST list"																																									  /* RPL_ENDOFBANLIST */
#define MSG_369 "<nick> :<info> Reply to WHOWAS - End of list"																																											  /* RPL_ENDOFWHOWAS */
#define MSG_371 ":<string> Reply to INFO"																																																  /* RPL_INFO */
#define MSG_372 ":- <string> Reply to MOTD"																																																  /* RPL_MOTD */
#define MSG_373 ""																																																						  /* RPL_INFOSTART */
#define MSG_374 " :<info> Termination of an RPL_INFO list"																																												  /* RPL_ENDOFINFO */
#define MSG_375 " :- <server> Message of the day - Start of an RPL_MOTD list"																																							  /* RPL_MOTDSTART */
#define MSG_376 " :<info> Termination of an RPL_MOTD list"																																												  /* RPL_ENDOFMOTD */
#define MSG_381 " :You are now an IRC operator"																																													  /* RPL_YOUREOPER */
#define MSG_382 "<config_file> :<info> Successful reply from REHASH"																																									  /* RPL_REHASHING */
#define MSG_383 ":You are service <service_name> Sent upon successful registration of a service"																																		  /* RPL_YOURESERVICE */
#define MSG_384 ""																																																						  /* RPL_MYPORTIS */
#define MSG_391 "<server> :<time string> Response to the TIME command. The string format may vary greatly. Also see #679."																												  /* RPL_TIME */
#define MSG_392 ":UserID Terminal Host Start of an RPL_USERS list"																																										  /* RPL_USERSSTART */
#define MSG_393 ":<username> <ttyline> <hostname> Response to the USERS command (See RFC)"																																				  /* RPL_USERS */
#define MSG_394 ":<info> Termination of an RPL_USERS list"																																												  /* RPL_ENDOFUSERS */
#define MSG_395 ":<info> Reply to USERS when nobody is logged in"																																										  /* RPL_NOUSERS */
#define ERR_401 arg1 + " :No such nick/channel" 				  /* ERR_NOSUCHNICK */
#define ERR_402 arg1 + " :Used to indicate the server name given currently doesn't exist"																																		  /* ERR_NOSUCHSERVER */
#define ERR_403 arg1 + " :No such channel"																																																  /* ERR_NOSUCHCHANNEL */
#define ERR_404 arg1 + " :Cannot send to channel"																																														  /* ERR_CANNOTSENDTOCHAN */
#define ERR_405 "<channel> :<reason> Sent to a user when they have joined the maximum number of allowed channels and they tried to join another channel"																				  /* ERR_TOOMANYCHANNELS */
#define ERR_406 "<nick> :<reason> Returned by WHOWAS to indicate there was no history information for a given nickname"																													  /* ERR_WASNOSUCHNICK */
#define ERR_407 "<target> :<reason> The given target(s) for a command are ambiguous in that they relate to too many targets"																											  /* ERR_TOOMANYTARGETS */
#define ERR_408 "<service_name> :<reason> Returned to a client which is attempting to send an SQUERY (or other message) to a service which does not exist"																				  /* ERR_NOSUCHSERVICE */
#define ERR_409 ":PING or PONG message missing the originator parameter which is required since these commands must work without valid prefixes"																				  /* ERR_NOORIGIN */
#define ERR_411 ":<reason> Returned when no recipient is given with a command"																																							  /* ERR_NORECIPIENT */
#define ERR_412 ":<reason> Returned when NOTICE/PRIVMSG is used with no message given"																																					  /* ERR_NOTEXTTOSEND */
#define ERR_413 "<mask> :<reason> Used when a message is being sent to a mask without being limited to a top-level domain (i.e. * instead of *.au)"																						  /* ERR_NOTOPLEVEL */
#define ERR_414 "<mask> :<reason> Used when a message is being sent to a mask with a wild-card for a top level domain (i.e. *.*)"																										  /* ERR_WILDTOPLEVEL */
#define ERR_415 "<mask> :<reason> Used when a message is being sent to a mask with an invalid syntax"																																	  /* ERR_BADMASK */
#define ERR_421 "<command> :<reason> Returned when the given command is unknown to the server (or hidden because of lack of access rights)"																								  /* ERR_UNKNOWNCOMMAND */
#define ERR_422 ":<reason> Sent when there is no MOTD to send the client"																																								  /* ERR_NOMOTD */
#define ERR_423 "<server> :<reason> Returned by a server in response to an ADMIN request when no information is available. RFC1459 mentions this in the list of numerics. While it's not listed as a valid reply in section 4.3.7 [...]." /* ERR_NOADMININFO */
#define ERR_424 ":<reason> Generic error message used to report a failed file operation during the processing of a command"																												  /* ERR_FILEERROR */
#define ERR_431 ":<reason> Returned when a nickname parameter expected for a command isn't found"																																		  /* ERR_NONICKNAMEGIVEN */
#define ERR_432 "<nick> :<reason> Returned after receiving a NICK message which contains a nickname which is considered invalid, s[...] "																								  /* ERR_ERRONEUSNICKNAME */
#define ERR_433 arg1 + " :Nickname is already in use" //Returned by the NICK command when the given nickname is already in use"																																  /* ERR_NICKNAMEINUSE */
#define ERR_436 "<nick> :<reason> Returned by a server to a client when it detects a nickname collision"																																  /* ERR_NICKCOLLISION */
#define ERR_437 "<nick/channel/service> :<reason> Return when the target is unable to be reached temporarily, eg. a delay mechanism in play, or a service being offline"																  /* ERR_UNAVAILRESOURCE */
#define ERR_441 arg1 + " " + arg2 + ": They aren't on that channel"																																										  /* ERR_USERNOTINCHANNEL */
#define ERR_442 arg1 + " :You're not on that channel" 																		  /* ERR_NOTONCHANNEL */
#define ERR_443 arg1 + " " + arg2 + " :User already on channel"																																											  /* ERR_USERONCHANNEL */
#define ERR_444 "<user> :<reason> Returned by the SUMMON command if a given user was not logged in and could not be summoned"																											  /* ERR_NOLOGIN */
#define ERR_445 ":<reason> Returned by SUMMON when it has been disabled or not implemented"																																				  /* ERR_SUMMONDISABLED */
#define ERR_446 ":<reason> Returned by USERS when it has been disabled or not implemented"																																				  /* ERR_USERSDISABLED */
#define ERR_451 ":<reason> Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail"																				  /* ERR_NOTREGISTERED */
#define ERR_461 arg1 + " :Not enough parameters"																																														  /* ERR_NEEDMOREPARAMS */
#define ERR_462 ":Unauthorized command (already registered)"																																											  /* ERR_ALREADYREGISTERED */
#define ERR_463 ":Your host isn't among the privileged"																																													  /* ERR_NOPERMFORHOST */
#define ERR_464 arg1 + ":Password incorrect"																																																	  /* ERR_PASSWDMISMATCH */
#define ERR_465 ":You are banned from this server"																																														  /* ERR_YOUREBANNEDCREEP */
#define ERR_466 ""																																																						  /* ERR_YOUWILLBEBANNED  , no msg */
#define ERR_467 arg1 + " :Channel key already set"																																														  /* ERR_KEYSET */
#define ERR_471 arg1 + " :Cannot join channel (+l)"																																														  /* ERR_CHANNELISFULL */
#define ERR_472 arg1 + " :is unknown mode char to me for " + arg2																																										  /* ERR_UNKNOWNMODE */
#define ERR_473 arg1 + " :Cannot join channel (+i) (You must be invited)"																																								  /* ERR_INVITEONLYCHAN */
#define ERR_474 arg1 + " :Cannot join channel (+b) (You're banned)"																																														  /* ERR_BANNEDFROMCHAN */
#define ERR_475 arg1 + " :Cannot join channel (+k)"																																														  /* ERR_BADCHANNELKEY */
#define ERR_476 arg1 + " :Bad Channel Mask"																																																  /* ERR_BADCHANMASK */
#define ERR_477 arg1 + " :Channel doesn't support modes"																																												  /* ERR_NOCHANMODES */
#define ERR_478 arg1 + " :Channel list is full"																																															  /* ERR_BANLISTFULL */
#define ERR_481 ":<reason> Returned by any command requiring special privileges (eg. IRC operator) to indicate the operation was unsuccessful"																							  /* ERR_NOPRIVILEGES */
#define ERR_482 arg1 + " :You're not channel operator"																																													  /* ERR_CHANOPRIVSNEEDED */
#define ERR_483 ":<reason> Returned by KILL to anyone who tries to kill a server"																																						  /* ERR_CANTKILLSERVER */
#define ERR_484 ":<reason> Sent by the server to a user upon connection to indicate the restricted nature of the connection (i.e. usermode +r)"																							  /* ERR_RESTRICTED */
#define ERR_485 ":<reason> Any mode requiring 'channel creator' privileges returns this error if the client is attempting to use it while not a channel creator on the given channel"													  /* ERR_UNIQOPRIVSNEEDED */
#define ERR_491 ":<reason> Returned by OPER to a client who cannot become an IRC operator because the server has been configured to disallow the client's host"																			  /* ERR_NOOPERHOST */
#define ERR_492 ""																																																						  /* ERR_NOSERVICEHOST */
#define ERR_501 ":<reason> Returned by the server to indicate that a MODE message was sent with a nickname parameter and that the mode flag sent was not recognised"																	  /* ERR_UMODEUNKNOWNFLAG */
#define ERR_502 ":<reason> Error sent to any user trying to view or change the user mode for a user other than themselves"																												  /* ERR_USERSDONTMATCH */

/*
**      Numeric Replies :
**      Functions pointed in server_replies returning content of define messages
*/

inline std::string RPL_001(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_001);}
inline std::string RPL_002(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_002);}
inline std::string RPL_003(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_003);}
inline std::string RPL_004(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_004);}
inline std::string RPL_005(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_005);}
inline std::string RPL_200(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_200);}
inline std::string RPL_201(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_201);}
inline std::string RPL_202(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_202);}
inline std::string RPL_203(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_203);}
inline std::string RPL_204(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_204);}
inline std::string RPL_205(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_205);}
inline std::string RPL_206(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_206);}
inline std::string RPL_207(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_207);}
inline std::string RPL_208(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_208);}
inline std::string RPL_209(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_209);}
inline std::string RPL_210(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_210);}
inline std::string RPL_211(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_211);}
inline std::string RPL_212(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_212);}
inline std::string RPL_213(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_213);}
inline std::string RPL_214(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_214);}
inline std::string RPL_215(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_215);}
inline std::string RPL_216(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_216);}
inline std::string RPL_217(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_217);}
inline std::string RPL_218(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_218);}
inline std::string RPL_219(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_219);}
inline std::string RPL_221(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_221);}
inline std::string RPL_231(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_231);}
inline std::string RPL_232(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_232);}
inline std::string RPL_233(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_233);}
inline std::string RPL_234(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_234);}
inline std::string RPL_235(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_235);}
inline std::string RPL_240(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_240);}
inline std::string RPL_241(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_241);}
inline std::string RPL_242(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_242);}
inline std::string RPL_243(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_243);}
inline std::string RPL_244(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_244);}
inline std::string RPL_246(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_246);}
inline std::string RPL_247(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_247);}
inline std::string RPL_249(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_249);}
inline std::string RPL_250(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_250);}
inline std::string RPL_251(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_251);}
inline std::string RPL_252(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_252);}
inline std::string RPL_253(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_253);}
inline std::string RPL_254(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_254);}
inline std::string RPL_255(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_255);}
inline std::string RPL_256(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_256);}
inline std::string RPL_257(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_257);}
inline std::string RPL_258(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_258);}
inline std::string RPL_259(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_259);}
inline std::string RPL_261(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_261);}
inline std::string RPL_262(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_262);}
inline std::string RPL_263(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_263);}
inline std::string RPL_300(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_300);}
inline std::string RPL_301(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_301);}
inline std::string RPL_302(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_302);}
inline std::string RPL_303(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_303);}
inline std::string RPL_305(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_305);}
inline std::string RPL_306(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_306);}
inline std::string RPL_311(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_311);}
inline std::string RPL_312(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_312);}
inline std::string RPL_313(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_313);}
inline std::string RPL_314(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_314);}
inline std::string RPL_315(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_315);}
inline std::string RPL_316(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_316);}
inline std::string RPL_317(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_317);}
inline std::string RPL_318(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_318);}
inline std::string RPL_319(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_319);}
inline std::string RPL_322(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_322);}
inline std::string RPL_323(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_323);}
inline std::string RPL_324(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_324);}
inline std::string RPL_325(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_325);}
inline std::string RPL_331(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_331);}
inline std::string RPL_332(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_332);}
inline std::string RPL_341(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_341);}
inline std::string RPL_342(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_342);}
inline std::string RPL_346(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_346);}
inline std::string RPL_347(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_347);}
inline std::string RPL_348(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_348);}
inline std::string RPL_349(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_349);}
inline std::string RPL_351(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_351);}
inline std::string RPL_352(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_352);}
inline std::string RPL_353(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_353);}
inline std::string RPL_354(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_354);}
inline std::string RPL_361(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_361);}
inline std::string RPL_362(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_362);}
inline std::string RPL_363(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_363);}
inline std::string RPL_364(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_364);}
inline std::string RPL_365(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_365);}
inline std::string RPL_366(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_366);}
inline std::string RPL_367(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_367);}
inline std::string RPL_368(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_368);}
inline std::string RPL_369(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_369);}
inline std::string RPL_371(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_371);}
inline std::string RPL_372(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_372);}
inline std::string RPL_373(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_373);}
inline std::string RPL_374(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_374);}
inline std::string RPL_375(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_375);}
inline std::string RPL_376(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_376);}
inline std::string RPL_381(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_381);}
inline std::string RPL_382(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_382);}
inline std::string RPL_383(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_383);}
inline std::string RPL_384(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_384);}
inline std::string RPL_391(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_391);}
inline std::string RPL_392(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_392);}
inline std::string RPL_393(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_393);}
inline std::string RPL_394(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_394);}
inline std::string RPL_395(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (MSG_395);}
inline std::string RPL_401(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_401);}
inline std::string RPL_402(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_402);}
inline std::string RPL_403(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_403);}
inline std::string RPL_404(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_404);}
inline std::string RPL_405(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_405);}
inline std::string RPL_406(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_406);}
inline std::string RPL_407(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_407);}
inline std::string RPL_408(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_408);}
inline std::string RPL_409(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_409);}
inline std::string RPL_411(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_411);}
inline std::string RPL_412(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_412);}
inline std::string RPL_413(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_413);}
inline std::string RPL_414(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_414);}
inline std::string RPL_415(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_415);}
inline std::string RPL_421(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_421);}
inline std::string RPL_422(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_422);}
inline std::string RPL_423(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_423);}
inline std::string RPL_424(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_424);}
inline std::string RPL_431(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_431);}
inline std::string RPL_432(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_432);}
inline std::string RPL_433(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_433);}
inline std::string RPL_436(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_436);}
inline std::string RPL_437(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_437);}
inline std::string RPL_441(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_441);}
inline std::string RPL_442(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_442);}
inline std::string RPL_443(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_443);}
inline std::string RPL_444(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_444);}
inline std::string RPL_445(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_445);}
inline std::string RPL_446(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_446);}
inline std::string RPL_451(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_451);}
inline std::string RPL_461(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_461);}
inline std::string RPL_462(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_462);}
inline std::string RPL_463(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_463);}
inline std::string RPL_464(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_464);}
inline std::string RPL_465(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_465);}
inline std::string RPL_466(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_466);}
inline std::string RPL_467(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_467);}
inline std::string RPL_471(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_471);}
inline std::string RPL_472(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_472);}
inline std::string RPL_473(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_473);}
inline std::string RPL_474(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_474);}
inline std::string RPL_475(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_475);}
inline std::string RPL_476(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_476);}
inline std::string RPL_477(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_477);}
inline std::string RPL_478(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_478);}
inline std::string RPL_481(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_481);}
inline std::string RPL_482(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_482);}
inline std::string RPL_483(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_483);}
inline std::string RPL_484(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_484);}
inline std::string RPL_485(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_485);}
inline std::string RPL_491(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_491);}
inline std::string RPL_492(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_492);}
inline std::string RPL_501(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_501);}
inline std::string RPL_502(Server &s, User *user, std::string arg1, std::string arg2, std::string arg3){ (void)s; (void)user; (void)arg1; (void)arg2; (void)arg3; return (ERR_502);}

/*
**  Server_relay
**  @brief non numeric replies. Just relay in course command to
**  @tparam T : others users, specified in user_list (corresponding to server_users or just a specific
**  channel users)
**  OR
**  @tparam <> : total specialization for User *
**  Their shape is : :<nick>!<user>@<host> <cmd> [<param>] :<msg>
*/
template <typename T>
inline std::string server_relay(const User *u, std::vector<std::string> cmd, T user_list)
{
	std::string txt;
	txt.append(":");
	txt.append(u->nickname);
	txt.append("!");
	txt.append(u->name); // username
	txt.append("@");
	txt.append(u->ip);
	txt.append(" ");
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end() && *it != "\n"; it++)
		txt.append(*it + " "); // on met touts les commandes dans le prefixe
	txt = trim(txt);
	txt.append("\r\n");
	out(FG2("Server Reply to be sent: (server relay)"));
	out(txt) for (typename T::iterator ite = user_list.begin(); ite != user_list.end(); ite++)
		send(ite->second->socket_descriptor, txt.c_str(), txt.length(), 0); // send to all
	return ((txt));
}

template <> // specialisation si un seul envoi a effectuer
inline std::string server_relay(const User *u, std::vector<std::string> cmd, User *receiver)
{
	std::string txt;
	txt.append(":");
	txt.append(u->nickname);
	txt.append("!");
	txt.append(u->name); // username
	txt.append("@");
	txt.append(u->ip);
	txt.append(" ");
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end() && *it != "\n"; it++)
		txt.append(*it + " "); // on met touts les commandes dans le prefixe
	txt = trim(txt);
	txt.append("\r\n");
	out(FG2("Server Reply to be sent: (server relay)"));
	out(txt)
		send(receiver->socket_descriptor, txt.c_str(), txt.length(), 0);
	return ((txt));
}

/*
**  Numeric Replies
**  @brief  numeric replies sent back to client after a request
**
**  Their shape is : :<host> <3digits> <nickname> : [...] (depends on the answer)
*/

inline std::string Server::choose_msg(int code, User *u, std::string arg1, std::string arg2, std::string arg3)
{
	start;
	out("anwer code " << code) if (cmds.server_replies.count(code) != 1)
	{
		out("==> Unfound server_replies");
		return ("(no reply found)");
	}
	return (*(cmds.server_replies.find(code)->second))(*this, u, arg1, arg2, arg3); // second = la function
}

inline void Server::numeric_reply(User *u, std::string code, std::string arg1, std::string arg2, std::string arg3) // rajouter autre chose pour le channel par ex ? //numeric reply
{
	start;
	std::string txt;
	char *ptr;
	txt.append(":");
//	txt.append("localhost "); // remplacer par le define
	txt.append(hostname);
	txt.append(" ");
	txt.append(code);
	txt.append(" ");
	txt.append(u->nickname); // lui qui va servir commenickname
	txt.append(" ");
	txt.append(choose_msg(std::strtol(code.c_str(), &ptr, 10), u, arg1, arg2, arg3));
	txt.append("\r\n");

	out(FG2("Server Reply to be sent:") << code);
	out(txt.c_str());
	if (send(u->socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
	{
		perror("SEND FAILED");
	}
}

#endif
