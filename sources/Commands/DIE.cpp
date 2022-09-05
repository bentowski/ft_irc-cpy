//
// Created by antoine on 05/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/******************** OPERATOR COMMAND ***********************/

void	die_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** Die command called ***" << endl;
	(void)params;
	if (!usr.isOperator())
	{
		srv.ft_error(&usr, ERR_NOPRIVILEGES);
		return ;
	}
	if (params.size() == 1 && usr.getWelcome())
		srv.setState(0);
	//std::cout << "Server shutdown..." << std::endl;
}
