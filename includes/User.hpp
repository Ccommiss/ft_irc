#ifndef USER_HPP
# define USER_HPP

#include <iostream> 
#include <vector>

class Channel;

class User {
    public:
        int         			socket_descriptor;
        int 					registered;
        std::string 			name;
        std::string 			nickname;
		struct epoll_event	*	event;


    //User();
    User(int sd);
    User(User const & src);
    ~User();
    User &	operator=(User const & rhs);

    void                            setSocket(int sd);
    void                            setNickName(std::string newNickName);
    void                            setName(std::string newName);
    std::string const               &getName();
    static std::string              getNickName(); //{ return nickname; }

    void                            join_chan(Channel *chan);
    std::vector<Channel *>          joined_chans;

    
};


#endif 
