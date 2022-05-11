#ifndef USER_HPP
# define USER_HPP

#include <iostream> 
 

class User {
    public:
        int         socket_descriptor;
        std::string name;
        std::string nickname;


    User();
    User(User const & src);
    ~User();
    User &	operator=(User const & rhs);

    void        setSocket(int sd);
    // COMMANDES 
    void        setNickName(std::string newNickName);
    void        setName(std::string newName);

    
};


#endif 