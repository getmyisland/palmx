#ifndef GUI_CONTROLS_PANEL_H
#define GUI_CONTROLS_PANEL_H
#ifdef _WIN32
#pragma once
#endif

#include <Windows.h>
#include <vector>

namespace gui_controls
{
	class Panel
	{
	public:
		// Constructor
		Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText); // Standard
		Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight);
		Panel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwExStyle, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight); // Complete Constructor
		~Panel();

		// Window methods
		HWND* GetHandle();

		virtual const wchar_t* GetWindowName();
		virtual void SetWindowName(const wchar_t* p_wszNewText);
		virtual const wchar_t* GetWindowClassName();

		void SetVisible(bool p_bVisible);
		bool IsVisible();
		bool IsFullyVisible(); // Checks also if all the parents are visible

		void SetEnabled(bool p_bEnabled);
		bool IsEnabled();

		// Parent methods
		Panel* GetParentPanel();
		bool HasParent(Panel* p_pParentPanel);
		void SetNewParent(Panel* p_pNewParentPanel);

		// Child methods
		void OnChildAdded(Panel* p_pAddedChildPanel);
		Panel* GetChildPanel(int p_ixChild);
		Panel* FindChildPanelByName(const wchar_t* p_wszChildName);
		int GetChildPanelCount();

		// Layout methods
		virtual int GetPosX();
		virtual int GetPosY();
		virtual void SetPos(int p_nPosX, int p_nPosY);

		virtual int GetWidth();
		virtual int GetHeight();
		virtual void SetSize(int p_nWidth, int p_nHeight);

		// Style methods
		virtual UINT GetStyle();

		virtual DWORD GetDwExStyle();
		virtual void SetDwExStyle(DWORD p_dwNewExStyle);

		virtual DWORD GetDwStyle();
		virtual void SetDwStyle(DWORD p_dwNewStyle);

		// Static WndProc to redirect to real WndProc
		static LRESULT CALLBACK StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		Panel() {}; // Default Constructor

		// Instance of the process
		const HINSTANCE* m_phInstance = nullptr;

		// Handle of the window
		HWND m_hWnd = nullptr;

		// Parent panel
		Panel* m_pParentPanel = nullptr;

		// List of child panel
		std::vector<Panel*> m_vecChildPanels;

		// Name of the window
		const wchar_t* m_wszWindowText = L"Default Window";

		// Name of the window class !UNIQUE!
		const wchar_t* m_wszWindowClassText = L"Default Window Class";

		// Window styles
		UINT m_wStyle = 0;
		DWORD m_dwExStyle = WS_EX_APPWINDOW;
		DWORD m_dwStyle = WS_CLIPCHILDREN; // WS_CHILD | WS_BORDER | WS_VISIBLE

		// X and Y position
		int m_nPosX = 0;
		int m_nPosY = 0;

		// Width and height of window
		int m_nWidth = 1280;
		int m_nHeight = 720;

		void ConstructPanel();
		virtual void RegisterWindowClass();
		virtual HWND CreateWindowHandle();
		virtual void ShowWindowHandle();

		// Custom window procedure
		LRESULT CALLBACK RealWndProc(HWND m_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}

#endif // GUI_CONTROLS_PANEL_H