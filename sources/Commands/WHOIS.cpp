#include "../../includes/User.hpp"
#include "../../includes/Server.hpp"
#include <list>
# include "../../includes/reply.hpp"
#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

void	who_user(Server & srv, User & usr, vector<string> params, bool wild)
{
	(void)usr;
	if (params.size() == 1 || (params.size() == 2 && params[1][0] == '#'))
	{
		vector<User *> users = srv.getUsers();
		for (vector<User *>::iterator it = users.begin(); it != users.end(); it++)
			if ( (*it)->getNickName() == params[0] || (*it)->getHostname() == params[0] || (*it)->getServerName() == params[0] || (*it)->getRealName() == params[0] )
				srv.ft_reply(&usr, RPL_WHOREPLY, (*it)->getCurrentChannelName(), (*it)->getUserName(), (*it)->getHostname(), (*it)->getServerName(), (*it)->getNickName(), (*it)->getRealName());
	}
	if (wild == true)
		srv.ft_reply(&usr, RPL_ENDOFWHO, "*");
	else
		srv.ft_reply(&usr, RPL_ENDOFWHO, params[0]);
}

void	who_chan(Server & srv, User & usr, vector<string> params, bool wild)
{
	if (usr.getChannelByName(params[1]))
	{
		if (params.size() == 1 || (params.size() == 2 && params[1][0] == '#'))
		{
			vector<User *> users = srv.getUsers();
			for (vector<User *>::iterator it = users.begin(); it != users.end(); it++)
				srv.ft_reply(&usr, RPL_WHOREPLY, (*it)->getCurrentChannelName(), (*it)->getUserName(), (*it)->getHostname(), (*it)->getServerName(), (*it)->getNickName(), (*it)->getRealName());

		}
	}
	srv.ft_reply(&usr, RPL_ENDOFWHO,(wild == true ? "*" : params[0]));
}

void				who_wildcard(Server &srv, User &usr, vector<string> params)
{
	if (usr.getCurrentChannel() != NULL)
	{
		params[0] = usr.getCurrentChannelName();
		who_chan(srv, usr, params, true);
	}
	else
	{
		params[0] = usr.getNickName();
		who_user(srv, usr, params, true);
	}
}

void	whois_cmd(Server & srv, User & usr, vector<string> params)
{
	// cout << "*** Whois command called ***" << endl;
	if (params[0][0] == '#')
		who_chan(srv, usr, params, false); // chan
	else if (params[0] == "*")
		who_wildcard(srv, usr, params);
	else
		who_user(srv, usr, params, false);
}
