//
// Created by antoine on 05/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

//DONT DO THIS COMMAND

/*********************** OPERATOR COMMAND ************************/

void	wallops_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Wallops command called ***" << endl;
	if (!srv.check_command(&usr, 2, params))
		return ;
	if (!usr.isOperator())
	{
		srv.ft_reply(&usr, ERR_NOPRIVILEGES);
		return ;
	}
	string msg;
	if (params.size() >= 2)
	{
		for (vector<string>::iterator it = params.begin() + 1; it != params.end();it++)
		{
			for (size_t i = 0; i < (*it).size(); i++)
				msg.push_back((*it)[i]);
			msg.push_back(' ');
		}
	}
	cout << "msg = " << msg << endl;
	vector<User *> users = srv.getUsers();
	for (vector<User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it)->getNickName() != usr.getNickName())
			srv.ft_notice(&usr, *it, NTC_WALLOPS((*it)->getNickName(), msg));
	}
	//cout << "wallops command called" << cout;
}
