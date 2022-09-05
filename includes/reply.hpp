//
// Created by user42 on 27/06/22.
//

#include "ft_irc.hpp"
#include "Server.hpp"

/************* USELESS FOR THE MOMENT *********************/

#ifndef FT_IRC_REPLY_HPP
#define FT_IRC_REPLY_HPP

using namespace irc;
using namespace std;

/*Command responses */

# define RPL_WELCOME "001"
# define RPL_YOURHOST "002"
# define RPL_CREATED "003"
# define RPL_MYINFO "004"
# define RPL_WHOISUSER "311"
# define RPL_ENDOFWHOIS "315"
# define RPL_LIST "322"
# define RPL_LISTEND "323"
# define RPL_NOTOPIC "331"
# define RPL_TOPIC "332"
# define RPL_NAMREPLY "353"
# define RPL_ENDOFNAMES "366"
# define RPL_YOUREOPER "381"
# define RPL_UMODEIS "221"
# define RPL_INVITING "341"
# define RPL_ENDOFWHO "315"
# define RPL_WHOREPLY "352"

/* Error Replies */
# define ERR_NOSUCHNICK "401"
# define ERR_NOSUCHSERVER "402"
# define ERR_NOSUCHCHANNEL "403"
# define ERR_CANNOTSENDTOCHAN "404"
# define ERR_TOOMANYCHANNELS "405"
# define ERR_WASNOSUCHNICK "406"
# define ERR_TOOMANYTARGETS "407"
# define ERR_NOSUCHSERVICE "408"
# define ERR_NOORIGIN "409"
# define ERR_NORECIPIENT "411"
# define ERR_NOTEXTTOSEND "412"
# define ERR_NOTOPLEVEL "413"
# define ERR_WILDTOPLEVEL "414"
# define ERR_BADMASK "415"
# define ERR_UNKNOWNCOMMAND "421"
# define ERR_NOMOTD "422"
# define ERR_NOADMININFO "423"
# define ERR_FILEERROR "424"
# define ERR_NONICKNAMEGIVEN "431"
# define ERR_ERRONEUSNICKNAME "432"
# define ERR_NICKNAMEINUSE "433"
# define ERR_NICKCOLLISION "436"
# define ERR_UNAVAILRESOURCE "437"
# define ERR_USERNOTINCHANNEL "441"
# define ERR_NOTONCHANNEL "442"
# define ERR_USERONCHANNEL "443"
# define ERR_NOLOGIN "444"
# define ERR_SUMMONDISABLED "445"
# define ERR_USERSDISABLED "446"
# define ERR_NOTREGISTERED "451"
# define ERR_NEEDMOREPARAMS "461"
# define ERR_ALREADYREGISTRED "462"
# define ERR_NOPERMFORHOST "463"
# define ERR_PASSWDMISMATCH "464"
# define ERR_YOUREBANNEDCREEP "465"
# define ERR_YOUWILLBEBANNED "466"
# define ERR_KEYSET "467"
# define ERR_CHANNELISFULL "471"
# define ERR_UNKNOWNMODE "472"
# define ERR_INVITEONLYCHAN "473"
# define ERR_BANNEDFROMCHAN "474"
# define ERR_BADCHANNELKEY "475"
# define ERR_BADCHANMASK "476"
# define ERR_NOCHANMODES "477"
# define ERR_BANLISTFULL "478"
# define ERR_NOPRIVILEGES "481"
# define ERR_CHANOPRIVSNEEDED "482"
# define ERR_CANTKILLSERVER "483"
# define ERR_RESTRICTED "484"
# define ERR_UNIQOPPRIVSNEEDED "485"
# define ERR_NOOPERHOST "491"
# define ERR_ERRSYNTAX "492"
# define ERR_UMODEUNKNOWNFLAG "501"
# define ERR_USERSDONTMATCH "502"

# define NTC_NICK(nick) ("NICK :" + nick)
# define NTC_MODE(nick, mode) ("MODE " + nick + " :" + mode)
# define NTC_JOIN(channel) ("JOIN :" + channel)
# define NTC_PART(channel) ("PART :" + channel)
# define NTC_PART_MSG(channel, msg) ("PART " + channel + " :\"" + msg +"\"")
# define NTC_PRIVMSG(dest, msg) ("PRIVMSG " + dest + " " + msg)
# define NTC_NOTICE(dest, msg) ("NOTICE " + dest + " " + msg)
# define NTC_QUIT(msg) (" QUIT :Quit: " + msg)
# define NTC_TOPIC(channel, topic) ("TOPIC " + channel + " :" + topic)
# define NTC_CHANMODE(channel, mode) ("MODE " + channel + " :" + mode)
# define NTC_CHANMODE_ARG(channel, mode, arg) ("MODE " + channel + " " + mode + " :" + arg)
# define NTC_KICK(channel, usr, reason) ("KICK " + channel  + " " + usr + " " + reason)
# define NTC_INVITE(channel, usr) ("INVITE " + usr  + " :" + channel)
# define NTC_WALLOPS(nick, msg) ("WALLOPS " + nick + " :" + msg)

string ft_RPL_WELCOME(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_YOURHOST(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_CREATED(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_WHOISUSER(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_MYINFO(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_NAMREPLY(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_ENDOFNAMES(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_WHOREPLY(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_ENDOFWHOIS(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_LIST(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_LISTEND(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_YOUREOPER(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_TOPIC(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_UMODEIS(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_INVITING(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);
string ft_RPL_ENDOFWHO(string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7);

#endif //FT_IRC_REPLY_HPP
