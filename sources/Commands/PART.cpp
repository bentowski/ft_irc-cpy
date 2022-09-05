//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* CHANNEL COMMAND **********************/

/*
 * PART
 * parameters: <channel> *( "," <channel> ) [ <Part Message> ]
 *         ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_NOTONCHANNEL

 */

void	part_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Part command called ***" << endl;
	if (!srv.check_command(&usr, 2, params))
		return ;
	string msg = "";
	if (params.size() >= 3)
	{
		for (vector<string>::iterator it = params.begin() + 2; it != params.end();it++)
		{
			for (size_t i = 0; i < (*it).size(); i++)
				msg.push_back((*it)[i]);
			msg.push_back(' ');
		}
	}
	vector<string> chans;
	stringstream str(params[1]);
	string s;
	while (getline(str, s, ','))
	{
		chans.push_back(s);
	}
	for (vector<string>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		Channel * chan;
		if ((chan = srv.getChannelByName(*it)))
		{
			if (chan->isUserHere(&usr))
			{
				vector<User *> memb = chan->getChannelUsers();
				for (vector<User *>::iterator i = memb.begin(); i != memb.end();i++)
				{
						if (msg.empty())
							srv.ft_notice(&usr, *i, NTC_PART(chan->getChannelName()));
						else
						{
							if (msg[0] == ':')
								msg.erase(0);
							srv.ft_notice(&usr, *i, NTC_PART_MSG(chan->getChannelName(), msg));
						}
				}
				usr.quitChannel(chan);
				chan->delUser(&usr);
				if (chan->getChannelUsers().empty())
				{
					srv.deleteChannel(chan);
				}
			}
			else
			{
				srv.ft_error(&usr, ERR_NOTONCHANNEL, chan->getChannelName());
				return ;
			}
		}
		else
		{
			srv.ft_error(&usr, ERR_NOSUCHCHANNEL, *it); //ERR NO SUCH CHANNEL
			return ;
		}
	}
	//std::cout << "part command end" << std::endl;
}
