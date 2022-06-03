/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:59:04 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/18 12:05:51 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <list>

/*
**         INVITE  - Invite a client to an invite-only channel (mode +i) //
**         KICK    - Eject a client from the channel
**         MODE    - Change the channel's mode, as well as
**                   members' privileges
**         PRIVMSG - Sending messages to the channel (mode +n, +m, +v)
**         TOPIC   - Change the channel topic in a mode +t channel
*/

class Channel
{

public:
	Channel();
	Channel(std::string name, User *creator);
	Channel(Channel const &src);
	~Channel();
	Channel &operator=(Channel const &src);

	/* Accessors + infos */

	bool isInvited(User *user);
	bool isCorrectPass(std::string candidate);
	bool isInChan(User *u);
	bool findByName(std::string nick, User **u);
	bool matchInviteMask(User *u);
	bool matchBannedMask(User *u);
	bool matchExceptMask(User *u);
	bool isTopicSet();
	bool hasKey();
	bool hasMode(char mode);
	bool isBanned(User *u);
	bool isOperator(User *u);
	bool isVoiced(User *u);
	bool isOwner(User *u);
	bool isPrivateForUser(User *u);
	void setTopic(std::string topic);
	size_t getLimit();
	void removeBannedFromUsers();
	std::map<char, bool> &getModes();
	std::string &getTopic();
	std::string &getName();
	std::vector<std::string> &getBannedMasks();
	std::vector<std::string> &getInvitedMasks();
	std::vector<std::string> &getExceptMasks();
	std::map<std::string *, User *> &getUsers();

	/* Methods */

	void add_user(User *new_user);
	void remove_user(User *new_user);
	void addOperator(User *to_add);
	void removeOperator(User *to_del);
	void addBanned(User *to_add);
	void removeBanned(User *to_del);
	void addVoiced(User *to_add);
	void removeVoiced(User *to_del);
	void addToInviteList(User *to_add);
	void removeFromInviteList(User *to_del);
	void printUsers();
	void printBanned();
	void seeBannedmasks();

	/* Modes related function */
	std::string setMode(User *u, char mode, bool value, std::string param);
	void displayModes();

	std::string _name; // nom du chan
	std::string _topic;

private:
	std::map<std::string *, User *> _users;
	std::vector<User *> _operators;
	std::list<User *> _banned;
	User *_owner;
	User *_creator;
	std::map<char, bool> _modes;
	std::string _password;
	std::vector<User *> _invited;
	std::vector<User *> _voiced;
	std::vector<std::string> _bannedMasks;
	std::vector<std::string> _invitedMasks;
	std::vector<std::string> _exceptMasks;
	size_t _limit;
};

std::ostream &operator<<(std::ostream &o, Channel &i);

std::string printNames(Channel *chan, User *u);
std::string printModes(Channel *chan);

#endif /* ********************************************************* CHANNEL_H */
