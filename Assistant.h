#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Command.h"

class Assistant
{
	std::string path;
	std::vector<std::unique_ptr<Command>> commands;

public:
	Assistant();

	std::string Execute(const std::string& command);

private:
	void Reload();
};

