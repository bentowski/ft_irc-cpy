//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********* SENDING MESSAGES ************/

/*
 * PRIVMSG
 * <msgtarget> <text to be sent>
 *
           ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
           ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
           ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
           ERR_NOSUCHNICK
           RPL_AWAY
 */

void	privmsg_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Privmsg command called ***" << endl;
	if (!srv.check_command(&usr, 3, params))
		return ;
	else
	{
		if (params[2].size() < 1 || params.size() < 3)
		{
			srv.ft_error(&usr, ERR_NOTEXTTOSEND, NULL);
			return ;
		}
		vector<string> names;
		stringstream ss(params[1]);
		string str;
		while (getline(ss, str,','))
		{
			names.push_back(str);
		}
		// convert vector into params
		string msg;
		vector<string>::iterator last = params.end();
		for (vector<string>::iterator it = params.begin() + 2; it != last; it++)
		{
			string::iterator last_char = (*it).end();
			for (string::iterator it_char = (*it).begin(); it_char != last_char; it_char++)
				msg.push_back(*it_char);
			msg.push_back(' ');
		}

		//what happen if user,,user
		string ret;
		if (((ret = isDouble(names)) != "") && names.size() > 2)
		{
			srv.ft_error(&usr, ERR_TOOMANYTARGETS, ret);
			return ;
		}
		for (vector<string>::iterator memb = names.begin(); memb != names.end(); memb++)
		{
			if ((*memb).size() < 1)
			{
				srv.ft_error(&usr, ERR_NORECIPIENT, params[0]);
				return ;
			}
			Channel * dstc;
			User * dstu;
			if (params[1][0] == '#')
			{
				if ((dstc = srv.getChannelByName(*memb)))
				{
					if (!srv.isChanReal(*memb))
					{
						srv.ft_error(&usr, ERR_NOSUCHNICK, *memb);
						return ;
					}
					if (dstc->getUser(usr.getNickName()))
					{
						vector<User *> usrs = dstc->getChannelUsers();
						for (vector<User *>::iterator it = usrs.begin(); it != usrs.end(); it++)
						{
							if ((*it)->getNickName() != usr.getNickName())
								srv.ft_notice(&usr, *it, NTC_PRIVMSG(dstc->getChannelName(), msg));
						}
					}
					else
					{
						srv.ft_error(&usr, ERR_NORECIPIENT, params[0]);
						return ;
					}
				}
				else
				{
					srv.ft_error(&usr, ERR_NOSUCHCHANNEL, *memb);
					return ;
				}

			}
			else if ((dstu = *srv.getUser(*memb)))
			{
				if (!srv.isUserReal(*memb))
				{
					srv.ft_error(&usr, ERR_NOSUCHNICK, *memb);
					return ;
				}
				srv.ft_notice(&usr, dstu, NTC_PRIVMSG(dstu->getNickName(), msg));
			}
			else
			{
				srv.ft_error(&usr, ERR_NOSUCHNICK, *memb);
				return ;
			}
		}
	}
	//cout << "privmsg command called" << endl;
}
