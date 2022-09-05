#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <algorithm>
# include <arpa/inet.h>
# include <bitset>
# include <iostream>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <map>
# include <netinet/ip.h>
# include <fcntl.h>
# include <poll.h>
# include <string.h>
# include <sstream>
# include <stdio.h>
# include <unistd.h>
# include <vector>
# include <ctime>

# include "Channel.hpp"
# include "reply.hpp"
# include "Server.hpp"
# include "User.hpp"

# define OPER_PASS		"hackme"
# define OPER_NAME		"admin"
# define SERVER_NAME	"surLeFil"
# define VERSION		"1.0"

// Reset
# define RESET		"\033[0m"

// DarkColors
# define DBLACK		"\033[2;30m"
# define DRED		"\033[2;31m"
# define DGREEN		"\033[2;32m"
# define DYELLOW	"\033[2;33m"
# define DBLUE		"\033[2;34m"
# define DPURPLE	"\033[2;35m"
# define DCYAN		"\033[2;36m"
# define DWHITE		"\033[2;37m"

// Regular Colors
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"

// Bold
# define BBLACK		"\033[1;30m"
# define BRED		"\033[1;31m"
# define BGREEN		"\033[1;32m"
# define BYELLOW	"\033[1;33m"
# define BBLUE		"\033[1;34m"
# define BPURPLE	"\033[1;35m"
# define BCYAN		"\033[1;36m"
# define BWHITE		"\033[1;37m"

// Underline
# define UBLACK		"\033[4;30m"
# define URED		"\033[4;31m"
# define UGREEN		"\033[4;32m"
# define UYELLOW	"\033[4;33m"
# define UBLUE		"\033[4;34m"
# define UPURPLE	"\033[4;35m"
# define UCYAN		"\033[4;36m"
# define UWHITE		"\033[4;37m"

// Background
# define OBLACK		"\033[40m"
# define ORED		"\033[41m"
# define OGREEN		"\033[42m"
# define OYELLOW	"\033[43m"
# define OBLUE		"\033[44m"
# define OPURPLE	"\033[45m"
# define OCYAN		"\033[46m"
# define OWHITE		"\033[47m"

// High Intensity
# define IBLACK		"\033[0;90m"
# define IRED		"\033[0;91m"
# define IGREEN		"\033[0;92m"
# define IYELLOW	"\033[0;93m"
# define IBLUE		"\033[0;94m"
# define IPURPLE	"\033[0;95m"
# define ICYAN		"\033[0;96m"
# define IWHITE		"\033[0;97m"

// Bold High Intensity
# define BIBLACK	"\033[1;90m"
# define BIRED		"\033[1;91m"
# define BIGREEN	"\033[1;92m"
# define BIYELLOW	"\033[1;93m"
# define BIBLUE		"\033[1;94m"
# define BIPURPLE	"\033[1;95m"
# define BICYAN		"\033[1;96m"
# define BIWHITE	"\033[1;97m"

// High Intensity backgrounds
# define OIBLACK	"\033[0;100m"
# define OIRED		"\033[0;101m"
# define OIGREEN	"\033[0;102m"
# define OIYELLOW	"\033[0;103m"
# define OIBLUE		"\033[0;104m"
# define OIPURPLE	"\033[0;105m"
# define OICYAN		"\033[0;106m"
# define OIWHITE	"\033[0;107m"

using namespace std;
using namespace irc;

void	cap_cmd(Server & srv, User & usr, vector<string> params);
void	die_cmd(Server & srv, User & usr, vector<string> params);
void	join_cmd(Server & srv, User & usr, vector<string> params);
void	kick_cmd(Server & srv, User & usr, vector<string> params);
void	list_cmd(Server & srv, User & usr, vector<string> params);
void	mode_cmd(Server & srv, User & usr, vector<string> params);
void	msg_cmd(Server & srv, User & usr, vector<string> params);
void	names_cmd(Server & srv, User & usr, vector<string> params);
void	nick_cmd(Server & srv, User & usr, vector<string> params);
void	notice_cmd(Server & srv, User & usr, vector<string> params);
void	oper_cmd(Server & srv, User & usr, vector<string> params);
void	part_cmd(Server & srv, User & usr, vector<string> params);
void	pass_cmd(Server & srv, User & usr, vector<string> params);
void	ping_cmd(Server & srv, User & usr, vector<string> params);
void	pong_cmd(Server & srv, User & usr, vector<string> params);
void	privmsg_cmd(Server & srv, User & usr, vector<string> params);
void	quit_cmd(Server & srv, User & usr, vector<string> params);
void	user_cmd(Server & srv, User & usr, vector<string> params);
void	topic_cmd(Server & srv, User & usr, vector<string> params);
void	wallops_cmd(Server & srv, User & usr, vector<string> params);
void	whois_cmd(Server & srv, User & usr, vector<string> params);
void	invite_cmd(Server & srv, User & usr, vector<string> params);

string	isDouble(vector<string> str);

#endif
