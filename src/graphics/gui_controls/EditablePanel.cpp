#include "EditablePanel.h"
#include "../../debug/Logger.h"
#include <iostream>

gui_controls::EditablePanel::EditablePanel(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		Logger::Log(Logger::Severity::FATAL, "HINSTANCE is a nullptr");
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;

	ConstructPanel();
}

gui_controls::EditablePanel::EditablePanel(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwStyle)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		Logger::Log(Logger::Severity::FATAL, "HINSTANCE is a nullptr");
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_wStyle = p_wStyle;
	m_dwStyle = p_dwStyle;

	ConstructPanel();
}

gui_controls::EditablePanel::EditablePanel(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		Logger::Log(Logger::Severity::FATAL, "HINSTANCE is a nullptr");
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

gui_controls::EditablePanel::EditablePanel(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		Logger::Log(Logger::Severity::FATAL, "HINSTANCE is a nullptr");
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_wStyle = p_wStyle;
	m_dwStyle = p_dwStyle;
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;

	ConstructPanel();
}

gui_controls::EditablePanel::~EditablePanel() {};

void gui_controls::EditablePanel::RegisterWindowClass()
{
	WNDCLASSEXW windowClass = { 0 };

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style = GetStyle();
	windowClass.lpfnWndProc = EditablePanel::StaticWndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 50;
	windowClass.hInstance = *m_phInstance;
	windowClass.hIcon = LoadIcon(*m_phInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = GetWindowClassName();
	windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&windowClass))
	{
		Logger::Log(Logger::Severity::FATAL, "Failed to register window class with error " + GetLastError());
	}
}

LRESULT gui_controls::EditablePanel::StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	EditablePanel* self;
	if (uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		self = static_cast<EditablePanel*>(lpcs->lpCreateParams);
		if (self) { self->m_hWnd = pHwnd; }
		SetWindowLongPtr(pHwnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(self));
	}
	else
	{
		self = reinterpret_cast<EditablePanel*>(
			GetWindowLongPtr(pHwnd, GWLP_USERDATA));
	}

	if (self)
	{
		return self->RealWndProc(pHwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(pHwnd, uMsg, wParam, lParam);
}

LRESULT gui_controls::EditablePanel::RealWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

const wchar_t* gui_controls::EditablePanel::GetWindowName()
{
	return m_wszWindowText;
}

void gui_controls::EditablePanel::SetWindowName(const wchar_t* p_wszNewText)
{
	m_wszWindowText = p_wszNewText;
	SetWindowText(m_hWnd, m_wszWindowText);
}

const wchar_t* gui_controls::EditablePanel::GetWindowClassName()
{
	return m_wszWindowClassText;
}

int gui_controls::EditablePanel::GetPosX()
{
	return m_nPosX;
}

int gui_controls::EditablePanel::GetPosY()
{
	return m_nPosY;
}

void gui_controls::EditablePanel::SetPos(int p_nPosX, int p_nPosY)
{
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

int gui_controls::EditablePanel::GetWidth()
{
	return m_nWidth;
}

int gui_controls::EditablePanel::GetHeight()
{
	return m_nHeight;
}

void gui_controls::EditablePanel::SetSize(int p_nWidth, int p_nHeight)
{
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

UINT gui_controls::EditablePanel::GetStyle()
{
	return m_wStyle;
}

DWORD gui_controls::EditablePanel::GetDwStyle()
{
	return m_dwStyle;
}

void gui_controls::EditablePanel::SetDwStyle(DWORD p_dwNewStyle)
{
	m_dwStyle = p_dwNewStyle;
	SetWindowLong(m_hWnd, GWL_STYLE, m_dwStyle);
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}