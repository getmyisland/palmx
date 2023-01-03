#include "Panel.h"
#include "../GraphicModule.h"
#include "../../logging/Logger.h"

gui_controls::Panel::Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText)
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

gui_controls::Panel::Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
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

gui_controls::Panel::Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwExStyle, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight)
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
	m_wStyle = p_wStyle;
	m_dwExStyle = p_dwExStyle;
	m_dwStyle = p_dwStyle;
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;

	ConstructPanel();
}

gui_controls::Panel::~Panel() {};

bool gui_controls::Panel::Release() 
{
	if (!DestroyWindow(m_hWnd))
	{
		return false;
	}

	return true;
}

void gui_controls::Panel::ConstructPanel()
{
	LOGGER.LogW(Logger::Severity::Info, L"Creating " + std::wstring(GetWindowName()) + L" panel");

	RegisterWindowClass();

	m_hWnd = CreateWindowHandle();

	if (m_hWnd == nullptr)
	{
		LOGGER.Log(Logger::Severity::Error, "Failed to create handle");
		LOGGER.LogLastError(Logger::Severity::Error, GetLastError());
		return;
	}
	else 
	{
		LOGGER.LogW(Logger::Severity::Info, L"Created handle for " + std::wstring(GetWindowName()) + L" panel");
	}

	ShowWindowHandle();

	if (m_pParentPanel != nullptr)
	{
		m_pParentPanel->OnChildAdded(this);
	}
	else
	{
		LOGGER.Log(Logger::Severity::Warning, "No parent panel provided");
	}

	GraphicModule::AddElementToList(this);

	LOGGER.LogW(Logger::Severity::Info, L"Finished creating " + std::wstring(GetWindowName()) + L" panel");
}

void gui_controls::Panel::RegisterWindowClass()
{
	WNDCLASSEXW windowClass = { 0 };

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style = GetStyle();
	windowClass.lpfnWndProc = Panel::StaticWndProc;
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
	else 
	{
		LOGGER.LogW(Logger::Severity::Info, L"Created window class for " + std::wstring(GetWindowName()) + L" panel");
	}
}

HWND gui_controls::Panel::CreateWindowHandle()
{
	if (m_pParentPanel != nullptr)
	{
		return CreateWindowEx(GetDwExStyle(), GetWindowClassName(), GetWindowName(), GetDwStyle(),
			GetPosX(), GetPosY(), GetWidth(), GetHeight(), *m_pParentPanel->GetHandle(), nullptr, *m_phInstance, this);
	}
	else
	{
		return CreateWindowEx(GetDwExStyle(), GetWindowClassName(), GetWindowName(), GetDwStyle(),
			GetPosX(), GetPosY(), GetWidth(), GetHeight(), nullptr, nullptr, *m_phInstance, this);
	}
}

LRESULT gui_controls::Panel::StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Panel* self;
	if (uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		self = static_cast<Panel*>(lpcs->lpCreateParams);
		if (self) { self->m_hWnd = pHwnd; }
		SetWindowLongPtr(pHwnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(self));
	}
	else
	{
		self = reinterpret_cast<Panel*>(
			GetWindowLongPtr(pHwnd, GWLP_USERDATA));
	}

	if (self)
	{
		return self->RealWndProc(pHwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(pHwnd, uMsg, wParam, lParam);
}

LRESULT gui_controls::Panel::RealWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void gui_controls::Panel::ShowWindowHandle()
{
	// Shows the window using the handle
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);

	// Updates the window using the handle
	UpdateWindow(m_hWnd);
}

HWND* gui_controls::Panel::GetHandle()
{
	return &m_hWnd;
}

const HINSTANCE* gui_controls::Panel::GetWindowInstance() 
{
	return m_phInstance;
}

const wchar_t* gui_controls::Panel::GetWindowName()
{
	return m_wszWindowText;
}

void gui_controls::Panel::SetWindowName(const wchar_t* p_wszNewText)
{
	m_wszWindowText = p_wszNewText;
	SetWindowText(m_hWnd, m_wszWindowText);
}

const wchar_t* gui_controls::Panel::GetWindowClassName()
{
	return m_wszWindowClassText;
}

void gui_controls::Panel::SetVisible(bool p_bVisible)
{
	if (p_bVisible) {
		ShowWindow(m_hWnd, SW_SHOW);
	}
	else {
		ShowWindow(m_hWnd, SW_HIDE);
	}
}

bool gui_controls::Panel::IsVisible()
{
	return IsWindowVisible(m_hWnd);
}

// Checks also if all the parents are visible
bool gui_controls::Panel::IsFullyVisible()
{
	// If the current window is not visible
	if (!IsVisible())
	{
		return false;
	}

	// If the current window has no parent
	if (this->GetParentPanel() == nullptr)
	{
		return true;
	}

	Panel* tempParent = this->GetParentPanel();

	// If the parent panel is not visible
	if (!tempParent->IsVisible())
	{
		return false;
	}

	while (true) {
		// Check if the new parent has another parent
		if (tempParent->GetParentPanel() != nullptr)
		{
			tempParent = tempParent->GetParentPanel();

			// If the new parent is not visible
			if (!tempParent->IsVisible())
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	return true;
}

void gui_controls::Panel::SetEnabled(bool p_bEnabled)
{
	EnableWindow(m_hWnd, p_bEnabled);
}

bool gui_controls::Panel::IsEnabled()
{
	return IsWindowEnabled(m_hWnd);
}

gui_controls::Panel* gui_controls::Panel::GetParentPanel()
{
	return m_pParentPanel;
}

bool gui_controls::Panel::HasParent(Panel* p_pParentPanel)
{
	if (this->GetParentPanel() == nullptr)
	{
		return false;
	}

	Panel* tempParent = this->GetParentPanel();

	if (tempParent == p_pParentPanel)
	{
		return true;
	}

	while (true)
	{
		if (tempParent->GetParentPanel() != nullptr)
		{
			tempParent = tempParent->GetParentPanel();

			if (tempParent == p_pParentPanel)
			{
				break;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

void gui_controls::Panel::SetNewParent(Panel* p_pNewParentPanel)
{
	m_pParentPanel = p_pNewParentPanel;
	SetParent(m_hWnd, *m_pParentPanel->GetHandle());
}

void gui_controls::Panel::OnChildAdded(Panel* p_pAddedChildPanel)
{
	m_vecChildPanels.push_back(p_pAddedChildPanel);
}

gui_controls::Panel* gui_controls::Panel::GetChildPanel(int p_ixChild)
{
	if (p_ixChild > ((int)m_vecChildPanels.size() - 1)) // Check if the index is in range
	{
		return nullptr;
	}
	else
	{
		return m_vecChildPanels[p_ixChild];
	}
}

gui_controls::Panel* gui_controls::Panel::FindChildPanelByName(const wchar_t* p_wszChildName)
{
	for (Panel* childPanel : m_vecChildPanels)
	{
		if (childPanel->GetWindowName() == p_wszChildName)
		{
			return childPanel;
		}
	}

	return nullptr;
}

int gui_controls::Panel::GetChildPanelCount()
{
	return (int)m_vecChildPanels.size();
}

int gui_controls::Panel::GetPosX()
{
	return m_nPosX;
}

int gui_controls::Panel::GetPosY()
{
	return m_nPosY;
}

void gui_controls::Panel::SetPos(int p_nPosX, int p_nPosY)
{
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

int gui_controls::Panel::GetWidth()
{
	return m_nWidth;
}

int gui_controls::Panel::GetHeight()
{
	return m_nHeight;
}

void gui_controls::Panel::SetSize(int p_nWidth, int p_nHeight)
{
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

UINT gui_controls::Panel::GetStyle()
{
	return m_wStyle;
}

DWORD gui_controls::Panel::GetDwExStyle()
{
	return m_dwExStyle;
}

void gui_controls::Panel::SetDwExStyle(DWORD p_dwNewExStyle)
{
	m_dwExStyle = p_dwNewExStyle;
	SetWindowLong(m_hWnd, GWL_EXSTYLE, m_dwExStyle);
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

DWORD gui_controls::Panel::GetDwStyle()
{
	return m_dwStyle;
}

void gui_controls::Panel::SetDwStyle(DWORD p_dwNewStyle)
{
	m_dwStyle = p_dwNewStyle;
	SetWindowLong(m_hWnd, GWL_STYLE, m_dwStyle);
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}