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

void	nick_cmd(Server & srv, User & usr, vector<string> params)
{
	//cout << "*** Nick command called ***" << endl;
	string	tmp = usr.getNickName();
	string	buf;

	if (params.size() == 1)
	{
		usr.resetRdySend();
		srv.ft_error(&usr, ERR_NEEDMOREPARAMS);
		return ;
	}
	if (params.size() > 2 || params[1].length() > 9 || params[1].length() == 0
		|| (params[1].find(',') != params[1].npos) || (params[1].find('#') != params[1].npos))
	{
		usr.resetRdySend();
		srv.ft_error(&usr, ERR_ERRONEUSNICKNAME, params[1]);
		return ;
	}
	if (srv.searchNick(params[1]))
	{
		usr.decreaseRdySend();
		srv.ft_error(&usr, ERR_NICKNAMEINUSE, params[1]);
		return ;
	}

	usr.setNickName(params[1]);
	vector<Channel *> chans = srv.getChannels();
	for (vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		User * user = (*it)->getUser(usr.getNickName());
		if (user)
		{
			user->setNickName(params[1]);
		}
	}
	srv.ft_notice(&usr, &usr, NTC_NICK(usr.getNickName()));
	usr.setPrefix();
	if (usr.getRdySend() == 2)
		usr.setRdySend();
	//std::cout << tmp << "'s nickname becomes " << usr.getNickName() << std::endl;
}
