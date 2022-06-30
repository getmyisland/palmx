#include "Panel.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		// Exit the program
		PostQuitMessage(0);

		break;
	}
	default: { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Panel::Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* szTitle) {
	p_hInstance = hInst;
	
	p_Parent = parent;

	windowTitle = szTitle;
	windowClassTitle = szTitle;

	if (p_hInstance == nullptr) {
		return;
	}

	RegisterWindowClass();

	HWND tempHandle = CreateWindowHandle();
	hwnd = &tempHandle;

	if (hwnd == nullptr) {
		return;
	}
	
	ShowWindowHandle();
}

Panel::~Panel() {};

void Panel::RegisterWindowClass() {
	WNDCLASSEXW windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = *p_hInstance;
	windowClass.hIcon = LoadIcon(*p_hInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = (LPCWSTR)windowClassTitle;
	windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

	RegisterClassExW(&windowClass);
}

HWND Panel::CreateWindowHandle() {
	return CreateWindowEx(WS_EX_APPWINDOW, (LPCWSTR)windowClassTitle, (LPCWSTR)windowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, *p_hInstance, nullptr);
}

void Panel::ShowWindowHandle() {
	// Shows the window using the handle
	ShowWindow(*hwnd, SW_SHOW);

	// Updates the window using the handle
	UpdateWindow(*hwnd);
}