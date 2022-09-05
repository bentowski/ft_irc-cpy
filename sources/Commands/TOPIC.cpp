#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

void		topic_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Topic command called ***" << endl;
	if (!srv.check_command(&usr, 2, params))
		return ;
	if (params.size() == 2)
	{
		Channel * test = srv.getChannelByName(params[1]);
		if (test)
		{
			if (!usr.getChannelByName(params[1]))
			{
				srv.ft_error(&usr, ERR_NOTONCHANNEL, params[1]);
				return ;
			}
			else
			{
				srv.ft_reply(&usr, RPL_TOPIC, test->getChannelName(), test->getTopic());
				return ;
			}
		}
		else
		{
			srv.ft_error(&usr, ERR_NOSUCHCHANNEL, params[1]);
			return ;
		}
	}
	else if (params.size() > 2)
	{
		Channel * test = srv.getChannelByName(params[1]);
		if (test != NULL)
		{
			if (!usr.getChannelByName(params[1]))
			{
				srv.ft_error(&usr, ERR_NOTONCHANNEL, params[1]);
				return ;
			}
			else
			{
				if (usr.isOperator())
				{
					string	ret = "";
					for (size_t i = 2; i < params.size(); i++)
					{
						ret += params[i];
						if (i + 1 != params.size())
							ret += " ";
					}
					test->setTopic(ret);
					vector<User *> memb = test->getChannelUsers();
					for (vector<User *>::iterator it = memb.begin(); it != memb.end(); it++)
					{
						//if ((*it)->getNickName() != usr.getNickName())
							srv.ft_notice(&usr, *it, NTC_TOPIC(test->getChannelName(), ret));
					}
					srv.ft_reply(&usr, RPL_TOPIC, test->getChannelName(), test->getTopic());
					return ;
				}
				else
				{
					srv.ft_error(&usr, ERR_NOPRIVILEGES);
					return ;
				}
			}
		}
		else
		{
			srv.ft_error(&usr, ERR_NOSUCHCHANNEL, params[1]);
			return ;
		}
	}
}

// Command: TOPIC
// Parameters: <channel> [ <topic> ]
//
// The TOPIC command is used to change or view the topic of a channel.
// The topic for channel <channel> is returned if there is no <topic>
// given.  If the <topic> parameter is present, the topic for that
// channel will be changed, if this action is allowed for the user
// requesting it.  If the <topic> parameter is an empty string, the
// topic for that channel will be removed.
//
// Numeric Replies:
//
// 	[x]ERR_NEEDMOREPARAMS				ERR_NOTONCHANNEL
// 	RPL_NOTOPIC						RPL_TOPIC
// 	ERR_CHANOPRIVSNEEDED			ERR_NOCHANMODES
//
// Examples:
//
// :WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic ; User Wiz setting the
// 							topic.
//
// TOPIC #test :another topic	; Command to set the topic on #test
// 							to "another topic".
//
// TOPIC #test :				; Command to clear the topic on
// 							#test.
//
// TOPIC #test					; Command to check the topic for
// 							#test.
