#include "Assistant.h"

#include "framework.h"
#include <fstream>
#include <sstream>
#include "Command.h"
#include "CommandParameter.h"

Assistant::Assistant()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string path(buffer);
	std::string::size_type pos = path.find_last_of("\\/");
	this->path = path.substr(0, pos + 1);
	Reload();
}

std::string Assistant::Execute(const std::string& cmd)
{
	if (cmd == "reload")
	{
		Reload();
		return "";
	}
	else if (cmd == "config")
	{
		char fullPath[MAX_PATH];
		GetFullPathNameA("config", MAX_PATH, fullPath, NULL);
		BatCommand cmd("config", "code \"" + std::string(fullPath) + '"', false);
		cmd.Execute("");
		return "";
	}
	else if (cmd == "commands")
	{
		char fullPath[MAX_PATH];
		GetFullPathNameA("commands", MAX_PATH, fullPath, NULL);
		BatCommand cmd("commands", "code \"" + std::string(fullPath) + '"', false);
		cmd.Execute("");
		return "";
	}
	else
	{
		std::string::size_type pos = cmd.find_first_of(" ", 1);
		std::string name = pos == std::string::npos ? cmd : cmd.substr(0, pos);
		for (auto& command : commands)
		{
			if (command->GetName() == name)
			{
				command->Execute(pos == std::string::npos ? "" : cmd.substr(pos + 1));
				return "";
			}
		}
		return "";
	}
}

void Assistant::Reload()
{
	commands.clear();

	std::string line;
	std::ifstream file("commands");
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string type, name;
		if (!(iss >> type >> name))
		{
			continue;
		}

		if (type == "BAT")
		{
			CommandParameter path, show;
			if (iss >> path >> show)
			{
				commands.push_back(std::make_unique<BatCommand>(name, path, show == "1"));
			}
		}
		else if (type == "URL")
		{
			CommandParameter url;
			if (iss >> url)
			{
				commands.push_back(std::make_unique<UrlCommand>(name, url));
			}
		}
	}
}
