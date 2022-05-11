

#include "User.hpp"
#include "Commands.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User() : socket_descriptor(0)
{
    this->name = "Guest";
    nickname = "Guest";
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
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
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

/* ************************************************************************** */
