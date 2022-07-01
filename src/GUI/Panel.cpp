#include "Panel.h"
#include <iostream>

Panel::Panel(HINSTANCE* hInst, const wchar_t* pWindowName) {
	p_hInstance = hInst;

	if (p_hInstance == nullptr) {
		return;
	}

	windowName = pWindowName;
	windowClassName = pWindowName;
	dwExStyle = WS_EX_APPWINDOW;
	dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;

	RegisterWindowClass();

	hwnd = CreateWindowHandle();

	if (hwnd == nullptr) {
		std::cout << "Failed to create handle." << std::endl;
		return;
	}

	ShowWindowHandle();
}

Panel::Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* pWindowName) {
	p_hInstance = hInst;

	if (p_hInstance == nullptr) {
		return;
	}

	p_Parent = parent;
	windowName = pWindowName;
	windowClassName = pWindowName;
	width = 600;
	height = 200;

	RegisterWindowClass();

	hwnd = CreateWindowHandleWithParent();

	if (hwnd == nullptr) {
		std::cout << "Failed to create handle." << std::endl;
		return;
	}

	ShowWindowHandle();
}

Panel::~Panel() {};

void Panel::RegisterWindowClass() {
	WNDCLASSEXW windowClass = { 0 };;

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style = style;
	windowClass.lpfnWndProc = StaticWndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 50;
	windowClass.hInstance = *p_hInstance;
	windowClass.hIcon = LoadIcon(*p_hInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = windowClassName;
	windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&windowClass)) {
		std::cout << "Failed to register class." << std::endl;
		std::cout << GetLastError() << std::endl;
	}
}

HWND Panel::CreateWindowHandle() {
	return CreateWindowEx(dwExStyle, windowClassName, windowName, dwStyle,
		posX, posY, width, height, nullptr, nullptr, *p_hInstance, nullptr);
}

LRESULT Panel::StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Panel* self;
	if (uMsg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		self = static_cast<Panel*>(lpcs->lpCreateParams);
		if (self) { self->hwnd = pHwnd; }
		if (SetWindowLongPtr(pHwnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(self)) == 0) {
			//std::cout << GetLastError() << std::endl;
		}
	}
	else {
		if (GetWindowLongPtr(pHwnd, GWLP_USERDATA) == 0) {
			//std::cout << GetLastError() << std::endl;
		}

		self = reinterpret_cast<Panel*>(
			GetWindowLongPtr(pHwnd, GWLP_USERDATA));
	}

	if (self) {
		return self->RealWndProc(pHwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(pHwnd, uMsg, wParam, lParam);
}

LRESULT Panel::RealWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		break;
	}
	default: { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND Panel::CreateWindowHandleWithParent() {
	return CreateWindowEx(dwExStyle, windowClassName, windowName, dwStyle,
		posX, posY, width, height, *p_Parent->GetPanel(), nullptr, *p_hInstance, this);
}

void Panel::ShowWindowHandle() {
	// Shows the window using the handle
	ShowWindow(hwnd, SW_SHOWNORMAL);

	// Updates the window using the handle
	UpdateWindow(hwnd);
}