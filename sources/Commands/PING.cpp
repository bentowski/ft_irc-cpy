//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

void	ping_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** Ping command called ***" << endl;
	if (!srv.check_command(&usr, 1, params))
		return ;
	srv.sending(usr.getFdUser(), "PONG\r\n");
	//std::cout << "ping command called" << std::endl;
}
