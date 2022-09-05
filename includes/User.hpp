//
// Created by antoine on 20/06/22.
//

#ifndef FT_IRC_CLIENT_HPP
# define FT_IRC_CLIENT_HPP

# include "ft_irc.hpp"

using namespace std;

namespace irc
{
	class Channel;
	class Server;

	class User
	{
	private:
		int 												_fd;
		string												_hostname;
		string 												_realname;
		string 												_username;
		string												_nickname;
		string 												_password;
		string 												_serverName;
		string 												_prefix;
		vector<string>										parameters;
		vector<Channel *>									_channel;
		int 												_maxChan;
		Channel												*_currChan;
		string  											_mode;
		bool												_acceptConnect;
		bool												_toClose;
		bool												_welcome;
		int													_rdySend;
		string 												_awayMsg;
		string 												_msg; //stores buffer here for accessing it via reply functions

		//if client send a cap command, ignore it

	public:
		User(int fd);
		virtual ~User();
		User &operator=(User const &rhs);

		/********************** FUNCTIONS ****************************/
		void												clearAllChannels();
		void												quitChannel(Channel * chan);
		void												addChannel(Channel * chan);
		bool												isMaxChannel();
		bool												isOperator();
		bool												isInvisible();
		bool												check_if_complete() const;


		/********************* GETTERS ***********************/
		int 												getFdUser(void) const;
		string 												getPrefix() const;
		string 												getHostname() const;
		string 												getServerName() const;
		string 												getNickName() const;
		string 												getPassWord() const;
		string 												getUserName() const;
		string												getRealName() const;
		vector<Channel *>									getChannel() const;
		bool												getChannelByName(string name);
		bool												getAcceptConnect() const;
		int 												getRdySend() const;
		string 												getMode();
		Channel												*getCurrentChannel();
		string 												getCurrentChannelName();
		bool 												getToClose();
		string 												getMsg() const;
		bool 												getWelcome() const;

		/********************** SETTERS ***********************/
		void												setMsg(string const & msg);
		void												setPrefix();
		void												setMode(string const & mode);
		void												setAcceptConnect(bool const & ac);
		void 												setFdUser(int const & fd);
		void												setNickName(string const & nickname);
		void												setUserName(string const & username);
		void												setRealName(string const & realname);
		void												setHostName(string const & hostname);
		void												setPassword(string const & password);
		void 												setRdySend();
		void 												decreaseRdySend();
		void 												resetRdySend();
		void 												setToClose(int const & x);
		void												setCurrentChannel(Channel * chan);
		void												setServerName(string const & name);
		void 												setWelcome(bool value);
		void												setOperator(bool set);
		void												setInvisible(bool set);

	};
}

#endif //FT_IRC_CLIENT_HPP
