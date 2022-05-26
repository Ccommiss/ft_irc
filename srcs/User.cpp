

#include "Server.hpp"
#include "User.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User(int sd) : socket_descriptor(sd), name("Guest"), nickname("Guest"), event(NULL)
{
    for (int i = 0; i < 4; i++)
         registered[i] = false;
	nickname.append(to_str(sd));
}

User::User( const User & src )
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

User &				User::operator=( User const & rhs )
{

    (void)rhs;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, User const & i )
{
    (void)i;
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


void        User::setName(std::string newName)
{
    this->name = trim(newName); 
}

void        User::setNickName(std::string newNickName)
{
    this->nickname = trim(newNickName); 
}

void        User::setSocket(int sd)
{
    this->socket_descriptor = sd;
}

void        User::joinChan(Channel *chan)
{
    this->joined_chans.push_back(chan);
}

void        User::leaveChan(Channel *chan)
{
    for (std::vector<Channel *>::iterator it = joined_chans.begin(); it != joined_chans.end(); it++)
    {
        if (*it == chan)
        {
            this->joined_chans.erase(it);
            chan->remove_user(this);
        }
    }
}

std::string const &       User::getName() const
{
    return (this->name);
}

std::string const &       User::getNickName() const
{
    return (this->nickname);
}

std::vector<Channel *> const & User::getJoinedChannels()
{
    return (this->joined_chans);
}

bool    User::HasCompletedRegistration()
{
    if (!registered[USER] || !registered[NICK])
        return false;
    return true;
}

/* ************************************************************************** */
