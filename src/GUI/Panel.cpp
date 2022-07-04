#include "Panel.h"

#include "GUI.fwd.h"
#include <iostream>

Panel::Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText) {
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;

	ConstructPanel();
}

Panel::Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;

	ConstructPanel();
}

Panel::Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwExStyle, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_wStyle = p_wStyle;
	m_dwExStyle = p_dwExStyle;
	m_dwStyle = p_dwStyle;
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;

	ConstructPanel();
}

Panel::~Panel() {};

void Panel::ConstructPanel() {
	RegisterWindowClass();

	m_hWnd = CreateWindowHandle();

	if (m_hWnd == nullptr) {
		std::cout << "Failed to create handle" << std::endl;
		return;
	}

	ShowWindowHandle();

	if (m_pParentPanel != nullptr) {
		m_pParentPanel->AddChild(this);
	}

	GUI::AddElementToList(this);
}

void Panel::RegisterWindowClass() {
	WNDCLASSEXW windowClass = { 0 };;

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style = m_wStyle;
	windowClass.lpfnWndProc = StaticWndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 50;
	windowClass.hInstance = *m_phInstance;
	windowClass.hIcon = LoadIcon(*m_phInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = m_wszWindowClassText;
	windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&windowClass)) {
		std::cout << "Failed to register window class" << std::endl;
		std::cout << GetLastError() << std::endl;
	}
}

HWND Panel::CreateWindowHandle() {
	if (m_pParentPanel != nullptr) {
		return CreateWindowEx(m_dwExStyle, m_wszWindowClassText, m_wszWindowText, m_dwStyle,
			m_nPosX, m_nPosY, m_nWidth, m_nHeight, *m_pParentPanel->GetHandle(), nullptr, *m_phInstance, this);
	}
	else {
		return CreateWindowEx(m_dwExStyle, m_wszWindowClassText, m_wszWindowText, m_dwStyle,
			m_nPosX, m_nPosY, m_nWidth, m_nHeight, nullptr, nullptr, *m_phInstance, nullptr);
	}
}

LRESULT Panel::StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Panel* self;
	if (uMsg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		self = static_cast<Panel*>(lpcs->lpCreateParams);
		if (self) { self->m_hWnd = pHwnd; }
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
	default: { return DefWindowProc(m_hWnd, uMsg, wParam, lParam); }
	}

	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void Panel::ShowWindowHandle() {
	// Shows the window using the handle
	ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);

	// Updates the window using the handle
	UpdateWindow(m_hWnd);
}