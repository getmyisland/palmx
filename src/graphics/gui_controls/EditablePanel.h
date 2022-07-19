#ifndef GUI_CONTROLS_EDITABLE_PANEL_H
#define GUI_CONTROLS_EDITABLE_PANEL_H
#ifdef _WIN32
#pragma once
#endif

#include "Panel.h"

namespace gui_controls
{
	class EditablePanel : public Panel
	{
	public:
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText); // Standard
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwStyle);
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight);
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight); // Complete Constructor
		~EditablePanel();

		// Inherited methods via Panel
		const wchar_t* GetWindowName() override;
		void SetWindowName(const wchar_t* p_wszNewText) override;
		const wchar_t* GetWindowClassName() override;

		int GetPosX() override;
		int GetPosY() override;
		void SetPos(int p_nPosX, int p_nPosY) override;

		int GetWidth() override;
		int GetHeight() override;
		void SetSize(int p_nWidth, int p_nHeight) override;

		UINT GetStyle() override;
		DWORD GetDwStyle() override;
		void SetDwStyle(DWORD p_dwNewStyle) override;

		// Static WndProc to redirect to real WndProc
		static LRESULT CALLBACK StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		EditablePanel() {};

		// Inherited members via Panel
		// Name of the window
		const wchar_t* m_wszWindowText = L"Default Window";

		// Name of the window class !UNIQUE!
		const wchar_t* m_wszWindowClassText = L"Default Window Class";

		UINT m_wStyle = CS_HREDRAW | CS_VREDRAW;
		DWORD m_dwStyle = WS_THICKFRAME | WS_CLIPCHILDREN;

		// X and Y position
		int m_nPosX = 0;
		int m_nPosY = 0;

		// Width and height of window
		int m_nWidth = 1280;
		int m_nHeight = 720;

		void RegisterWindowClass() override;

		// Custom window procedure
		LRESULT CALLBACK RealWndProc(HWND m_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}

#endif // GUI_CONTROLS_EDITABLE_PANEL_H