#ifndef GUI_CONTROLS_PANEL_H
#define GUI_CONTROLS_PANEL_H
#ifdef _WIN32
#pragma once
#endif

#include <Windows.h>
#include <vector>

class Panel
{
public:
	/* === Constructor === */
	Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText); // Default
	Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight);
	Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwExStyle, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight); // Complete Constructor
	~Panel();

	/* === Methods === */
	void AddChild(Panel* p_pChildPanelToAdd) {
		m_vecChildPanels.push_back(p_pChildPanelToAdd);
	}

	/* === Getter === */
	HWND* GetHandle() { return &m_hWnd; }

	Panel* GetParentPanel() { return m_pParentPanel; }

	Panel* GetChildPanel(int p_ixChild) {
		if (p_ixChild > ((int)m_vecChildPanels.size() - 1)) {
			return nullptr;
		}
		else {
			return m_vecChildPanels[p_ixChild];
		}
	}

	int GetChildPanelCount() {
		return (int)m_vecChildPanels.size();
	}

	const wchar_t* GetWindowName() { return m_wszWindowText; }
	const wchar_t* GetWindowClassName() { return m_wszWindowClassText; }

	UINT GetStyle() { return m_wStyle; }

	DWORD GetDwExStyle() { return m_dwExStyle; }
	DWORD GetDwStyle() { return m_dwStyle; }

	int GetPosX() { return m_nPosX; }
	int GetPosY() { return m_nPosY; }

	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }

	/* === Setter === */
	void SetNewParent(Panel* p_pNewParentPanel) {
		m_pParentPanel = p_pNewParentPanel;
		SetParent(m_hWnd, *m_pParentPanel->GetHandle());
	}

	void SetWindowName(const wchar_t* p_wszNewText) {
		m_wszWindowText = p_wszNewText;
		SetWindowText(m_hWnd, m_wszWindowText);
	}

	void SetDwExStyle(DWORD p_dwNewExStyle) {
		m_dwExStyle = p_dwNewExStyle;
		SetWindowLong(m_hWnd, GWL_EXSTYLE, m_dwExStyle);
		SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
	}

	void SetDwStyle(DWORD p_dwNewStyle) {
		m_dwStyle = p_dwNewStyle;
		SetWindowLong(m_hWnd, GWL_STYLE, m_dwStyle);
		SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
	}

	void SetPos(int p_nPosX, int p_nPosY) {
		m_nPosX = p_nPosX;
		m_nPosY = p_nPosY;
		SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
	}

	void SetSize(int p_nWidth, int p_nHeight) {
		m_nWidth = p_nWidth;
		m_nHeight = p_nHeight;
		SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
	}

	/* === Static WndProc === */
	static LRESULT CALLBACK StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	// The instance of the engine
	const HINSTANCE* m_phInstance = nullptr;

	// The handle of the window
	HWND m_hWnd = nullptr;

	// Parent element
	Panel* m_pParentPanel = nullptr;

	// List of child elements
	std::vector<Panel*> m_vecChildPanels;

	// Name of the window
	const wchar_t* m_wszWindowText = L"Default Window";

	// Name of the window class !UNIQUE!
	const wchar_t* m_wszWindowClassText = L"Default Window Class";

	// Window styles
	UINT m_wStyle = CS_HREDRAW | CS_VREDRAW;
	DWORD m_dwExStyle = 0;
	DWORD m_dwStyle = WS_CHILD | WS_BORDER | WS_VISIBLE;

	// X and Y position
	int m_nPosX = 0;
	int m_nPosY = 0;

	// Width and height of window
	int m_nWidth = 1280;
	int m_nHeight = 720;

	void ConstructPanel();
	void RegisterWindowClass();
	HWND CreateWindowHandle();
	void ShowWindowHandle();

	// Custom window procedure
	LRESULT CALLBACK RealWndProc(HWND m_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // GUI_CONTROLS_PANEL_H