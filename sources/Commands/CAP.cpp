//
// Created by alangloi on 6/24/22.
//

#include "../../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

//optional for the moment

/********************* USER COMMAND **********************/

void	cap_cmd(Server & srv, User & usr, std::vector<std::string> params)
{
	//cout << "*** Cap command called ***" << endl;
	(void)srv;
	if (params.size() < 2)
		return ;
	transform(params[1].begin(), params[1].end(), params[1].begin(), ::toupper);
	if (params.size() != 2 || !(params[1] == "LS"))
		return;
	if (usr.getRdySend() == 0)
		usr.setRdySend();
	//cout << "*** Cap command success ***" << endl;
}
