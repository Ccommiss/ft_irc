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
    User(int sd, std::string name);
    User(const std::string & user_name, const std::string & nick_name, const int fd );
    ~User();
    User &	operator=(User const & rhs);

    void        setSocket(int sd);
    // COMMANDES 
    void        setNickName(std::string newNickName);
    void        setName(std::string newName);
    std::string getName() const;
    std::string getNick() const;    
};


#endif 