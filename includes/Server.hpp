//
// Created by blyzance on 18/06/22.
//

#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

#include "ft_irc.hpp"

using namespace std;

namespace irc
{
	class User;
	class Channel;

	class Server
	{

	public:
		typedef string (*function_reply)(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
		typedef void (*function_command)(Server & srv, User & usr, std::vector<std::string> params);

	private:
		map<string, function_command>					map_cmd;
		map<string, function_reply>						map_rep;
		map<string, string>								map_err;

	private:
		int 											_fd;
		int												_fdMax;
		struct sockaddr_in								_serverAddr;
		string											_serverName; //identify the server, has a max length of 63 chars. servername = hostname
		socklen_t										_size;			//_user; //we're going to delete it for the instanciation with set
		vector<User *>									_user;
		vector<User *>									_oper;
		vector<Channel *>								_channel;
		int												_portNum; //default port 6667
		bool											_state;
		string											_password;
		vector<vector<string> >							_param;
		int 											_maxChannels;
		string 											_date;
		string 											_ver;

	public:
		// Server(int const & portNum);
		Server(int const & portNum, string const & passw);
		virtual ~Server();

		/******************** CONNECTION **********************/
		void 											initServer(void);
		void											establishConnection(void);
		void											createServerAddr(int const & portNum);
		int												acceptUser(socklen_t size);
		void											closeUser(User const &  user);
		int												bindServer(void);
		void											sendBuffer(User * dest, string const & content);
		void											printParam();
		void											initCommand();
		void 											welcome(int const & fd);
		void											parse_buffer_command(string const &  buffer);
		void 											execCommand(int const & fd);
		bool											check_command(User * u, size_t want, vector<string> command);
		int												searchNick(string const & nick);
		void											sendToChan(string const & name, string const & msg);
		void											sendToUser(string const & name, string const & msg);
		void											sending(int fd, string toSend);
		Channel*										addChannel(User * user, string const & name);
		Channel*										searchChannel(string const & name);
		void											delUserAllChannel(User * user);
		void 											deleteUser(vector<User *>::iterator user);
		void											deleteChannel(Channel * chan);
		string 											printListChannels();

		/******************** ACCESSORS **********************/
		int												getFdMax( void ) const;
		int												getFdServer() const;
		struct sockaddr_in								getServerAddr() const;
		vector<User *>									getUsers() const;

		vector<User *>::iterator						getUser(int const & fd);
		vector<User *>::iterator						getUser(string const & nick);
		User*											getUserInstance(string const & name);
		Channel*										getChannelByName(string const & name);
		vector<Channel *>								getChannels() const;
		string 											getVersion() const;
		socklen_t										getSize() const;
		int												getPortNum() const;
		vector<User *>									getOper() const;
		User*											getOper(string const & name);
		int 											getMaxChannel() const;
		bool											getState() const;
		string											getServerName() const;
		string											getPassword() const;
		string											getDate() const;

		/********************* MUTATORS *************************/
		void											setFdServer(int const & fd);
		void											setState(bool const & st);
		void											setUpFdMax(int const & fdCurrent);
		void											setDate();


		/******************* CHECKERS **********************/
		bool											isMaxChannel();
		bool											isUserEmpty();
		bool											isUserReal(string const & nick);
		bool											isChanReal(string const & nick);

		/********************* REPLIES **************************/
		void											initReplyTree();
		void											initErrorTree();
		void											ft_notice(User * from, User * to, string notice);
		void 											ft_reply(User * from, string code, string arg1 = "", string arg2 = "", string arg3 = "", string arg4 = "", string arg5 = "", string arg6 = "", string arg7 = "");
		void											ft_error(User * from, string code, string arg = "");
	};
}

#endif //FT_IRC_SERVER_HPP
