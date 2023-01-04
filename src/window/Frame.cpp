#include "Frame.h"
#include "../logging/Logger.h"

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		LOGGER.Log(Logger::Severity::Error, "HINSTANCE is a nullptr");
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;

	ConstructPanel();
}

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		LOGGER.Log(Logger::Severity::Error, "HINSTANCE is a nullptr");
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_dwStyle = p_dwStyle;

	ConstructPanel();
}

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		LOGGER.Log(Logger::Severity::Error, "HINSTANCE is a nullptr");
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

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
{
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr)
	{
		LOGGER.Log(Logger::Severity::Error, "HINSTANCE is a nullptr");
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

void gui_controls::Frame::RegisterWindowClass()
{
	WNDCLASSEXW windowClass = { 0 };

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style = GetStyle();
	windowClass.lpfnWndProc = Frame::StaticWndProc;
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
		LOGGER.Log(Logger::Severity::Error, "Failed to register window class");
		LOGGER.LogLastError(Logger::Severity::Error, GetLastError());
	}
}

LRESULT gui_controls::Frame::StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Frame* self;
	if (uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		self = static_cast<Frame*>(lpcs->lpCreateParams);
		if (self) { self->m_hWnd = pHwnd; }
		SetWindowLongPtr(pHwnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(self));
	}
	else
	{
		self = reinterpret_cast<Frame*>(
			GetWindowLongPtr(pHwnd, GWLP_USERDATA));
	}

	if (self)
	{
		return self->RealWndProc(pHwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(pHwnd, uMsg, wParam, lParam);
}

LRESULT gui_controls::Frame::RealWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(m_hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	default:
		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	return NULL;
}

const wchar_t* gui_controls::Frame::GetWindowName()
{
	return m_wszWindowText;
}

void gui_controls::Frame::SetWindowName(const wchar_t* p_wszNewText)
{
	m_wszWindowText = p_wszNewText;
	SetWindowText(m_hWnd, m_wszWindowText);
}

const wchar_t* gui_controls::Frame::GetWindowClassName()
{
	return m_wszWindowClassText;
}

int gui_controls::Frame::GetPosX()
{
	return m_nPosX;
}

int gui_controls::Frame::GetPosY()
{
	return m_nPosY;
}

void gui_controls::Frame::SetPos(int p_nPosX, int p_nPosY)
{
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

int gui_controls::Frame::GetWidth()
{
	return m_nWidth;
}

int gui_controls::Frame::GetHeight()
{
	return m_nHeight;
}

void gui_controls::Frame::SetSize(int p_nWidth, int p_nHeight)
{
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

DWORD gui_controls::Frame::GetDwStyle()
{
	return m_dwStyle;
}

void gui_controls::Frame::SetDwStyle(DWORD p_dwNewStyle)
{
	m_dwStyle = p_dwNewStyle;
	SetWindowLong(m_hWnd, GWL_STYLE, m_dwStyle);
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}