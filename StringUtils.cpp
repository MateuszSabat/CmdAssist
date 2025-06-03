#include "StringUtils.h"

int MoveToPreviousWord(const std::string& str, int pos)
{
	if (pos > str.length())
	{
		return pos;
	}
	while (pos > 0 && !isalnum(str[pos - 1]))
	{
		--pos;
	}
	while (pos > 0 && isalnum(str[pos - 1]))
	{
		--pos;
	}
	return pos;
}

int MoveToNextWord(const std::string& str, int pos)
{
	if (pos < 0)
	{
		return pos;
	}
	while (pos < str.length() && isalnum(str[pos]))
	{
		++pos;
	}
	while (pos < str.length() && !isalnum(str[pos]))
	{
		++pos;
	}
	return pos;
}

void DeleteWordBackward(std::string& str, int& pos)
{
	if (pos > 0)
	{
		int begining = MoveToPreviousWord(str, pos);
		str.erase(begining, pos - begining);
		pos = begining;
	}
}

void DeleteWordForward(std::string& str, int& pos)
{
	if (pos < str.length())
	{
		int ending = MoveToNextWord(str, pos);
		str.erase(pos, ending - pos);
	}
}
