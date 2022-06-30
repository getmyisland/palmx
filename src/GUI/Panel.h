#pragma once

#include <Windows.h>

#define MAX_LOADSTRING 100

class Panel
{
public:
	Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* title);
	~Panel();

private:
	Panel() {};

	const HINSTANCE* p_hInstance = nullptr;

	Panel* p_Parent = nullptr;

	const wchar_t* windowTitle = nullptr;
	const wchar_t* windowClassTitle = nullptr;

	const HWND *hwnd = nullptr;

	void RegisterWindowClass();
	HWND CreateWindowHandle();
	void ShowWindowHandle();
};