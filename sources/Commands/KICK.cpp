//
// Created by alangloi on 6/24/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* USER COMMAND **********************/

/* Gives a nickname to given user or change the existing one:
 * Erreurs:
 *	ERR_NONICKNAMEGIVEN ERR_ERRONEUSNICKNAME  ERR_NICKNAMEINUSE    ERR_NICKCOLLISION ERR_RESTRICTED ERR_UNAVAILRESOURCE
 */

void	kick_cmd(Server & srv, User & usr, vector<string> params)
{
	if (!srv.check_command(&usr, 3, params))
		return ;
	if (!usr.isOperator())
	{
		srv.ft_error(&usr, ERR_NOPRIVILEGES);
		return ;
	}
	Channel * chan = srv.getChannelByName(params[1]);
	if (!chan)
	{
		srv.ft_error(&usr, ERR_NOSUCHCHANNEL, params[1]);
		return ;
	}
	User * user = chan->getUser(params[2]);
	if (!user)
	{
		srv.ft_error(&usr, ERR_NOSUCHNICK, params[2]);
		return ;
	}
	if (!chan->isUserHere(user))
	{
		srv.ft_error(&usr, ERR_NOTONCHANNEL, chan->getChannelName());
		return ;
	}
	if (&usr == user)
	{
		srv.ft_error(&usr, ERR_USERONCHANNEL);
		return ;
	}
	string msg;
	if (params.size() >= 3)
	{
		for (vector<string>::iterator it = params.begin() + 2; it != params.end();it++)
		{
			for (size_t i = 0; i < (*it).size(); i++)
				msg.push_back((*it)[i]);
			msg.push_back(' ');
		}
	}
	vector<User *> memb = chan->getChannelUsers();
	for (vector<User *>::iterator it = memb.begin(); it != memb.end(); it++)
	{
			srv.ft_notice(&usr, *it, NTC_KICK(chan->getChannelName(), user->getNickName(), msg));
	}
	chan->delUser(user);
	user->quitChannel(chan);
	if (chan->getChannelUsers().empty())
	{
		srv.deleteChannel(chan);
	}
}
