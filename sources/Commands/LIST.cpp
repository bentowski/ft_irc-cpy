//
// Created by antoine on 04/07/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

//DONT DO THIS COMMAND

/********************* CHANNEL COMMAND **********************/

//not mandatory but usefull for debugging

/*
 * LIST
 * parameters : [ <channel> *( "," <channel> ) [ <target> ] ]
 */

void		list_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** List command called ***" << endl;
	if (!srv.check_command(&usr, 1, params))
		return ;
	vector<Channel *> chans = srv.getChannels();
	for (vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		srv.ft_reply(&usr, RPL_LIST, (*it)->getChannelName(), "1", (*it)->getTopic());
	}
	srv.ft_reply(&usr, RPL_LISTEND);
	//std::cout << "list command called " << std::endl;
}
