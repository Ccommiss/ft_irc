

#include "Server.hpp"
#include "User.hpp"
#include "Answers.hpp"
#include <algorithm>

/*
**				a - user is flagged as away;
**            i - marks a users as invisible;
**            w - user receives wallops;
**            r - restricted user connection;
**            o - operator flag;
**            O - local operator flag;
**            s - marks a user for receipt of server notices.
*/
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User(int sd, std::string ip) : socket_descriptor(sd), name("Guest"), nickname("Guest"), ip(ip)
{
	for (int i = 0; i < 4; i++)
		registered[i] = false;

	initModes();
	nickname.append(to_str(sd));
	debug(US, presentation(), NOCR);
	debug(US, "CONNECTED");
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

User::~User()
{
	debug(US, presentation(), NOCR);
	debug(US, "CLOSED");
	joined_chans.clear();
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void User::initModes()
{
	/* Initializing modes */
	_modes.insert(std::make_pair('a', false));
	_modes.insert(std::make_pair('i', false));
	_modes.insert(std::make_pair('w', false));
	_modes.insert(std::make_pair('r', false));
	_modes.insert(std::make_pair('o', false));
	_modes.insert(std::make_pair('O', false));
	_modes.insert(std::make_pair('s', false));
	_modes.insert(std::make_pair('q', false));
}

std::string User::presentation(void)
{
	std::string to_ret(nickname);
	to_ret = to_ret + "[" + ip + ":" + to_str(socket_descriptor) + "] - ";
	return (to_ret);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void User::setName(std::string newName)
{
	this->name = newName;
}

void User::setNickName(std::string newNickName)
{
	this->nickname = newNickName;
}

void User::setSocket(int sd)
{
	this->socket_descriptor = sd;
}

void User::joinChan(Channel *chan)
{
	this->joined_chans.push_back(chan);
}

void User::leaveChan(Channel *chan)
{
	std::vector<Channel *>::iterator it = std::find(joined_chans.begin(), joined_chans.end(), chan);
	if (it != joined_chans.end())
		joined_chans.erase(it);
}

std::string const &User::getName() const
{
	return (this->name);
}

std::string const &User::getNickName() const
{
	return (this->nickname);
}

std::vector<Channel *> const &User::getJoinedChannels() const
{
	return (this->joined_chans);
}

void User::setAway(std::string msg)
{
	_modes['a'] = true;
	_away_msg = msg;
}

bool User::isAway()
{
	return _modes['a'];
}

std::string &User::getAwayMsg()
{
	return _away_msg;
}

std::string const &User::getRealname() const
{
	return real_name;
}

bool User::HasCompletedRegistration()
{
	if (!registered[USER] || !registered[NICK] || !registered[PASS])
		return false;
	return true;
}

/*
**	@brief displays a full id in for of <nick>!<name>@<host>
**	@details this form is used in comparisons with channel masks (banned, invite, etc)
*/
std::string User::fullID()
{
	std::string txt;
	txt.append(nickname);
	txt.append("!");
	txt.append(name);
	txt.append("@");
	txt.append(ip);

	return txt;
}

std::string User::makeModeString()
{
	std::string msg = "+";
	for (size_t i = 0; i < _modes.size(); i++)
	{
		if (_modes[i] == true)
			msg += _modes[i];
	}
	return msg.length() > 1 ? msg : "";
}

/*
**	whoIsChannel : displays list of channels a user belongs to.
**	@param u - the user asking the whois command. It is used not to
**		display secrets channel the requested user is member of
**		if requetsing user is not a member.
*/
std::string User::whoIsChannels(User *u)
{
	std::string answer;
	for (std::vector<Channel *>::iterator it = joined_chans.begin(); it != joined_chans.end(); it++)
	{
		if (!(*it)->isPrivateForUser(u))
		{
			if ((*it)->isOperator(this))
				answer.append("@");
			answer.append((*it)->_name);
			answer.append(" ");
		}
	}
	return answer;
}

bool User::hasMode(char mode)
{
	if (_modes.count(mode) == 0)
		return false;
	return (_modes[mode]);
}

void User::setOneKeyMode(char mode, bool value)
{
	if (_modes.count(mode) == 0)
		return;
	_modes[mode] = value;
}

/*
**	@brief changing mode of user
**	@param mode the mode to be set
**	@param value the +/- value
**	@param params the facultative args
*/
std::string User::setMode(char mode, bool value, std::vector<std::string> params)
{
	if (!_modes.count(mode)) /* Checking if mode exists */
		return ERR_UMODEUNKNOWNFLAG;
	/* Future target user for O, o and v options*/
	(void)params;
	switch (mode)
	{
	case 'a': /* Away */
	{
		return ERR_UMODEUNKNOWNFLAG;
	}
	case 'i': /* Invisible */
	{
		_modes['i'] = value;
		break;
	}
	case ('o'):
	{
		if (value == false) /* An user cannot op himself but through OPER command */
			_modes['o'] = false;
		else
			return IGNORE;
		break;
	}
	case ('O'):
	{
		if (value == false) /* Same as above */
			_modes['O'] = false;
		else
			return IGNORE;
		break;
	}
	case ('w'): /* Wall ops */
	{
		_modes['w'] = value;
		break;
	}
	case ('r'): /* restricted mode */
	{
		if (value == true)		/* Same as above */
			_modes['r'] = true; /* on peut se restricted mais pas se unrestricted */
		else
			return IGNORE;
		break;
	}
	}
	return "";
}

/* ************************************************************************** */
