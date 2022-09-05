//
// Created by blyzance on 18/06/22.
//


#include "../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

/******************** CONSTRUCTORS **********************/

// Server::Server(int const & portNum) :
// 	map_cmd(),
// 	_fd(-1),
// 	_fdMax(-1),
// 	_serverName(SERVER_NAME),
// 	_size(0),
// 	_user(),
// 	_oper(),
// 	_channel(),
// 	_portNum(portNum),
// 	_state(1),
// 	_password(),
// 	_param(),
// 	_maxChannels(10)
// {
// 	this->initServer();
// }

Server::Server(int const & portNum, string const & passw) :
	map_cmd(),
	_fd(-1),
	_fdMax(-1),
	_serverName(SERVER_NAME),
	_size(0),
	_user(),
	_oper(),
	_channel(),
	_portNum(portNum),
	_state(1),
	_password(passw),
	_param(),
	_maxChannels(10),
	_ver(VERSION)
{
	this->setDate();
	this->initServer();
}

Server::~Server()
{
	for (vector<Channel *>::iterator ch = this->_channel.begin(); ch != this->_channel.end(); ch++)
		delete(*ch);
	for (vector<User *>::iterator it = this->_user.begin(); it != this->_user.end(); it++)
		delete(*it);
	this->_user.clear();
	return;
}

/******************** CONNECTION **********************/

void 					Server::initServer()
{
	this->establishConnection();
	this->_fdMax = this->_fd;
	this->createServerAddr(this->_portNum);

	int optval = 1;
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0)
	{
		cout << RED << "Error: setting socket failed..." << RESET << endl;
		this->setState(0);
		return ;
	}
	fcntl(this->_fd, F_SETFL, O_NONBLOCK);
	this->bindServer();
	this->_size = sizeof(this->getServerAddr());
	if (listen(this->_fd, this->getServerAddr().sin_port) < 0)
	{
		cout << RED << "Error: listen failed..." << RESET << endl;
		this->setState(0);
		return ;
	}
	this->initCommand();
	this->initReplyTree();
	this->initErrorTree();
}

void					 Server::establishConnection(void)
{
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd < 0)
	{
		cout << RED << "Error: connection failed..." << RESET << endl;
		this->setState(0);
		return ;
	}
	cout << GREEN << "Server Socket connection created..." << RESET << endl;
}

void					Server::createServerAddr(int const & portNum)
{
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
	this->_serverAddr.sin_port = htons(portNum);
}

int						Server::acceptUser(socklen_t size)
{
	int fd = accept(this->_fd, (struct sockaddr*)&this->_serverAddr,
						  reinterpret_cast<socklen_t *>(&size));
	if (fd < 0)
	{
		cout << RED << "Error: accept failed..." << RESET << endl;
		return (-1);
	}
	vector<User *>::iterator it = _user.begin();
	while (it != _user.end() && (*it)->getFdUser() > fd)
		it++;
	_user.insert(it, new User(fd));
	return (fd);
}

void					Server::closeUser(User const &  user)
{
	close(user.getFdUser());
}


int						Server::bindServer()
{
	if (bind(this->_fd, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr)) < 0 )
	{
		cout << RED <<  "Error: binding socket failed..." << RESET << endl;
		setState(0);
		return (0);
	}
	return (1);
}

void					Server::initCommand()
{
	map_cmd["CAP"] 		= 	cap_cmd;
	map_cmd["DIE"] 		= 	die_cmd;
	map_cmd["JOIN"] 	= 	join_cmd;
	map_cmd["KICK"] 	= 	kick_cmd;
	map_cmd["LIST"] 	= 	list_cmd;
	map_cmd["MODE"] 	= 	mode_cmd;
	map_cmd["NAMES"] 	= 	names_cmd;
	map_cmd["NICK"] 	=	nick_cmd;
	map_cmd["NOTICE"] 	= 	notice_cmd;
	map_cmd["OPER"] 	= 	oper_cmd;
	map_cmd["PART"] 	=	part_cmd;
	map_cmd["PASS"] 	= 	pass_cmd;
	map_cmd["PING"] 	= 	ping_cmd;
	map_cmd["PRIVMSG"] 	=	privmsg_cmd;
	map_cmd["QUIT"] 	=	quit_cmd;
	map_cmd["USER"] 	= 	user_cmd;
	map_cmd["TOPIC"] 	= 	topic_cmd;
	map_cmd["WALLOPS"] 	= 	wallops_cmd;
	map_cmd["WHOIS"] 	= 	whois_cmd;
	map_cmd["INVITE"]	=	invite_cmd;
}

void 					Server::welcome(int const & fd)
{
	User * usr = *this->getUser(fd);
	if (usr->check_if_complete() == 0)
		return;
	usr->setWelcome(1);
	ft_reply(usr, RPL_WELCOME, usr->getPrefix());
	ft_reply(usr, RPL_YOURHOST, _serverName, _ver);
	ft_reply(usr, RPL_CREATED, this->getDate());
	ft_reply(usr, RPL_MYINFO, _serverName, _ver, "io", "0o");
	sendBuffer(*getUser(fd), "                                                           \r\n");
	sendBuffer(*getUser(fd), "                 █████▒▄▄▄█████▓    ██▓ ██▀███   ▄████▄    \r\n");
	sendBuffer(*getUser(fd), "               ▓██   ▒ ▓  ██▒ ▓▒   ▓██▒▓██ ▒ ██▒▒██▀ ▀█    \r\n");
	sendBuffer(*getUser(fd), "               ▒████ ░ ▒ ▓██░ ▒░   ▒██▒▓██ ░▄█ ▒▒▓█    ▄   \r\n");
	sendBuffer(*getUser(fd), "               ░▓█▒  ░ ░ ▓██▓ ░    ░██░▒██▀▀█▄  ▒▓▓▄ ▄██▒  \r\n");
	sendBuffer(*getUser(fd), "               ░▒█░      ▒██▒ ░    ░██░░██▓ ▒██▒▒ ▓███▀ ░  \r\n");
	sendBuffer(*getUser(fd), "                ▒ ░      ▒ ░░      ░▓  ░ ▒▓ ░▒▓░░ ░▒ ▒  ░  \r\n");
	sendBuffer(*getUser(fd), "                ░          ░        ▒ ░  ░▒ ░ ▒░  ░  ▒     \r\n");
	sendBuffer(*getUser(fd), "                ░ ░      ░          ▒ ░  ░░   ░ ░          \r\n");
	sendBuffer(*getUser(fd), "                                    ░     ░     ░ ░        \r\n");
	sendBuffer(*getUser(fd), "                                                ░          \r\n");
	sendBuffer(*getUser(fd), "                    By Ivan, Benjamin and Antoine          \r\n");
	sendBuffer(*getUser(fd), "--------------------------------------------------------------------------\r\n");
	sendBuffer(*getUser(fd), "- LIST OF COMMANDS :              - ACTION                    - OPERATOR -\r\n");
	sendBuffer(*getUser(fd), "--------------------------------------------------------------------------\r\n");
	sendBuffer(*getUser(fd), "- DIE                             - stops server              -    YES   -\r\n");
	sendBuffer(*getUser(fd), "- INVITE <User> <Channel>         - invite user               -    YES   -\r\n");
	sendBuffer(*getUser(fd), "- JOIN <Channel>                  - joins/create channel      -          -\r\n");
	sendBuffer(*getUser(fd), "- KICK <Channel> <User> <Message> - kick user out             -    YES   -\r\n");
	sendBuffer(*getUser(fd), "- LIST                            - list all channels         -          -\r\n");
	sendBuffer(*getUser(fd), "- NICK <Name>                     - sets nickname             -          -\r\n");
	sendBuffer(*getUser(fd), "- OPER <Name> <Password>          - set operator mode         -          -\r\n");
	sendBuffer(*getUser(fd), "- PART <Channel>                  - quit channel              -          -\r\n");
	sendBuffer(*getUser(fd), "- PASS <Password>                 - sets password             -          -\r\n");
	sendBuffer(*getUser(fd), "- QUIT <Message>                  - quit server               -          -\r\n");
	sendBuffer(*getUser(fd), "- TOPIC <Channel> <Topic>         - show/changes topic        -   NO/YES -\r\n");
	sendBuffer(*getUser(fd), "- WALLOPS <Message>               - send message to all users -     YES  -\r\n");
	sendBuffer(*getUser(fd), "--------------------------------------------------------------------------\r\n");

}

void					Server::parse_buffer_command(string const & str)
{
	this->_param.clear();
	stringstream 			ss(str);
	string					s;
	vector<string>			tmp;

	while (getline(ss, s, '\r'))
	{
		stringstream o(s);
		string u;
		while (getline(o, u, ' '))
			if (u.length() && u != "\n")
				tmp.push_back(u);
		if (tmp.size() > 0)
		{
			size_t x = tmp.size() - 1;
			if (tmp[x].size() > 0)
			{
				size_t y = tmp[x].size() - 1;
				if (tmp[x][y] == '\n')
					tmp[x].replace(y, 1, "\0");
				this->_param.push_back(tmp);
			}
		}
		tmp.clear();
		getline(ss, s, '\n');
	}
}

void				Server::printParam()
{
	int	i = 0;

	for (vector<vector<string> >::iterator it = this->_param.begin(); it != this->_param.end(); it++)
	{
		cout << "param[" << i << "] = { ";
		for (vector<string>::iterator jt = (*it).begin(); jt != (*it).end(); jt++)
			cout << *jt << "; ";
		cout << " }" << endl;
		i++;
	}
}

string 				Server::printListChannels()
{
	string ret;
	for (vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++)
	{
		ret += (*it)->getChannelName();
		ret += ' ';
	}
	ret.erase(ret.size());
	return (ret);
}

void 				Server::execCommand(int const & fd)
{
	vector<string> test;
	test.push_back("CAP");
	test.push_back("DIE");
	test.push_back("JOIN");
	test.push_back("KICK");
	test.push_back("LIST");
	test.push_back("MODE");
	test.push_back("NAMES");
	test.push_back("NICK");
	test.push_back("NOTICE");
	test.push_back("OPER");
	test.push_back("PART");
	test.push_back("PASS");
	test.push_back("PING");
	test.push_back("PRIVMSG");
	test.push_back("INVITE");
	test.push_back("QUIT");
	test.push_back("USER");
	test.push_back("TOPIC");
	test.push_back("WALLOPS");

	for (size_t x = 0; x < this->_param.size(); x++)
	{
		transform(this->_param[x][0].begin(), this->_param[x][0].end(), this->_param[x][0].begin(), ::toupper);
		for (size_t y = 0; y < test.size(); y++)
		{
			if (this->_param[x][0] == test[y])
			{
				this->map_cmd.find(this->_param[x][0])->second(*this, *(*(this->getUser(fd))), this->_param[x]);
				break;
			}
			if (y + 1 == test.size())
				this->ft_error((*this->getUser(fd)), ERR_UNKNOWNCOMMAND, this->_param[x][0]);
		}
		if ((*(this->getUser(fd)))->getToClose() == 1)
			break;
	}
}

bool				Server::check_command(User * u, size_t want, vector<string> command)
{
	if (!u->getWelcome())
	{
		ft_error(u, ERR_NOTREGISTERED, "");
		return false;
	}
	if (command.size() < want)
	{
		ft_error(u, ERR_NEEDMOREPARAMS, command[0]);
		return false;
	}
	return true;
}

int					Server::searchNick(string const & nick)
{
	vector<User *>::iterator last = this->_user.end();
	for (vector<User *>::iterator it = this->_user.begin(); it != last; it++)
		if ((*it)->getNickName() == nick)
			return ((*it)->getFdUser());
	return (0);
}

void				Server::sendToChan(string const & name, string const & msg)
{
	vector<User *> chan_usr = this->getChannelByName(name)->getChannelUsers();
	vector<User *>::iterator last = chan_usr.end();
	for (vector<User *>::iterator it = chan_usr.begin(); it != last; it++)
		sendBuffer(*it, msg);
}

void				Server::sendToUser(string const & name, string const &  msg)
{
	sendBuffer(*this->getUser(name), msg);
}

void				Server::sendBuffer(User * dest, string const & content)
{
	sending(dest->getFdUser(), content);
}

void				Server::sending(int fd, string toSend)
{
	cout << YELLOW << "Sending : " << toSend << RESET;
	send(fd, toSend.c_str(), toSend.length(), 0);
}

Channel*			Server::addChannel(User * user, string const & name)
{
	this->_channel.push_back(new Channel(user, name));
	return *(this->_channel.end() - 1);
}

void				Server::deleteChannel(Channel * chan)
{
	for (vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++)
	{
		if ((*it)->getChannelName() == chan->getChannelName())
		{
			delete *it;
			this->_channel.erase(it);
			return ;
		}
	}
}

Channel*			Server::searchChannel(string const & name)
{
	vector<Channel *>::iterator last = this->_channel.end();
	for (vector<Channel *>::iterator it = this->_channel.begin(); it != last; it++)
		if ((*it)->getChannelName() == name)
			return (*it);
	return (NULL);
}

void				Server::delUserAllChannel(User * user)
{
	vector<Channel *>::iterator last = this->_channel.end();
	for (vector<Channel *>::iterator it = this->_channel.begin(); it != last; it++)
	{
		(*it)->delUser(user);
	}
}

void				Server::deleteUser(vector<User *>::iterator user)
{
	delete(*user);
	this->_user.erase(user);
}

/******************** ACCESSORS **********************/

int 				Server::getFdMax() const
{
	return this->_fdMax;
}

int					Server::getFdServer(void) const
{
	return (this->_fd);
}

struct sockaddr_in	Server::getServerAddr() const
{
	return (this->_serverAddr);
}

vector<User *>		Server::getUsers() const
{
	return (this->_user);
}

vector<User *>::iterator				Server::getUser(int const & fd)
{
	vector<User *>::iterator it = this->_user.begin();
	while (it != _user.end() && (*it)->getFdUser() != fd)
		it++;
	return (it);
}

User*					Server::getUserInstance(string const & name)
{
	for (vector<User *>::iterator it = _user.begin(); it != _user.end(); it++)
	{
		if ((*it)->getNickName() == name)
			return (*it);
	}
	return (NULL);
}



vector<User *>::iterator				Server::getUser(string const & nick)
{
	vector<User *>::iterator it = this->_user.begin();
	while (it != _user.end() && (*it)->getNickName() != nick)
		it++;
	return (it);
}

Channel*			Server::getChannelByName(string const & name)
{
	vector<Channel *>::iterator last = this->_channel.end();
	for (vector<Channel *>::iterator it = this->_channel.begin(); it != last; it++)
		if ((*it)->getChannelName() == name)
			return (*it);
	return (NULL);
}

vector<Channel *>	Server::getChannels() const
{
	return (this->_channel);
}

string 				Server::getVersion() const
{
	return (this->_ver);
}

socklen_t			Server::getSize() const
{
	return (this->_size);
}

int 				Server::getPortNum() const
{
	return (this->_portNum);
}

vector<User *>		Server::getOper() const
{
	return (this->_oper);
}

User*				Server::getOper(string const & name)
{
	vector<User *>::iterator last = this->_oper.end();
	for (vector<User *>::iterator it = this->_oper.begin(); it != last; it++)
		if ((*it)->getUserName() == name)
			return (*it);
	return (NULL);
}

int 				Server::getMaxChannel() const
{
	return (this->_maxChannels);
}

bool				Server::getState() const
{
	return	(this->_state);
}

string 				Server::getServerName() const
{
	return (this->_serverName);
}

string				Server::getPassword() const
{
	return (this->_password);
}

string				Server::getDate() const
{
	return this->_date;
}

/********************* MUTATORS *************************/

void				Server::setFdServer(int const & fd)
{
	this->_fd = fd;
}

void				Server::setState(bool const & st)
{
	this->_state = st;
}

void 				Server::setUpFdMax(int const & fdCurrent)
{
	if (fdCurrent > this->_fdMax)
		this->_fdMax = fdCurrent;
}

void				Server::setDate()
{
	time_t	now = time(0);
	char *	dt = ctime(&now);
	string	s = dt;

	this->_date = s.substr(0, s.length() - 1);
	return ;
}


/******************* CHECKERS **********************/

bool				Server::isMaxChannel()
{
	int nb = 0;
	vector<Channel *>::iterator last = this->_channel.end();
	for (vector<Channel *>::iterator it = this->_channel.begin(); it != last; it++)
		nb++;
	return (nb >= this->_maxChannels);
}

bool				Server::isUserEmpty()
{
	return (this->_user.empty());
}

bool				Server::isUserReal(string const & nick)
{
	for (vector<User *>::iterator it = _user.begin(); it != _user.end(); it++)
	{
		if ((*it)->getNickName() == nick)
			return (true);
	}
	return (false);
}


bool				Server::isChanReal(string const & name)
{
	for (vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++)
	{
		if ((*it)->getChannelName() == name)
		{
			return (true);
		}
	}
	return (false);
}


/******************* REPLIES **********************/


void 	Server::initReplyTree()
{
	map_rep[RPL_WELCOME] = ft_RPL_WELCOME;
	map_rep[RPL_YOURHOST] = ft_RPL_YOURHOST;
	map_rep[RPL_CREATED] = ft_RPL_CREATED;
	map_rep[RPL_MYINFO] = ft_RPL_MYINFO;
	map_rep[RPL_WHOISUSER] = ft_RPL_WHOISUSER;
	map_rep[RPL_ENDOFWHOIS] = ft_RPL_ENDOFWHOIS;
	map_rep[RPL_NAMREPLY] = ft_RPL_NAMREPLY;
	map_rep[RPL_ENDOFNAMES] = ft_RPL_ENDOFNAMES;
	map_rep[RPL_ENDOFNAMES] = ft_RPL_ENDOFNAMES;
	map_rep[RPL_LIST] = ft_RPL_LIST;
	map_rep[RPL_LISTEND] = ft_RPL_LISTEND;
	map_rep[RPL_YOUREOPER] = ft_RPL_YOUREOPER;
	map_rep[RPL_TOPIC] = ft_RPL_TOPIC;
	map_rep[RPL_UMODEIS] = ft_RPL_UMODEIS;
	map_rep[RPL_INVITING] = ft_RPL_INVITING;
	map_rep[RPL_WHOREPLY] = ft_RPL_WHOREPLY;
	map_rep[RPL_ENDOFWHO] = ft_RPL_ENDOFWHO;
}

void	Server::initErrorTree()
{
	map_err[ERR_NOSUCHNICK] = ":No such nick/channel";
	map_err[ERR_NOSUCHSERVER] = ":No such server";
	map_err[ERR_NOSUCHCHANNEL] = ":No such channel";
	map_err[ERR_CANNOTSENDTOCHAN] = ":Cannot send to channel";
	map_err[ERR_TOOMANYCHANNELS] = ":You have joined too many channels";
	map_err[ERR_WASNOSUCHNICK] =  ":There was no such nickname";
	map_err[ERR_TOOMANYTARGETS] = ":Duplicate recipients. No message delivered";
	map_err[ERR_NOORIGIN] = ":No origin specified";
	map_err[ERR_NORECIPIENT] = ":No recipient given";
	map_err[ERR_NOTEXTTOSEND] = ":No text to send";
	map_err[ERR_NOTOPLEVEL] = ":No toplevel domain specified";
	map_err[ERR_WILDTOPLEVEL] = ":Wildcard in toplevel domain";
	map_err[ERR_BADMASK] = ":Bad Server/host mask";
	map_err[ERR_UNKNOWNCOMMAND] = ":Unknown command";
	map_err[ERR_NOMOTD] = ":MOTD File is missing";
	map_err[ERR_NOADMININFO] = ":No administrative info available";
	map_err[ERR_NONICKNAMEGIVEN] = ":No nickname given";
	map_err[ERR_ERRONEUSNICKNAME] = ":Erroneus nickname";
	map_err[ERR_NICKNAMEINUSE] = ":Nickname is already in use";
	map_err[ERR_NICKCOLLISION] = ":Nickname collision KILL";
	map_err[ERR_USERNOTINCHANNEL] = ":You're not on that channel";
	map_err[ERR_NOTONCHANNEL] = ":You're not on that channel";
	map_err[ERR_USERONCHANNEL] = ":is already on channel";
	map_err[ERR_NOLOGIN] = ":User not logged in";
	map_err[ERR_SUMMONDISABLED] = ":SUMMON has been disabled";
	map_err[ERR_USERSDISABLED] = ":USERS has been disabled";
	map_err[ERR_NOTREGISTERED] = ":You have not registered";
	map_err[ERR_NEEDMOREPARAMS] = ":Not enough parameters";
	map_err[ERR_ALREADYREGISTRED] = ":You may not reregister";
	map_err[ERR_NOPERMFORHOST] = ":Your host isn't among the privileged";
	map_err[ERR_PASSWDMISMATCH] = ":Password incorrect";
	map_err[ERR_YOUREBANNEDCREEP] = ":You are banned from this server";
	map_err[ERR_KEYSET] = ":Channel key already set";
	map_err[ERR_CHANNELISFULL] = ":Cannot join channel (+l)";
	map_err[ERR_UNKNOWNMODE] = ":is unknown mode char to me";
	map_err[ERR_INVITEONLYCHAN] = ":Cannot join channel (+i)";
	map_err[ERR_BANNEDFROMCHAN] = ":Cannot join channel (+b)";
	map_err[ERR_BADCHANNELKEY] = ":Cannot join channel (+k)";
	map_err[ERR_BADCHANMASK] = ":Bad Channel Mask";
	map_err[ERR_NOCHANMODES] = ":Channel doesn't support modes";
	map_err[ERR_BANLISTFULL] = ":Channel list is full";
	map_err[ERR_NOPRIVILEGES] = ":Permission Denied- You're not an IRC operator";
	map_err[ERR_CANTKILLSERVER] = ":You cant kill a server!";
	map_err[ERR_RESTRICTED] = ":Your connection is restricted!";
	map_err[ERR_CHANOPRIVSNEEDED] = ":You're not channel operator";
	map_err[ERR_UNIQOPPRIVSNEEDED] = ":You're not the original channel operator";
	map_err[ERR_NOOPERHOST] = ":No O-lines for your host";
	map_err[ERR_ERRSYNTAX] = ":Error Syntaxe";
	map_err[ERR_UMODEUNKNOWNFLAG] = ":Unknown MODE flag";
	map_err[ERR_USERSDONTMATCH] = ":Cant change mode for other users";
}

void 	Server::ft_reply(User * from, string code, string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7)
{
	string ret = ":";
	ret += _serverName;
	ret += " ";
	ret += code;
	ret += " ";
	ret += from->getNickName();
	ret += " ";
	ret += map_rep.find(code)->second(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	ret += "\r\n";
	sendBuffer(from, ret);
}

void	Server::ft_error(User * from, string code, string arg)
{
	string ret = ":";
	ret += _serverName;
	ret += " ";
	ret += code;
	ret += " * ";
	ret += arg;
	ret += " ";
	ret += map_err.find(code)->second;
	ret += "\r\n";
	sendBuffer(from, ret);
}

void	Server::ft_notice(User * from, User * to, string notice)
{
	string ret = ":";
	ret += from->getPrefix();
	ret += " ";
	ret += notice;
	ret += "\r\n";
	sendBuffer(to, ret);
}
