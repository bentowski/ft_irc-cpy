//
// Created by antoine on 04/07/22.
//


#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* OPERATOR COMMAND **********************/

/*
 * OPER
 * A normal user uses the OPER command to obtain operator privileges.
 * The combination of name and password are required to gain operator privileges.
 *  ERR_NEEDMOREPARAMS  RPL_YOUREOPER ERR_NOOPERHOST   ERR_PASSWDMISMATCH
 */

void	oper_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** Oper command called ***" << endl;
	if (!srv.check_command(&usr, 3, params))
		return ;
	else
	{
		//IRCOperator
		if (params[1] == OPER_NAME)
		{
			if (params[2] == OPER_PASS)
			{
				//RPL_YOUREOPER
				usr.setOperator(1);
				srv.ft_notice(&usr, &usr, NTC_MODE(usr.getNickName(), "+o"));
				srv.ft_reply(&usr, RPL_YOUREOPER);
				return ;
			}
			//ERR_PASSWDMISMATCH
			srv.ft_error(&usr, ERR_PASSWDMISMATCH);
			return ;
		}
		//ERR_NOOPERHOST
		srv.ft_error(&usr, ERR_NOOPERHOST);
		return ;
	}
	//std::cout << "oper command called" << std::endl;
}
