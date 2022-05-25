#ifndef USER_HPP
# define USER_HPP

#include <iostream> 
#include <vector>

class Channel;

class User {
	private:
	User( void );
    public:
        int         			socket_descriptor;
        int 					registered;
        std::string 			name;
        std::string 			nickname;
        std::string 			ip;
    	std::vector<Channel *>	joined_chans;


    User( int sd, std::string ip );
    User(User const & src);
    ~User( void );
    User &	operator=(User const & rhs);

    void                            setSocket(int sd);
    void                            setNickName(std::string newNickName);
    void                            setName(std::string newName);


	std::string						presentation( void );
    std::string const               &getName( void );
    static std::string              getNickName( void ); //{ return nickname; }

    void                            joinChan(Channel *chan);
    void                            leaveChan(Channel *chan);
    std::vector<Channel *> const & getJoinedChannels();
    

    
};


#endif 
