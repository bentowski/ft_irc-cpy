//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* CHANNEL COMMAND **********************/

/*
 * JOIN command
 * ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
               / "0"
*/

/*
 * I don't know how to use theses :
 * ERR_NOSUCHCHANNEL
 * RPL_TOPIC
 * ERR_BADCHANNELKEY
 * ERR_BADCHANMASK
 * ERR_TOOMANYCHANNELS
 * ERR_UNAVAILRESOURCE
 */

/* to do :
 * keys are coming with a virgule, need to parse it
 * check the symbol before the name of the channel for setting its mode
 */

bool	user_join_channel(Server & srv, User & usr, Channel & existing)
{
	(void)srv;
	if (existing.isMaxUsers())
	{
		srv.ft_error(&usr, ERR_CHANNELISFULL, existing.getChannelName());
		return (false);
	}
	if (usr.isInvisible())
	{
		usr.setInvisible(0);
		srv.ft_notice(&usr, &usr, NTC_MODE(usr.getNickName(), "-i"));
	}
	existing.addUser(&usr);
	usr.addChannel(&existing);
	vector<User *> memb = existing.getChannelUsers();
	for (vector<User *>::iterator it = memb.begin(); it != memb.end(); it++)
	{
		if ((*it)->getNickName() != usr.getNickName())
			srv.ft_notice(&usr, *it, NTC_JOIN(existing.getChannelName()));
	}
	return (true);
}

Channel*	user_create_channel(Server &srv, User &usr, string &name)
{
	//cout << "it is ? " << usr.isMaxChannel() << endl;
	if (usr.isMaxChannel())
	{
		srv.ft_error(&usr, ERR_TOOMANYCHANNELS, name);
		return (NULL);
	}
	Channel * new_chan = srv.addChannel(&usr, name);
	new_chan->addUser(&usr);
	usr.addChannel(new_chan);
	if (usr.isInvisible())
	{
		usr.setInvisible(false);
		srv.ft_notice(&usr, &usr, NTC_MODE(usr.getNickName(), "-i"));
	}
	return (new_chan);
}

bool	quit_all_chan(Server &srv, User &usr, vector<string> &params)
{
	if (params[1] == "0" && params.size() < 2)
	{
		usr.clearAllChannels();
		srv.delUserAllChannel(&usr);
		return (true);
	}
	return (false);
}

void	reply_channel_joined(Server & srv, User & usr, Channel & chan)
{
	srv.ft_reply(&usr, RPL_NAMREPLY, chan.getChannelName(), chan.printAllUsers());
	srv.ft_reply(&usr, RPL_ENDOFNAMES, chan.getChannelName());
}

void	join_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Join command called ***" << endl;
	if (!srv.check_command(&usr, 2, params))
		return ;
	else
	{
		//check is user is registered
		if (quit_all_chan(srv, usr,params))
			return ;
		if (params[1][0] != '#')
		{
			srv.ft_error(&usr, ERR_BADCHANMASK);
			return ;
		}
		stringstream ss(params[1]);
		string str;
		vector<string> chans;
		while (getline(ss, str, ','))
		{
			if (str.rfind('#') == 0)
				chans.push_back(str);
			else
			{
				srv.ft_error(&usr, ERR_BADCHANMASK, str);//ERR_NOSUCHCHANNEL
				return ;
			}
		}
		string ret;
		if (((ret = isDouble(chans)) == "") && chans.size() > 1)
		{
			srv.ft_error(&usr, ERR_TOOMANYTARGETS, ret);//ERR_TOOMANYTARGETS
			return ;
		}
		for (vector<string>::iterator it = chans.begin(); it != chans.end(); it++)
		{
			if (srv.getChannelByName(*it) && usr.getChannelByName(*it))
			{
				srv.ft_error(&usr, ERR_ALREADYREGISTRED);
				return ;
			}
			if ((*it)[0] != '#' || (*it).size() < 2 || (*it).size() > 30)
			{
				srv.ft_error(&usr, ERR_BADCHANMASK, *it); //ERR_NOSUCHCHANNEL
				return ;
			}
			Channel *existing;
			if ((existing = srv.searchChannel(*it)))
			{
				if (!user_join_channel(srv, usr, *existing))
					return ;
				reply_channel_joined(srv, usr, *existing);
			}
			else
			{
				Channel * new_chan;
				new_chan = user_create_channel(srv, usr, *it);
				if (!new_chan)
					return ;
				srv.ft_notice(&usr, &usr, NTC_JOIN(new_chan->getChannelName()));
				reply_channel_joined(srv, usr, *new_chan);
			}
		}
	}
	//cout << "join command exit" << endl;
}
