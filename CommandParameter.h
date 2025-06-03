#pragma once

#include <string>

class CommandParameter
{
	std::string value;

public:
	friend std::istream& operator>>(std::istream& is, CommandParameter& out);
	friend bool operator== (const CommandParameter& param, const char* string);

	const std::string& Get() const { return value; }
	operator const std::string& () const { return value; }
};

