//
// Created by antoine on 06/07/22.
//

#include "../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/******************** CONSTRUCTORS ***********************/

Channel::Channel(User * user, string name) :
	_maxUsers(10),
	_user(),
	_name(name),
	_topic("<no topic defined>")
{
	(void)user;
	return ;
}

/********************** GETTERS **************************/

vector<User *>			Channel::getChannelUsers() const
{
	return (this->_user);
}

User*					Channel::getUser(string const & nickname)
{
	//into try catch or send null
	vector<User *>::iterator last = this->_user.end();
	for (vector<User *>::iterator it = this->_user.begin(); it != last; it++)
	{
		if ((*it)->getNickName() == nickname)
			return (*it);
	}
	return (NULL);
}

string 					Channel::getChannelName() const
{
	return (this->_name);
}

string					Channel::getTopic() const
{
	return this->_topic;
}

bool					Channel::getInvite() const
{
	return (this->_invite);
}

/******************* CHECKERS ****************************/

bool 					Channel::isMaxUsers()
{
	int cur = 0;

	vector<User *>::iterator last = this->_user.end();
	for (vector<User *>::iterator it = this->_user.begin(); it != last; it++)
	{
		cur++;
	}
	return (cur >= this->_maxUsers);
}

bool					Channel::isUserHere(User const * usr)
{
	for (vector<User *>::iterator it = _user.begin(); it != _user.end(); it++)
	{
		if (*it == usr)
		{
			return (true);
		}
	}
	return (false);
}

void					Channel::setInvite(bool const & set)
{
	this->_invite = set;
}

void					Channel::setChannelName(string const & name)
{
	this->_name = name;
}

void					Channel::setTopic(string const & topic)
{
	this->_topic = topic;
}

/******************** FUNCTIONS **************************/

void					Channel::addUser(User * user)
{
	this->_user.push_back(user);
}

/******************* DELETE FUNCTIONS *************************/

void					Channel::delUser(User * user)
{
	//into try catch
	vector<User *>::iterator last = this->_user.end();
	for (vector<User *>::iterator it = this->_user.begin(); it != last; it++)
	{
		if (user->getNickName() == (*it)->getNickName())
			this->_user.erase(it);
	}
}

string const 			Channel::printAllUsers()
{
	string result;
	for (vector<User *>::iterator it = _user.begin(); it != _user.end(); it++)
	{
		result += (*it)->getNickName();
		result += " ";
	}
	result.erase(result.size());
	return (result);
}
