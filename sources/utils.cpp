//
// Created by alangloi on 7/12/22.
//

#include "../includes/ft_irc.hpp"

using namespace irc;
using namespace std;

string	isDouble(vector<string> str)
{
	map<string, int> count;
	pair< map<string, int>::iterator, bool > result;

	for (vector<string>::iterator it = str.begin(); it != str.end(); it++)
	{
		result = count.insert(pair<string, int>(*it, 1));
		if (!result.second)
		{
			return (result.first->first);
		}
	}
	return ("");
}
