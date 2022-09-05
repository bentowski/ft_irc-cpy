//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* USER COMMAND **********************/

/*
 * Command: PASS
 * Parameters: <password>
 * Create a password variable (std::string)
 * Erreurs : ERR_NEEDMOREPARAMS ERR_ALREADYREGISTERED
 */

void	pass_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** Pass command called ***" << endl;
	if (params.size() == 2)
	{
		if (params[1] == srv.getPassword())
		{
			usr.setPassword(params[1]);
			string msg(":" + usr.getPrefix() + " PASS : ¯\\_(ツ)_/¯\r\n");
			srv.sendBuffer(&usr, msg);
			return;
		}
		else
		{
			srv.ft_error(&usr, ERR_PASSWDMISMATCH);
			return ;
		}
	}
	//usr.setToClose(1);
	srv.ft_error(&usr, ERR_NEEDMOREPARAMS);
	return ;
}
