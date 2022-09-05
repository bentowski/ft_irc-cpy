//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/********************* USER COMMAND **********************/

/*
 * QUIT
 * Parameters <quit message>
 */

void	quit_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** Quit command called ***" << endl;
	if (!srv.check_command(&usr, 1, params))
		return ;
	string msg = "";
	if (params.size() >= 2)
	{
		for (vector<string>::iterator it = params.begin() + 1; it != params.end();it++)
		{
			for (size_t i = 0; i < (*it).size(); i++)
				msg.push_back((*it)[i]);
			msg.push_back(' ');
		}
	}
	vector<Channel *> chans = srv.getChannels();
	for (vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		User * user = (*it)->getUser(usr.getNickName());
		if (user)
		{
			user->quitChannel(*it);
			(*it)->delUser(user);
			if ((*it)->getChannelUsers().empty())
			{
				srv.deleteChannel(*it);
			}
		}
	}
	usr.setToClose(1);
	//std::cout << "quit command called" << std::endl;
}
