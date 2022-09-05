//
// Created by antoine on 06/07/22.
//

#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP

#include "ft_irc.hpp"

using namespace std;

namespace irc
{
	class User;

	class Channel {

		int 					_maxUsers;
		vector<User *>			_user; //current users present in the channel
		bool					_invite;
		string 					_name; //begining with &#+| 50 char max and case insensitive, no spaces, no ^G, no coma, : is used for channel mask
		string					_topic;


	public:
		Channel(User * user, string name);

		vector<User *>			getChannelUsers() const;
		User					*getUser(string const & nickname);
		string 					getChannelName() const;
		bool					getInvite() const;
		string					getTopic() const;

		bool 					isMaxUsers();
		bool					isUserHere(User const * usr);

		void					setInvite(bool const & set);
		void					setChannelName(string const & name);
		void					setTopic(string const & topic);

		void					addUser(User * user);
		void					delUser(User * user);

		string const 			printAllUsers();

	};
}

#endif //FT_IRC_CHANNEL_HPP
