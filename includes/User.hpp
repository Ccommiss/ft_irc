#ifndef USER_HPP
# define USER_HPP

#include <iostream> 
#include <vector>
#include <map>

class Channel;

class User {
    public:
        int         			socket_descriptor;
        bool 					registered[4]; //trois booleens 
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
    bool                            HasCompletedRegistration();
    void                            setName(std::string newName);
    std::string const &             getName() const;
    std::string const &             getNickName() const; //{ return nickname; }

    void                            joinChan(Channel *chan);
    void                            leaveChan(Channel *chan);
    std::map<char, bool>&				getModes();
    	std::string							setMode(char mode, bool value, std::vector<std::string > params);
		void								displayModes();
    std::vector<Channel *> const & getJoinedChannels();
    
    
    std::vector<Channel *>          joined_chans;

    enum {
        NICK, 
        USER,
        PASS,
        WELCOMED
    };
    private:
        std::map<char, bool>			_modes;
};


#endif 
