#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <map>

class Channel;

class User
{
public:
    int socket_descriptor;
    bool registered[4]; // trois booleens
    std::string name;
    std::string nickname;
    std::string 			ip;
    struct epoll_event *event;

    // User();
    User( int sd, std::string ip );
    User(User const &src);
    ~User();
    User &operator=(User const &rhs);

    void setSocket(int sd);
    std::string						presentation( void );
    std::string whoIsChannels(User *u);   // print channels for whoiscmd
    std::string whoIsPrivileges(); // print privileges of user for whois
    void setNickName(std::string newNickName);
    bool HasCompletedRegistration();
    void setName(std::string newName);
    std::string const &getName() const;
    std::string const &getNickName() const; //{ return nickname; }

    void joinChan(Channel *chan);
    void leaveChan(Channel *chan);

    /* Modes */
    void initModes();
    std::map<char, bool> &getModes();
    std::string setMode(char mode, bool value, std::vector<std::string> params);
	void setOneKeyMode(char mode, bool value);
	void displayModes();
    bool hasMode(char mode);
    std::vector<Channel *> const &getJoinedChannels();

    std::vector<Channel *> joined_chans;

    enum
    {
        NICK,
        USER,
        PASS,
        WELCOMED
    };

private:
    std::map<char, bool> _modes;
};

#endif
