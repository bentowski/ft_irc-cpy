//
// Created by alangloi on 6/24/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* USER COMMAND **********************/

void	user_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** User command called ***" << endl;
	if (params.size() < 5)
	{
		srv.ft_error(&usr, ERR_NEEDMOREPARAMS, params[0]);
		return ;
	}
	if (usr.getUserName() != "" && usr.getHostname() != "" && usr.getServerName() != "" && usr.getRealName() != "")
	{
		srv.ft_error(&usr, ERR_ALREADYREGISTRED);
		return ;
	}
	if (params[1].length())
		usr.setUserName(params[1]);
	if (params[2].length())
		usr.setHostName(params[2]);
	if (params[2].length())
		usr.setServerName(params[3]);

	string real = "";
	if (params.size() >= 5)
	{
		for (vector<string>::iterator it = params.begin() + 2; it != params.end();it++)
		{
			for (size_t i = 0; i < (*it).size(); i++)
				real.push_back((*it)[i]);
			real.push_back(' ');
		}
	}
	usr.setRealName(real);
	string msg("USER: " + usr.getUserName() + " " + usr.getHostname() + " " + usr.getServerName() + " " + usr.getRealName());
	srv.ft_notice(&usr, &usr, msg);
	if (usr.getRdySend() == 3)
		usr.setRdySend();
	usr.setPrefix();
	//std::cout << "user command called = " << usr.getUserName() << std::endl;
}

/*
 * Command: 	USER
 * Parameters:	<user> <mode> <unused> <realname>
 * The USER command is used at the beginning of connection to specify
 * the username, hostname and realname of a new user.
 *  ERR_NEEDMOREPARAMS      ERR_ALREADYREGISTRED
 */
