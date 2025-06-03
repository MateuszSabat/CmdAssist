#pragma once

#include <string>

class Command
{
	std::string name;

public:
	Command(const std::string& name) : name(name) { }
	
	inline const std::string& GetName() const { return name; }

	virtual void Execute(const std::string& params) = 0;
};

class BatCommand : public Command
{
	std::string cmd;
	bool show;

public:
	BatCommand(const std::string& name, const std::string& cmd, bool show) : Command(name), cmd(cmd), show(show) {}
	
	virtual void Execute(const std::string& params) override;
};

class UrlCommand : public Command
{
	std::string url;

public:
	UrlCommand(const std::string& name, const std::string& url) : Command(name), url(url) {}

	virtual void Execute(const std::string& params) override;
};