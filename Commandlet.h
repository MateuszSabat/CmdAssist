#pragma once

#include "framework.h"
#include <string>
#include "Assistant.h"

class Commandlet
{
	HWND hWnd;
	bool isVisible;

	HBRUSH hBrush;

	std::string text;
	int caretPos;

	Assistant assistant;

public:
	explicit Commandlet(HINSTANCE hInstance);
	~Commandlet();

	void Toggle();

private:
	static LRESULT CALLBACK StaticWndHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool WndHandle(UINT message, WPARAM wParam, LPARAM lParam);

	bool Ctrl();
	void Repaint();
};

