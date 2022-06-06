#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <map>

class Channel;

class User
{
	friend class Server;
	friend class Commands;
public:
	int socket_descriptor;
	bool registered[4];
	struct epoll_event *event;

	/* Constructor, destructor & co */
	User(int sd, std::string ip);
	~User();

	/* Accessors */
	void setSocket(int sd);
	std::string const &getIP() const;
	std::string const &getBuffer() const;
	void setName(std::string newName);
	void setNickName(std::string newNickName);
	bool HasCompletedRegistration();
	std::string fullID();
	std::string const &getName() const;
	std::string &getName();
	std::string const &getNickName() const;
	std::string &getNickName();
	std::string const &getRealname() const;
	std::vector<Channel *> const &getJoinedChannels() const;
	void setAway(std::string msg);
	std::string &getAwayMsg();
	bool isAway();

	/* Methods */
	
	std::string presentation(void);
	std::string whoIsChannels(User *u);
	void joinChan(Channel *chan);
	void leaveChan(Channel *chan);
	

	/* Modes */
	void initModes();
	std::map<char, bool> &getModes();
	std::string setMode(char mode, bool value, std::vector<std::string> params);
	void setOneKeyMode(char mode, bool value);
	void displayModes();
	std::string makeModeString();
	bool hasMode(char mode);
	
	enum
	{
		NICK,
		USER,
		PASS,
		WELCOMED
	};

private:
	std::map<char, bool> _modes;
	std::string _away_msg;
	std::vector<Channel *> joined_chans;
	std::string name;
	std::string nickname;
	std::string real_name;
	std::string buffer;
	std::string ip;	
};

#endif
