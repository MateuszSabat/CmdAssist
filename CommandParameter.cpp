#include "CommandParameter.h"

#include <sstream>

std::istream& operator>>(std::istream& is, CommandParameter& out)
{
	out.value.clear();
	is >> std::ws;

	if (is.peek() == '(')
	{
		char quote;
		is.get(quote);
		std::getline(is, out.value, ')');
	}
	else if (is.peek() == '[')
	{
		char quote;
		is.get(quote);
		std::getline(is, out.value, ']');
	}
	else if (is.peek() == '{')
	{
		char quote;
		is.get(quote);
		std::getline(is, out.value, '}');
	}
	else
	{
		is >> out.value;
	}
	return is;
}

bool operator==(const CommandParameter& param, const char* string)
{
	return param.value == string;
}
