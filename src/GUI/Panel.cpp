#include "Panel.h"

#include "GUI.fwd.h"
#include <iostream>

Panel::Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* pWindowName) {
	hInstance = hInst;

	if (hInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	p_Parent = parent;
	windowName = pWindowName;
	windowClassName = pWindowName;

	ConstructPanel();
}

Panel::Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* pWindowName, UINT pStyle, DWORD pDwExStyle, DWORD pDwStyle, int pX, int pY, int pWidth, int pHeight)
{
	hInstance = hInst;

	if (hInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	p_Parent = parent;
	windowName = pWindowName;
	windowClassName = pWindowName;
	style = pStyle;
	dwExStyle = pDwExStyle;
	dwStyle = pDwStyle;
	posX = pX;
	posY = pY;
	width = pWidth;
	height = pHeight;

	ConstructPanel();
}

Panel::~Panel() {};

void Panel::ConstructPanel() {
	RegisterWindowClass();

	hwnd = CreateWindowHandle();

	if (hwnd == nullptr) {
		std::cout << "Failed to create handle" << std::endl;
		return;
	}

	ShowWindowHandle();

	if (p_Parent != nullptr) {
		p_Parent->AddChild(this);
	}

	GUI::AddElementToList(this);
}

void Panel::RegisterWindowClass() {
	WNDCLASSEXW windowClass = { 0 };;

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style = style;
	windowClass.lpfnWndProc = StaticWndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 50;
	windowClass.hInstance = *hInstance;
	windowClass.hIcon = LoadIcon(*hInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = windowClassName;
	windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&windowClass)) {
		std::cout << "Failed to register window class" << std::endl;
		std::cout << GetLastError() << std::endl;
	}
}

HWND Panel::CreateWindowHandle() {
	if (p_Parent != nullptr) {
		return CreateWindowEx(dwExStyle, windowClassName, windowName, dwStyle,
			posX, posY, width, height, *p_Parent->GetHandle(), nullptr, *hInstance, this);
	}
	else {
		return CreateWindowEx(dwExStyle, windowClassName, windowName, dwStyle,
			posX, posY, width, height, nullptr, nullptr, *hInstance, nullptr);
	}
}

LRESULT Panel::StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Panel* self;
	if (uMsg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		self = static_cast<Panel*>(lpcs->lpCreateParams);
		if (self) { self->hwnd = pHwnd; }
		SetWindowLongPtr(pHwnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(self));
	}
	else {
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

void Panel::ShowWindowHandle() {
	// Shows the window using the handle
	ShowWindow(hwnd, SW_SHOWNORMAL);

	// Updates the window using the handle
	UpdateWindow(hwnd);
}