#include "Config.h"

#include <fstream>
#include <sstream>

Config::Config(const std::string& path)
{
	HotkeyModifiers = MOD_ALT;
	HotkeyKey = 'Q';

	std::string line;
	std::ifstream file(path);
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string name;
		if (iss >> name)
		{
			if (name == "Hotkey")
			{
				HotkeyModifiers = 0;
				std::string token;
				while (iss >> token)
				{
					if (token == "Alt")
					{
						HotkeyModifiers |= MOD_ALT;
					}
					else if (token == "Shift")
					{
						HotkeyModifiers |= MOD_SHIFT;
					}
					else if (token == "Ctrl")
					{
						HotkeyModifiers |= MOD_CONTROL;
					}
					else {
						HotkeyKey = token[0];
					}
				}
			}
		}
	}
}
