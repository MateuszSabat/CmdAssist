#pragma once

#include <string>
#include <windows.h>

struct Config
{
	UINT HotkeyModifiers;
	UINT HotkeyKey;

	explicit Config(const std::string& path);
};

