#ifndef USER_HPP
# define USER_HPP

#include <iostream> 
#include <vector>
 

class User {
    public:
        int         socket_descriptor;
        int registered;
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
    std::string const &getName();
    static std::string getNickName(); //{ return nickname; }

    
};


#endif 