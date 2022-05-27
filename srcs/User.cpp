

#include "Server.hpp"
#include "User.hpp"
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

User::User(int sd) : socket_descriptor(sd), name("Guest"), nickname("Guest"), event(NULL)
{
    for (int i = 0; i < 4; i++)
        registered[i] = false;

    initModes();
    nickname.append(to_str(sd));
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

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void User::setName(std::string newName)
{
    this->name = trim(newName);
}

void User::setNickName(std::string newNickName)
{
    this->nickname = trim(newNickName);
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
    if (!registered[USER] || !registered[NICK])
        return false;
    return true;
}

std::string User::whoIsChannels()
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

std::string User::whoIsPrivileges()
{
    std::string answer;
    for (std::vector<Channel *>::iterator it = joined_chans.begin(); it != joined_chans.end(); it++)
    {
        if ((*it)->isOperator(this))
            answer.append("@");
        answer.append((*it)->_name);
        answer.append(" ");
    }
    return answer;
}

/* ************************************************************************** */
