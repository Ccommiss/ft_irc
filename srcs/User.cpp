

#include "Server.hpp"
#include "User.hpp"
#include "Answers.hpp"
#include <algorithm>

/*
**              a - user is flagged as away;
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

User::User(const User &src)
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

User::~User()
{
	debug(US, presentation(), NOCR);
	debug(US, "CLOSED");
	std::cout << "NEED TO LEAVE ALL CHANS" << std::endl;
	joined_chans.clear();
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

User &User::operator=(User const &rhs)
{

	(void)rhs;
	return *this;
}

std::ostream &operator<<(std::ostream &o, User const &i)
{
	(void)i;
	// o << "Value = " << i.getValue();
	return o;
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

std::string	User::presentation( void )
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

std::vector<Channel *> const &User::getJoinedChannels()
{
	return (this->joined_chans);
}

bool User::HasCompletedRegistration()
{
	if (!registered[USER] || !registered[NICK]) // rajouter pass 
		return false;
	return true;
}

std::string User::whoIsPrivileges()
{
	std::string privileges("privileges :");
	for (std::map<char, bool>::iterator it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->second == true)
		{
			privileges.append("+"); // je crois c une seule fois le +, a verifier
			privileges.push_back(it->first);
		}
	}
	return privileges;
} // print channels for whoiscmd


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
		if (!( (*it)->hasMode('s') || (*it)->hasMode('p')) && !(*it)->isInChan(u)) // a tester
		{
			if ((*it)->isOperator(this))
				answer.append("@");
			answer.append((*it)->_name);
			answer.append(" ");
		}
	}
	out("CHANNES JOIND =" << answer << " SIZE " << joined_chans.size()) return answer;
}

bool User::hasMode(char mode)
{
	return (_modes[mode]);
}

void User::setOneKeyMode(char mode, bool value)
{
	_modes[mode] = value;
}


/* Mode <nickname> valeur  */
std::string User::setMode(char mode, bool value, std::vector<std::string> params)
{
	start;
	out (" mode  " << mode << " value " << value)
	if (!_modes.count(mode)) /* Checking if mode exists */
		return ERR_UMODEUNKNOWNFLAG;

	/* Future target user for O, o and v options*/
	// User *user = NULL;
	(void)params;
	switch (mode)
	{
	case 'a': /* Away */
	{
		// NOT TOGGLED BY MODE BUT BY AWAY MSG SO RESTRICTION IN MODE MSG FOR a TODO
		break;
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
			return "  ";
		break;
	}
	case ('O'):
	{
		if (value == false) /* Same as above */
			_modes['O'] = false;
		else
			return "  ";
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
			return "  ";
		break;
	}
	}
	return "";
}

/* ************************************************************************** */
