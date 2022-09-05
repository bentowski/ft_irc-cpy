//
// Created by antoine on 05/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

//DONT DO THIS COMMAND

/*********************** OPERATOR COMMAND ************************/

void	invite_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Invite command called ***" << endl;
	if (!srv.check_command(&usr, 3, params))
		return ;
	if (!usr.isOperator())
	{
		srv.ft_error(&usr, ERR_NOPRIVILEGES);
		return ;
	}
	//set current channel
	Channel * chan = srv.getChannelByName(params[2]);
	if (!chan)
	{
		srv.ft_error(&usr, ERR_NOSUCHCHANNEL, params[2]);
		return ;
	}
	User * user = srv.getUserInstance(params[1]);
	if (!user)
	{
		srv.ft_error(&usr, ERR_NOSUCHNICK, params[1]);
		return ;
	}
	if (chan->getUser(user->getNickName()))
	{
		srv.ft_error(&usr, ERR_USERONCHANNEL, user->getNickName());
		return ;
	}
	srv.ft_notice(&usr, user, NTC_INVITE(chan->getChannelName(), user->getNickName()));
	srv.ft_reply(&usr, RPL_INVITING, user->getNickName(), chan->getChannelName());

	//cout << "*** Cap command success ***" << endl;
}
