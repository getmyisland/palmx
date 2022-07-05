#include "Frame.h"
#include <iostream>

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText) {
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

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle) {
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_dwStyle = p_dwStyle;

	ConstructPanel();
}

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight) {
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

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight) {
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_dwStyle = p_dwStyle;
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;

	ConstructPanel();
}

gui_controls::Frame::~Frame() {};

// TODO WndProc not working in Frame and EditablePanel
LRESULT gui_controls::Frame::RealWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	std::cout << "Hello World" << std::endl;

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

DWORD gui_controls::Frame::GetDwStyle() {
	return m_dwStyle;
}

void gui_controls::Frame::SetDwStyle(DWORD p_dwNewStyle) {
	m_dwStyle = p_dwNewStyle;
	SetWindowLong(m_hWnd, GWL_STYLE, m_dwStyle);
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}