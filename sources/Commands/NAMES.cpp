//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* CHANNEL COMMAND **********************/

//not mandatory but usefull for bebugging

/*
 * NAMES
 * parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
 */

string		add_nick(vector<User *> & users)
{
	string	ret;

	for (size_t i = 0; i < users.size(); i++)
	{
		if (!users[i]->isInvisible())
		{
			ret += users[i]->getNickName();
			if (i + 1 != users.size())
				ret += ", ";
		}
	}
	return ret;
}

void		names_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Names command called ***" << endl;
	(void)usr;

	vector<User *>	users;
	string			ret = "\n";

	if (!srv.check_command(&usr, 1, params))
		return ;
	if (params.size() == 1)
	{
		users = srv.getUsers();
		ret += srv.getServerName() + " = { ";
		ret += add_nick(users);
		ret += " }";
		srv.ft_reply(&usr, RPL_NAMREPLY, srv.getServerName(), ret);
		srv.ft_reply(&usr, RPL_ENDOFNAMES, srv.getServerName());
	}
	else if (params.size() > 1)
	{
		string			schan = "";
		for (size_t i = 1; i < params.size(); i++)
		{
			stringstream	ss(params[i]);
			string			s;
			while (getline(ss, s, ','))
			{
				users.clear();
				schan += s + " ";
				Channel * test = srv.getChannelByName(s);
				if (test != NULL)
				{
					users = test->getChannelUsers();
					ret += s + " = { ";
					ret += add_nick(users);
					ret += " }\n";
					srv.ft_reply(&usr, RPL_NAMREPLY, s, ret);
				}
				else
				{
					srv.ft_error(&usr, ERR_NOSUCHCHANNEL, s);
					return ;
				}
			}
		}
		srv.ft_reply(&usr, RPL_ENDOFNAMES, schan);
	}
	//std::cout << "names command called" << std::endl;
}
