

#include "User.hpp"
#include "Commands.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User() : socket_descriptor(0), registered(0)
{
    this->name = "Guest";
    nickname = "Guest";
}
User::User(int sd, std::string name): name(name), socket_descriptor(sd), registered(0)
{
    nickname = "Guest";
}

User::User( const User & src ): socket_descriptor(src.socket_descriptor), registered(src.registered)
{
    this->name = src.name;
    this->nickname = src.nickname;
    *this = src;
}
User::User(const std::string & user_name, const std::string & nick_name, const int sd):
    name(user_name),
	nickname(nick_name),
	socket_descriptor(sd)
{}
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
	if ( this != &rhs )
	{
		this->name = rhs.name;
        this->nickname = rhs.nickname;
        this->socket_descriptor = rhs.socket_descriptor;
        this->registered = rhs.registered;
	}
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

std::string User::getName() const 
{
    return (this->name);
}
std::string User::getNick() const 
{
    return (this->nickname);
}


/* ************************************************************************** */
